#pragma once

#include "../../../math/Vec3.h"
#include "../../../util/ThreadPool.h"

class QuadTree;

class BumpSphere
{
public:
	BumpSphere(float radius);
	~BumpSphere();

	void update(ThreadPool& threadPool, const Vec3& cameraPosition, float delta);
	void render();
private:
	QuadTree* m_faces[6];
	float m_radius;
};

