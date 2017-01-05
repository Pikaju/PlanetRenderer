#pragma once

#include <vector>

#include "../../../graphics/model/Model.h"
#include "../../../math/Vec2.h"
#include "../../../math/Vec3.h"

class QuadTree;

class Vertex
{
public:
	Vec3 m_position;
	Vec3 m_normal;
	Vec2 m_texcoord;
	Vertex(const Vec3& position = Vec3(), const Vec3& normal = Vec3(), const Vec2& texcoord = Vec2()) : m_position(position), m_normal(normal), m_texcoord(texcoord) {  }
};

class Chunk
{
public:
	Chunk(QuadTree* node, unsigned int size = 32);
	~Chunk();

	void update(float delta);
	void render();

	void generate();
	void createModel();

	Vec3 getCoordinates(int x, int y) const;
	Vec3 getHeightmapCoordinates(int x, int y) const;

	inline unsigned int getSize() const { return m_size; }
	inline bool isGenerated() const { return m_generated; }
	inline bool isModelCreated() const { return m_model != nullptr; }
protected:
	static Vec3 normalFromCorners(const Vec3& middle, const Vec3& v0, const Vec3& v1, const Vec3& v2, const Vec3& v3);
private:
	QuadTree* m_node;
	Model* m_model;
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
	float* m_heightmap;
	unsigned int m_size;
	bool m_generated;
};

