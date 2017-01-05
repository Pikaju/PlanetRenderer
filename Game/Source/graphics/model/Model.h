#pragma once

namespace VertexAttribType
{
	enum VertexAttribType
	{
		FLOAT, UNSIGNED_BYTE
	};
}

class VertexAttrib
{
public:
	VertexAttrib(VertexAttribType::VertexAttribType type, unsigned int amount, bool normalized = false) : m_type(type), m_amount(amount), m_normalized(normalized) {  }

	inline VertexAttribType::VertexAttribType getType() const { return m_type; }
	inline int getAmount() const { return m_amount; }
	inline bool getNormalized() const { return m_normalized; }
private:
	VertexAttribType::VertexAttribType m_type;
	unsigned int m_amount;
	bool m_normalized;
};

class Model
{
public:
	Model();
	~Model();

	void init();
	void cleanup();

	void setData(void* vertexData, unsigned int vertexDataSize, unsigned int* indexData, unsigned int numIndices, const VertexAttrib* attributes, unsigned int attributesSize);

	void render() const;
protected:
	static unsigned int getGLType(VertexAttribType::VertexAttribType type);
	static unsigned int getGLTypeSize(VertexAttribType::VertexAttribType type);
private:
	unsigned int m_vbo;
	unsigned int m_ibo;
	unsigned int m_vao;

	unsigned int m_mode;

	unsigned int m_numIndices;
	unsigned int m_indexType;
};

