#include "Vec4.h"

#include <math.h>

Vec4::Vec4() : m_x(0.0f), m_y(0.0f), m_z(0.0f), m_w(0.0f)
{
}

Vec4::Vec4(float v) : m_x(v), m_y(v), m_z(v), m_w(v)
{
}

Vec4::Vec4(float x, float y, float z, float w) : m_x(x), m_y(y), m_z(z), m_w(w)
{
}

Vec4::Vec4(const Vec3& v, float w) : m_x(v.getX()), m_y(v.getY()), m_z(v.getZ()), m_w(w)
{
}

Vec4::~Vec4()
{
}

float Vec4::length() const
{
	return sqrtf(m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w);
}

void Vec4::normalize()
{
	float t = length();
	if (t == 0.0f) return;
	m_x /= t;
	m_y /= t;
	m_z /= t;
	m_w /= t;
}

Vec4 Vec4::normalized() const
{
	Vec4 v(*this);
	v.normalize();
	return v;
}

float Vec4::dot(const Vec4& v) const
{
	return m_x * v.m_x + m_y * v.m_y + m_z * v.m_z + m_w * v.m_w;
}