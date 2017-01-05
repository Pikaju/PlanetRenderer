#include "Model.h"

#include <glew.h>

Model::Model() : m_vbo(0), m_ibo(0), m_vao(0), m_mode(GL_TRIANGLES), m_numIndices(0), m_indexType(GL_UNSIGNED_INT)
{
}

Model::~Model()
{
	cleanup();
}

void Model::init()
{
	cleanup();
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ibo);
	glGenVertexArrays(1, &m_vao);
}

void Model::cleanup()
{
	if (m_vbo != 0) {
		glDeleteBuffers(1, &m_vbo);
		m_vbo = 0;
	}
	if (m_ibo != 0) {
		glDeleteBuffers(1, &m_ibo);
		m_ibo = 0;
	}
	if (m_vao != 0) {
		glDeleteVertexArrays(1, &m_vao);
		m_vao = 0;
	}
}

void Model::setData(void* vertexData, unsigned int vertexDataSize, unsigned int* indexData, unsigned int numIndices, const VertexAttrib* attributes, unsigned int attributesSize)
{
	glBindVertexArray(m_vao);
	
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, vertexDataSize, vertexData, GL_STATIC_DRAW);

	unsigned int stride = 0;
	for (unsigned int i = 0; i < attributesSize / sizeof(VertexAttrib); i++) {
		stride += getGLTypeSize(attributes[i].getType()) * attributes[i].getAmount();
	}

	unsigned int pointer = 0;
	for (unsigned int i = 0; i < attributesSize / sizeof(VertexAttrib); i++) {
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, attributes[i].getAmount(), getGLType(attributes[i].getType()), attributes[i].getNormalized(), stride, (void*)pointer);
		pointer += getGLTypeSize(attributes[i].getType()) * attributes[i].getAmount();
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(unsigned int), indexData, GL_STATIC_DRAW);

	glBindVertexArray(0);
	
	m_numIndices = numIndices;
}

void Model::render() const
{
	glBindVertexArray(m_vao);
	glDrawElements(m_mode, m_numIndices, m_indexType, 0);
	glBindVertexArray(0);
}

unsigned int Model::getGLType(VertexAttribType::VertexAttribType type)
{
	switch (type) {
	case VertexAttribType::FLOAT: return GL_FLOAT; break;
	case VertexAttribType::UNSIGNED_BYTE: return GL_UNSIGNED_BYTE; break;
	}
	return 0;
}

unsigned int Model::getGLTypeSize(VertexAttribType::VertexAttribType type)
{
	switch (type) {
	case VertexAttribType::FLOAT: return 4; break;
	case VertexAttribType::UNSIGNED_BYTE: return 1; break;
	}
	return 0;
}