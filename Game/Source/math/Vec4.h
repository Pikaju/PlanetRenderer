#pragma once

#include "Vec3.h"

class Vec4
{
public:
	Vec4();
	Vec4(float v);
	Vec4(float x, float y, float z, float w);
	Vec4(const Vec3& v, float w);
	~Vec4();

	float length() const;

	void normalize();
	Vec4 normalized() const;

	float dot(const Vec4& v) const;

	inline float getX() const { return m_x; }
	inline float getY() const { return m_y; }
	inline float getZ() const { return m_z; }
	inline float getW() const { return m_w; }

	inline void setX(float x) { m_x = x; }
	inline void setY(float y) { m_y = y; }
	inline void setZ(float z) { m_z = z; }
	inline void setW(float w) { m_w = w; }
	
	inline void set(float x, float y, float z, float w) { m_x = x; m_y = y; m_z = z; m_w = w; }

	inline Vec3 getXYZ() const { return Vec3(m_x, m_y, m_z); }
	inline Vec3 toVec3() const { return getXYZ() / m_w; }

	inline Vec4 operator+(const Vec4& v) const { return Vec4(m_x + v.m_x, m_y + v.m_y, m_z + v.m_z, m_w + v.m_w); }
	inline Vec4 operator-(const Vec4& v) const { return Vec4(m_x - v.m_x, m_y - v.m_y, m_z - v.m_z, m_w - v.m_w); }
	inline Vec4 operator*(const Vec4& v) const { return Vec4(m_x * v.m_x, m_y * v.m_y, m_z * v.m_z, m_w * v.m_w); }
	inline Vec4 operator/(const Vec4& v) const { return Vec4(m_x / v.m_x, m_y / v.m_y, m_z / v.m_z, m_w / v.m_w); }

	inline Vec4 operator+(float v) const { return Vec4(m_x + v, m_y + v, m_z + v, m_w + v); }
	inline Vec4 operator-(float v) const { return Vec4(m_x - v, m_y - v, m_z - v, m_w - v); }
	inline Vec4 operator*(float v) const { return Vec4(m_x * v, m_y * v, m_z * v, m_w * v); }
	inline Vec4 operator/(float v) const { return Vec4(m_x / v, m_y / v, m_z / v, m_w / v); }

	inline void operator+=(const Vec4& v) { set(m_x + v.m_x, m_y + v.m_y, m_z + v.m_z, m_w + v.m_w); }
	inline void operator-=(const Vec4& v) { set(m_x - v.m_x, m_y - v.m_y, m_z - v.m_z, m_w - v.m_w); }
	inline void operator*=(const Vec4& v) { set(m_x * v.m_x, m_y * v.m_y, m_z * v.m_z, m_w * v.m_w); }
	inline void operator/=(const Vec4& v) { set(m_x / v.m_x, m_y / v.m_y, m_z / v.m_z, m_w / v.m_w); }

	inline void operator+=(float v) { set(m_x + v, m_y + v, m_z + v, m_w + v); }
	inline void operator-=(float v) { set(m_x - v, m_y - v, m_z - v, m_w - v); }
	inline void operator*=(float v) { set(m_x * v, m_y * v, m_z * v, m_w * v); }
	inline void operator/=(float v) { set(m_x / v, m_y / v, m_z / v, m_w / v); }
private:
	float m_x;
	float m_y;
	float m_z;
	float m_w;
};

