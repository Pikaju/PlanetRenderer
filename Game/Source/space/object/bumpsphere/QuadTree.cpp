#include "QuadTree.h"

#include "Chunk.h"

QuadTree::QuadTree(QuadTreeDirection::QuadTreeDirection direction, float x, float y, float size) : m_direction(direction), m_x(x), m_y(y), m_size(size), m_chunk(nullptr), m_visible(true), m_running(false)
{
	for (unsigned int i = 0; i < 4; i++) {
		m_nodes[i] = nullptr;
	}
}

QuadTree::~QuadTree()
{
	deleteNodes();
	deleteChunk();
}

void QuadTree::update(ThreadPool& threadPool, const Vec3& cameraPosition, float radius, float delta)
{
	if (m_chunk != nullptr && m_chunk->isGenerated() && !m_chunk->isModelCreated()) {
		m_chunk->createModel();
		if (m_nodes[0] != nullptr) {
			deleteNodes();
		}
	}
	m_visible = m_coordinates.normalized().dot(cameraPosition.normalized()) > 0.5f;
	if (m_chunk != nullptr) {
		m_chunk->update(delta);
	}
	for (unsigned int i = 0; i < 4; i++) {
		if (m_nodes[i] != nullptr) {
			m_nodes[i]->update(threadPool, cameraPosition, radius, delta);
			if (m_chunk != nullptr && m_nodes[i]->m_chunk != nullptr && m_nodes[i]->m_chunk->isGenerated()) {
				deleteChunk();
			}
		}
	}

	const float r = radius * 4.0f;
	if (m_nodes[0] == nullptr && (m_coordinates - cameraPosition).length() < m_size * r && m_size * 128.0f >= 1.0f) {
		if (!threadPool.isSaturated() && !m_running) {
			m_running = true;
			threadPool.addTask(Task(createNodesThread, (void*)this));
		}
	}
	if (m_nodes[0] != nullptr && (m_coordinates - cameraPosition).length() > m_size * r) {
		if (!threadPool.isSaturated() && !m_running) {
			m_running = true;
			threadPool.addTask(Task(createChunkThread, (void*)this));
		}
	}
}

void QuadTree::render()
{
	if (m_chunk != nullptr) {
		m_chunk->render();
	}
	for (unsigned int i = 0; i < 4; i++) {
		if (m_nodes[i] != nullptr) {
			m_nodes[i]->render();
		}
	}
}

void QuadTree::createNodes()
{
	deleteNodes();
	for (unsigned int i = 0; i < 4; i++) {
		m_nodes[i] = new QuadTree(m_direction, m_x + ((i / 2) * m_size * 0.5f), m_y + ((i % 2) * m_size * 0.5f), m_size * 0.5f);
		m_nodes[i]->createChunk();
	}
}

void QuadTree::deleteNodes()
{
	if (m_running) return;
	for (unsigned int i = 0; i < 4; i++) {
		if (m_nodes[i] != nullptr) {
			delete m_nodes[i];
			m_nodes[i] = nullptr;
		}
	}
}

void QuadTree::createChunk()
{
	deleteChunk();
	m_chunk = new Chunk(this);
	m_chunk->generate();
	m_coordinates = m_chunk->getHeightmapCoordinates(m_chunk->getSize() / 2, m_chunk->getSize() / 2);
}

void QuadTree::deleteChunk()
{
	if (m_running) return;
	if (m_chunk != nullptr) {
		delete m_chunk;
		m_chunk = nullptr;
	}
}

void QuadTree::createNodesThread(void* quadTree)
{
	QuadTree* tree = (QuadTree*)quadTree;
	tree->createNodes();
	tree->m_running = false;
}

void QuadTree::createChunkThread(void* quadTree)
{
	QuadTree* tree = (QuadTree*)quadTree;
	tree->createChunk();
	tree->m_running = false;
}
