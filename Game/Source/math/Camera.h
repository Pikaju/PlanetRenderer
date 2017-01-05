#pragma once

#include "Vec3.h"
#include "Mat4.h"
#include "../io/Input.h"

class Camera
{
public:
	Camera(const Vec3& position = Vec3(), const Vec3& rotation = Vec3());
	~Camera();

	void debugUpdate(const Input& input, float delta);

	Mat4 getViewMatrix() const;

	inline const Vec3& getPosition() const { return m_position; }
	inline const Vec3& getForward() const { return m_forward; }
private:
	Vec3 m_position;
	Vec3 m_forward;
	Vec3 m_up;
	Vec3 m_right;
};

