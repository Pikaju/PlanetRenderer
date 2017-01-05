#include "Shader.h"

#include <glew.h>

#include "../../debug/Debug.h"
#include "../../io/ResourceLoader.h"

Shader::Shader() : m_program(0)
{
}

Shader::~Shader()
{
	cleanup();
}

void Shader::init()
{
	cleanup();
	m_program = glCreateProgram();
}

void Shader::cleanup()
{
	deleteShaders();
	if (m_program != 0) {
		glDeleteProgram(m_program);
		m_program = 0;
	}
}

void Shader::addShader(const char* file, ShaderType::ShaderType type)
{
	unsigned int shader = glCreateShader(getGLShaderType(type));

	std::string stringSource;
	bool success = ResourceLoader::readText(file, stringSource);
	if (!success) {
		Debug::crash((std::string("Failed to read file: ") + file).c_str());
	}
	const char* source = stringSource.c_str();
	glShaderSource(shader, 1, &source, 0);
	
	glCompileShader(shader);
	glAttachShader(m_program, shader);
	m_shaders.push_back(shader);
}

void Shader::link()
{
	glLinkProgram(m_program);
	int status;
	glGetProgramiv(m_program, GL_LINK_STATUS, &status);
	if (!status) {
		int infoLogLength;
		glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<char> log(infoLogLength);
		glGetProgramInfoLog(m_program, log.size(), &infoLogLength, log.data());
		Debug::crash((std::string("Failed to link program:\n\n") + log.data()).c_str());
	}
	glValidateProgram(m_program);
	deleteShaders();
}

void Shader::enable()
{
	glUseProgram(m_program);
}

void Shader::disable()
{
	glUseProgram(0);
}

int Shader::getUniformLocation(const char* name) const
{
	return glGetUniformLocation(m_program, name);
}

void Shader::setUniform(const char* name, int v) const
{
	glUniform1i(getUniformLocation(name), v);
}

void Shader::setUniform(const char* name, float v) const
{
	glUniform1f(getUniformLocation(name), v);
}

void Shader::setUniform(const char* name, const Vec2& v) const
{
	glUniform2f(getUniformLocation(name), v.getX(), v.getY());
}

void Shader::setUniform(const char* name, const Vec3& v) const
{
	glUniform3f(getUniformLocation(name), v.getX(), v.getY(), v.getZ());
}

void Shader::setUniform(const char* name, const Vec4& v) const
{
	glUniform4f(getUniformLocation(name), v.getX(), v.getY(), v.getZ(), v.getW());
}

void Shader::setUniform(const char* name, const Mat4& v) const
{
	glUniformMatrix4fv(getUniformLocation(name), 1, false, v.getPointer());
}

void Shader::deleteShaders()
{
	for (unsigned int i = 0; i < m_shaders.size(); i++) {
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}
	m_shaders.clear();
}

unsigned int Shader::getGLShaderType(ShaderType::ShaderType type)
{
	switch (type)
	{
	case ShaderType::VERTEX: return GL_VERTEX_SHADER; break;
	case ShaderType::FRAGMENT: return GL_FRAGMENT_SHADER; break;
	case ShaderType::GEOMETRY: return GL_GEOMETRY_SHADER; break;
	case ShaderType::COMPUTE: return GL_COMPUTE_SHADER; break;
	}
	return 0;
}