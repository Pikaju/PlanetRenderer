#pragma once

class Vec3
{
public:
	Vec3();
	Vec3(float v);
	Vec3(float x, float y, float z);
	~Vec3();

	float length() const;

	void normalize();
	Vec3 normalized() const;

	float dot(const Vec3& v) const;
	Vec3 cross(const Vec3& v) const;

	inline float getX() const { return m_x; }
	inline float getY() const { return m_y; }
	inline float getZ() const { return m_z; }

	inline void setX(float x) { m_x = x; }
	inline void setY(float y) { m_y = y; }
	inline void setZ(float z) { m_z = z; }

	inline void set(float x, float y, float z) { m_x = x; m_y = y; m_z = z; }

	inline Vec3 inverse() const { return Vec3(-m_x, -m_y, -m_z); }

	inline Vec3 operator+(const Vec3& v) const { return Vec3(m_x + v.m_x, m_y + v.m_y, m_z + v.m_z); }
	inline Vec3 operator-(const Vec3& v) const { return Vec3(m_x - v.m_x, m_y - v.m_y, m_z - v.m_z); }
	inline Vec3 operator*(const Vec3& v) const { return Vec3(m_x * v.m_x, m_y * v.m_y, m_z * v.m_z); }
	inline Vec3 operator/(const Vec3& v) const { return Vec3(m_x / v.m_x, m_y / v.m_y, m_z / v.m_z); }

	inline Vec3 operator+(float v) const { return Vec3(m_x + v, m_y + v, m_z + v); }
	inline Vec3 operator-(float v) const { return Vec3(m_x - v, m_y - v, m_z - v); }
	inline Vec3 operator*(float v) const { return Vec3(m_x * v, m_y * v, m_z * v); }
	inline Vec3 operator/(float v) const { return Vec3(m_x / v, m_y / v, m_z / v); }

	inline void operator+=(const Vec3& v) { set(m_x + v.m_x, m_y + v.m_y, m_z + v.m_z); }
	inline void operator-=(const Vec3& v) { set(m_x - v.m_x, m_y - v.m_y, m_z - v.m_z); }
	inline void operator*=(const Vec3& v) { set(m_x * v.m_x, m_y * v.m_y, m_z * v.m_z); }
	inline void operator/=(const Vec3& v) { set(m_x / v.m_x, m_y / v.m_y, m_z / v.m_z); }

	inline void operator+=(float v) { set(m_x + v, m_y + v, m_z + v); }
	inline void operator-=(float v) { set(m_x - v, m_y - v, m_z - v); }
	inline void operator*=(float v) { set(m_x * v, m_y * v, m_z * v); }
	inline void operator/=(float v) { set(m_x / v, m_y / v, m_z / v); }
private:
	float m_x;
	float m_y;
	float m_z;
};

