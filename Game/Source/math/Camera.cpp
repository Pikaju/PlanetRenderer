#include "Camera.h"


Camera::Camera(const Vec3& position, const Vec3& rotation) : m_position(position), m_forward(0.0f, 0.0f, 1.0f), m_up(0.0f, 1.0f, 0.0f), m_right(1.0f, 0.0f, 0.0f)
{
}

Camera::~Camera()
{
}

void Camera::debugUpdate(const Input& input, float delta)
{
	if (input.isButtonDown(GLFW_MOUSE_BUTTON_LEFT)) input.setMouseGrabbed(true);
	if (input.isKeyDown(GLFW_KEY_ESCAPE)) input.setMouseGrabbed(false);

	if (input.isMouseGrabbed()) {
		const float sensitivity = 0.125f;
		float dx = input.getDX() * sensitivity;
		float dy = input.getDY() * sensitivity;
		if (dy != 0) {
			m_forward = (Mat4::rotation(m_right, dy) * Vec4(m_forward, 1.0)).getXYZ().normalized();
			m_up = m_forward.cross(m_right).normalized();
		}
		if (dx != 0) {
			m_forward = (Mat4::rotation(m_up, dx) * Vec4(m_forward, 1.0)).getXYZ().normalized();
			m_right = m_up.cross(m_forward).normalized();
		}
	}

	Vec3 direction;
	if (input.isKeyDown(GLFW_KEY_W)) direction.setZ(direction.getZ() + 1.0f);
	if (input.isKeyDown(GLFW_KEY_S)) direction.setZ(direction.getZ() - 1.0f);
	if (input.isKeyDown(GLFW_KEY_A)) direction.setX(direction.getX() - 1.0f);
	if (input.isKeyDown(GLFW_KEY_D)) direction.setX(direction.getX() + 1.0f);
	if (input.isKeyDown(GLFW_KEY_SPACE)) direction.setY(direction.getY() + 1.0f);
	if (input.isKeyDown(GLFW_KEY_LEFT_SHIFT)) direction.setY(direction.getY() - 1.0f);
	direction.normalize();

	float speed = delta * 1.0f;
	if (input.isKeyDown(GLFW_KEY_LEFT_CONTROL)) speed *= 8.0f;
	if (input.isKeyDown(GLFW_KEY_LEFT_ALT)) speed *= 32.0f;

	m_position += (m_right * direction.getX() + m_up * direction.getY() + m_forward * direction.getZ()) * speed;
}

Mat4 Camera::getViewMatrix() const
{
	Mat4 rotation = Mat4::lookat(m_right, m_up, m_forward);
	Mat4 translation = Mat4::translation(m_position.inverse());
	return translation * rotation;
}