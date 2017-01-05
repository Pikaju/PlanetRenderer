#pragma once

class Vec2
{
public:
	Vec2();
	Vec2(float v);
	Vec2(float x, float y);
	~Vec2();

	float length() const;

	void normalize();
	Vec2 normalized() const;

	float dot(const Vec2& v) const;

	inline float getX() const { return m_x; }
	inline float getY() const { return m_y; }

	inline void setX(float x) { m_x = x; }
	inline void setY(float y) { m_y = y; }

	inline void set(float x, float y) { m_x = x; m_y = y; }

	inline Vec2 operator+(const Vec2& v) const { return Vec2(m_x + v.m_x, m_y + v.m_y); }
	inline Vec2 operator-(const Vec2& v) const { return Vec2(m_x - v.m_x, m_y - v.m_y); }
	inline Vec2 operator*(const Vec2& v) const { return Vec2(m_x * v.m_x, m_y * v.m_y); }
	inline Vec2 operator/(const Vec2& v) const { return Vec2(m_x / v.m_x, m_y / v.m_y); }

	inline Vec2 operator+(float v) const { return Vec2(m_x + v, m_y + v); }
	inline Vec2 operator-(float v) const { return Vec2(m_x - v, m_y - v); }
	inline Vec2 operator*(float v) const { return Vec2(m_x * v, m_y * v); }
	inline Vec2 operator/(float v) const { return Vec2(m_x / v, m_y / v); }

	inline void operator+=(const Vec2& v) { set(m_x + v.m_x, m_y + v.m_y); }
	inline void operator-=(const Vec2& v) { set(m_x - v.m_x, m_y - v.m_y); }
	inline void operator*=(const Vec2& v) { set(m_x * v.m_x, m_y * v.m_y); }
	inline void operator/=(const Vec2& v) { set(m_x / v.m_x, m_y / v.m_y); }

	inline void operator+=(float v) { set(m_x + v, m_y + v); }
	inline void operator-=(float v) { set(m_x - v, m_y - v); }
	inline void operator*=(float v) { set(m_x * v, m_y * v); }
	inline void operator/=(float v) { set(m_x / v, m_y / v); }
private:
	float m_x;
	float m_y;
};

