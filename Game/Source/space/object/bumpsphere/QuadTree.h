#pragma once

#include "../../../math/Vec3.h"
#include "../../../util/ThreadPool.h"

namespace QuadTreeDirection
{
	enum QuadTreeDirection
	{
		TOP = 0, BOTTOM, LEFT, RIGHT, FRONT, BACK
	};
}

class Chunk;

class QuadTree
{
public:
	QuadTree(QuadTreeDirection::QuadTreeDirection direction, float x = -1.0f, float y = -1.0f, float size = 2.0f);
	~QuadTree();

	void update(ThreadPool& threadPool, const Vec3& cameraPosition, float radius, float delta);
	void render();

	void createNodes();
	void deleteNodes();

	void createChunk();
	void deleteChunk();

	inline QuadTreeDirection::QuadTreeDirection getDirection() const { return m_direction; }
	inline float getX() const { return m_x; }
	inline float getY() const { return m_y; }
	inline float getSize() const { return m_size; }
protected:
	static void createNodesThread(void* quadTree);
	static void createChunkThread(void* quadTree);
private:
	QuadTree* m_nodes[4];
	
	QuadTreeDirection::QuadTreeDirection m_direction;
	float m_x;
	float m_y;
	float m_size;

	Chunk* m_chunk;
	Vec3 m_coordinates;
	bool m_visible;

	bool m_running;
};

