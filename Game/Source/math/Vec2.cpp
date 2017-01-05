#include "Vec2.h"

#include <math.h>

Vec2::Vec2() : m_x(0.0f), m_y(0.0f)
{
}

Vec2::Vec2(float v) : m_x(v), m_y(v)
{
}

Vec2::Vec2(float x, float y) : m_x(x), m_y(y)
{
}

Vec2::~Vec2()
{
}

float Vec2::length() const
{
	return sqrtf(m_x * m_x + m_y * m_y);
}

void Vec2::normalize()
{
	float t = length();
	if (t == 0.0f) return;
	m_x /= t;
	m_y /= t;
}

Vec2 Vec2::normalized() const
{
	Vec2 v(*this);
	v.normalize();
	return v;
}

float Vec2::dot(const Vec2& v) const
{
	return m_x * v.m_x + m_y * v.m_y;
}