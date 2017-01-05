#include "BumpSphere.h"

#include "QuadTree.h"

BumpSphere::BumpSphere(float radius) : m_radius(radius)
{
	for (unsigned int i = 0; i < 6; i++) {
		m_faces[i] = new QuadTree(QuadTreeDirection::QuadTreeDirection(i));
	}
}

BumpSphere::~BumpSphere()
{
	for (unsigned int i = 0; i < 6; i++) {
		delete m_faces[i];
	}
}

void BumpSphere::update(ThreadPool& threadPool, const Vec3& cameraPosition, float delta)
{
	for (unsigned int i = 0; i < 6; i++) {
		m_faces[i]->update(threadPool, cameraPosition, m_radius, delta);
	}
}

void BumpSphere::render()
{
	for (unsigned int i = 0; i < 6; i++) {
		m_faces[i]->render();
	}
}