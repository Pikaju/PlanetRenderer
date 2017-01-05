#pragma once

#include <vector>

#include "../../math/Vec2.h"
#include "../../math/Vec3.h"
#include "../../math/Vec4.h"
#include "../../math/Mat4.h"

namespace ShaderType
{
	enum ShaderType
	{
		VERTEX, FRAGMENT, GEOMETRY, COMPUTE
	};
}

class Shader
{
public:
	Shader();
	~Shader();

	void init();
	void cleanup();

	void addShader(const char* file, ShaderType::ShaderType type);
	void link();

	void enable();
	void disable();

	int getUniformLocation(const char* name) const;

	void setUniform(const char* name, int v) const;
	void setUniform(const char* name, float v) const;
	void setUniform(const char* name, const Vec2& v) const;
	void setUniform(const char* name, const Vec3& v) const;
	void setUniform(const char* name, const Vec4& v) const;
	void setUniform(const char* name, const Mat4& v) const;
protected:
	void deleteShaders();
	static unsigned int getGLShaderType(ShaderType::ShaderType type);
private:
	unsigned int m_program;
	std::vector<unsigned int> m_shaders;
};

