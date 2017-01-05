#pragma once

#include "Vec3.h"
#include "Vec4.h"

class Mat4
{
private:
	Mat4();
public:
	~Mat4();

	static Mat4 identity();

	static Mat4 translation(float x, float y, float z);
	static Mat4 rotation(float x, float y, float z, float angle);
	static Mat4 scale(float x, float y, float z);
	static Mat4 lookat(const Vec3& right, const Vec3& up, const Vec3& forward);

	inline static Mat4 translation(const Vec3& v) { return translation(v.getX(), v.getY(), v.getZ()); }
	inline static Mat4 rotation(const Vec3& axis, float angle) { return rotation(axis.getX(), axis.getY(), axis.getZ(), angle); }
	inline static Mat4 scale(const Vec3& v) { return scale(v.getX(), v.getY(), v.getZ()); }

	static Mat4 perspective(float aspect, float fov, float near, float far);
	static Mat4 ortho(float left, float right, float bottom, float top, float near, float far);

	inline float get(int x, int y) const { return m_v[x * 4 + y]; }
	inline void set(int x, int y, float v) { m_v[x * 4 + y] = v; }

	inline const float* getPointer() const { return m_v; }

	void set(float* v);
	
	Mat4 operator*(const Mat4& v) const;
	void operator*=(const Mat4& v);

	Vec4 operator*(const Vec4& v) const;
private:
	float m_v[16];
};

