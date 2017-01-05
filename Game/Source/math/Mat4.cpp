#include "Mat4.h"

#include <xmemory>

Mat4::Mat4()
{
}

Mat4::~Mat4()
{
}

Mat4 Mat4::identity()
{
	Mat4 result;
	result.set(0, 0, 1.0f); result.set(1, 0, 0.0f); result.set(2, 0, 0.0f); result.set(3, 0, 0.0f);
	result.set(0, 1, 0.0f); result.set(1, 1, 1.0f); result.set(2, 1, 0.0f); result.set(3, 1, 0.0f);
	result.set(0, 2, 0.0f); result.set(1, 2, 0.0f); result.set(2, 2, 1.0f); result.set(3, 2, 0.0f);
	result.set(0, 3, 0.0f); result.set(1, 3, 0.0f); result.set(2, 3, 0.0f); result.set(3, 3, 1.0f);
	return result;
}

Mat4 Mat4::translation(float x, float y, float z)
{
	Mat4 result;
	result.set(0, 0, 1.0f); result.set(1, 0, 0.0f); result.set(2, 0, 0.0f); result.set(3, 0, x);
	result.set(0, 1, 0.0f); result.set(1, 1, 1.0f); result.set(2, 1, 0.0f); result.set(3, 1, y);
	result.set(0, 2, 0.0f); result.set(1, 2, 0.0f); result.set(2, 2, 1.0f); result.set(3, 2, z);
	result.set(0, 3, 0.0f); result.set(1, 3, 0.0f); result.set(2, 3, 0.0f); result.set(3, 3, 1.0f);
	return result;
}

Mat4 Mat4::rotation(float x, float y, float z, float angle)
{
	float sin = sinf(angle / 180.0f * 3.14159265f);
	float cos = cosf(angle / 180.0f * 3.14159265f);

	Mat4 result;
	result.set(0, 0, cos + x * x * (1.0f - cos)); result.set(1, 0, x * y * (1.0f - cos) - z * sin); result.set(2, 0, x * z * (1.0f - cos) + y * sin); result.set(3, 0, 0.0f);
	result.set(0, 1, y * x * (1.0f - cos) + z * sin); result.set(1, 1, cos + y * y * (1.0f - cos)); result.set(2, 1, y * x * (1.0f - cos) - x * sin); result.set(3, 1, 0.0f);
	result.set(0, 2, z * x * (1.0f - cos) - y * sin); result.set(1, 2, z * y * (1.0f - cos) + x * sin); result.set(2, 2, cos + z * z * (1.0f - cos)); result.set(3, 2, 0.0f);
	result.set(0, 3, 0.0f); result.set(1, 3, 0.0f); result.set(2, 3, 0.0f); result.set(3, 3, 1.0f);
	return result;
}

Mat4 Mat4::scale(float x, float y, float z)
{
	Mat4 result;
	result.set(0, 0, x); result.set(1, 0, 0.0f); result.set(2, 0, 0.0f); result.set(3, 0, 0.0f);
	result.set(0, 1, 0.0f); result.set(1, 1, y); result.set(2, 1, 0.0f); result.set(3, 1, 0.0f);
	result.set(0, 2, 0.0f); result.set(1, 2, 0.0f); result.set(2, 2, z); result.set(3, 2, 0.0f);
	result.set(0, 3, 0.0f); result.set(1, 3, 0.0f); result.set(2, 3, 0.0f); result.set(3, 3, 1.0f);
	return result;
}

Mat4 Mat4::lookat(const Vec3& right, const Vec3& up, const Vec3& forward)
{
	Mat4 result;
	result.set(0, 0, right.getX()); result.set(1, 0, right.getY()); result.set(2, 0, right.getZ()); result.set(3, 0, 0.0f);
	result.set(0, 1, up.getX()); result.set(1, 1, up.getY()); result.set(2, 1, up.getZ()); result.set(3, 1, 0.0f);
	result.set(0, 2, forward.getX()); result.set(1, 2, forward.getY()); result.set(2, 2, forward.getZ()); result.set(3, 2, 0.0f);
	result.set(0, 3, 0.0f); result.set(1, 3, 0.0f); result.set(2, 3, 0.0f); result.set(3, 3, 1.0f);
	return result;
}

Mat4 Mat4::perspective(float aspect, float fov, float near, float far)
{
	float tan = tanf(fov / 360.0f * 3.14159265f);
	Mat4 result;
	result.set(0, 0, 1.0f / (aspect * tan)); result.set(1, 0, 0.0f); result.set(2, 0, 0.0f); result.set(3, 0, 0.0f);
	result.set(0, 1, 0.0f); result.set(1, 1, 1.0f / tan); result.set(2, 1, 0.0f); result.set(3, 1, 0.0f);
	result.set(0, 2, 0.0f); result.set(1, 2, 0.0f); result.set(2, 2, (-near - far) / (near - far)); result.set(3, 2, (2.0f * far * near) / (near - far));
	result.set(0, 3, 0.0f); result.set(1, 3, 0.0f); result.set(2, 3, 1.0f); result.set(3, 3, 0.0f);
	return result;
}

Mat4 Mat4::ortho(float left, float right, float bottom, float top, float near, float far)
{
	Mat4 result;
	result.set(0, 0, 2.0f / (right - left)); result.set(1, 0, 0.0f); result.set(2, 0, 0.0f); result.set(3, 0, -(right + left) / (right - left));
	result.set(0, 1, 0.0f); result.set(1, 1, 2.0f / (top - bottom)); result.set(2, 1, 0.0f); result.set(3, 1, -(top + bottom) / (top - bottom));
	result.set(0, 2, 0.0f); result.set(1, 2, 0.0f); result.set(2, 2, -2.0f / (far - near)); result.set(3, 2, -(far + near) / (far - near));
	result.set(0, 3, 0.0f); result.set(1, 3, 0.0f); result.set(2, 3, 0.0f); result.set(3, 3, 1.0f);
	return result;
}

void Mat4::set(float* v)
{
	memcpy(m_v, v, sizeof(m_v));
}

Mat4 Mat4::operator*(const Mat4& v) const
{
	Mat4 result;
	for (unsigned int x = 0; x < 4; x++) {
		for (unsigned int y = 0; y < 4; y++) {
			result.set(x, y, get(x, 0) * v.get(0, y) + get(x, 1) * v.get(1, y) + get(x, 2) * v.get(2, y) + get(x, 3) * v.get(3, y));
		}
	}
	return result;
}

void Mat4::operator*=(const Mat4& v)
{
	set((*this * v).m_v);
}

Vec4 Mat4::operator*(const Vec4& v) const
{
	return Vec4(v.getX() * get(0, 0) + v.getY() * get(1, 0) + v.getZ() * get(2, 0) + v.getW() * get(3, 0),
				v.getX() * get(0, 1) + v.getY() * get(1, 1) + v.getZ() * get(2, 1) + v.getW() * get(3, 1),
				v.getX() * get(0, 2) + v.getY() * get(1, 2) + v.getZ() * get(2, 2) + v.getW() * get(3, 2),
				v.getX() * get(0, 3) + v.getY() * get(1, 3) + v.getZ() * get(2, 3) + v.getW() * get(3, 3));
}