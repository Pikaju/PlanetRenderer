#include "Chunk.h"

#include "QuadTree.h"
#include "../../../util/Noise.h"

Chunk::Chunk(QuadTree* node, unsigned int size) : m_node(node), m_model(nullptr), m_vertices(), m_indices(), m_heightmap(new float[(size + 3) * (size + 3)]), m_size(size), m_generated(false)
{
	

}

Chunk::~Chunk()
{
	delete m_model;
	delete[] m_heightmap;
}

void Chunk::update(float delta)
{

}

void Chunk::render()
{
	if (m_model != nullptr) {
		m_model->render();
	}
}

void Chunk::generate()
{
	Noise noise(0);
	for (unsigned int x = 0; x < m_size + 3; x++) {
		for (unsigned int y = 0; y < m_size + 3; y++) {
			Vec3 coordinates = getCoordinates(x, y);
			float scale = 64.0f;
			float n = noise.octavesAbs(coordinates.getX(), coordinates.getY(), coordinates.getZ(), 16, scale, 0.42f);
			float b = noise.octaves(coordinates.getX(), coordinates.getY(), coordinates.getZ(), 2, scale * 0.125f, 0.5f) * 0.4f + 0.3f;
			m_heightmap[x + y * (m_size + 3)] = (1.0f + ((2.0f - n) / 128.0f * (b))) * 1024.0f;
			if (m_heightmap[x + y * (m_size + 3)] < 1024.0f) m_heightmap[x + y * (m_size + 3)] = 1024.0f;
		}
	}

	for (unsigned int x = 0; x < m_size + 3; x++) {
		for (unsigned int y = 0; y < m_size + 3; y++) {
			Vec3 position = getHeightmapCoordinates((int)x - 1, (int)y - 1);
			if (x == 0 || x == m_size + 2 || y == 0 || y == m_size + 2) {
				position *= 0.99f;
			}
			m_vertices.emplace_back(position, Vec3(), (Vec2((float)(x - 1) / (float)m_size, (float)(y - 1) / (float)m_size) * m_node->getSize() + Vec2(m_node->getX(), m_node->getY())) * 1024.0f);
		}
	}
	unsigned int index = -1;
	for (unsigned int x = 0; x < m_size + 3; x++) {
		for (unsigned int y = 0; y < m_size + 3; y++) {
			index++;
			if (x == 0 || y == 0 || x == m_size + 2 || y == m_size + 2) continue;
			int xx = x - 1;
			int yy = y - 1;
			Vec3 position = getHeightmapCoordinates((int)xx, (int)yy);
			Vec3 v0 = getHeightmapCoordinates((int)xx - 1, (int)yy);
			Vec3 v1 = getHeightmapCoordinates((int)xx, (int)yy - 1);
			Vec3 v2 = getHeightmapCoordinates((int)xx + 1, (int)yy);
			Vec3 v3 = getHeightmapCoordinates((int)xx, (int)yy + 1);
			m_vertices[index].m_normal = normalFromCorners(position, v0, v1, v2, v3);
		}
	}
	for (unsigned int x = 0; x < m_size + 2; x++) {
		for (unsigned int y = 0; y < m_size + 2; y++) {
			m_indices.push_back(x + y * (m_size + 3));
			m_indices.push_back(x + (y + 1) * (m_size + 3));
			m_indices.push_back((x + 1) + (y + 1) * (m_size + 3));

			m_indices.push_back(x + y * (m_size + 3));
			m_indices.push_back((x + 1) + (y + 1) * (m_size + 3));
			m_indices.push_back((x + 1) + y * (m_size + 3));
		}
	}

	m_generated = true;
}

void Chunk::createModel()
{
	std::vector<VertexAttrib> attributes;
	attributes.emplace_back(VertexAttribType::FLOAT, 3);
	attributes.emplace_back(VertexAttribType::FLOAT, 3);
	attributes.emplace_back(VertexAttribType::FLOAT, 2);

	if (m_model != nullptr) {
		delete m_model;
	}

	m_model = new Model();
	m_model->init();
	m_model->setData(m_vertices.data(), m_vertices.size() * sizeof(Vertex), m_indices.data(), m_indices.size(), attributes.data(), attributes.size() * sizeof(VertexAttrib));
}

Vec3 Chunk::getCoordinates(int x, int y) const
{
	float xx = (float)x / (float)m_size * m_node->getSize() + m_node->getX();
	float yy = (float)y / (float)m_size * m_node->getSize() + m_node->getY();
	Vec3 coordinate;
	switch (m_node->getDirection()) {
	case QuadTreeDirection::TOP: coordinate = Vec3(xx, 1.0f, yy); break;
	case QuadTreeDirection::BOTTOM: coordinate = Vec3(-xx, -1.0f, yy); break;
	case QuadTreeDirection::LEFT: coordinate = Vec3(-1.0f, xx, yy); break;
	case QuadTreeDirection::RIGHT: coordinate = Vec3(1.0f, -xx, yy); break;
	case QuadTreeDirection::FRONT: coordinate = Vec3(xx, yy, -1.0f); break;
	case QuadTreeDirection::BACK: coordinate = Vec3(-xx, yy, 1.0f); break;
	}
	coordinate.normalize();
	return coordinate;
}

Vec3 Chunk::getHeightmapCoordinates(int x, int y) const
{
	return getCoordinates(x, y) * m_heightmap[(x + 1) + (y + 1) * (m_size + 3)];
}

Vec3 Chunk::normalFromCorners(const Vec3& middle, const Vec3& v0, const Vec3& v1, const Vec3& v2, const Vec3& v3)
{
	Vec3 n0 = (v0 - middle).cross(v1 - middle).normalized();
	Vec3 n1 = (v1 - middle).cross(v2 - middle).normalized();
	Vec3 n2 = (v2 - middle).cross(v3 - middle).normalized();
	Vec3 n3 = (v3 - middle).cross(v0 - middle).normalized();
	return (n0 + n1 + n2 + n3) * 0.25f;
}