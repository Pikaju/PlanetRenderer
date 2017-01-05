#include "Input.h"

#include <glfw3.h>

#include "../graphics/window/Window.h"

Input::Input(Window* window) : m_window(window), m_keys(), m_buttons(), m_keyEvents(), m_buttonEvents(), m_x(0), m_y(0), m_lx(0), m_ly(0), m_dx(0), m_dy(0)
{
}

Input::~Input()
{
}

bool Input::isKeyDown(int key) const
{
	auto it = m_keys.find(key);
	if (it == m_keys.end()) return false;
	return it->second;
}

bool Input::getKeyEvent(int key, bool state) const
{
	auto it = m_keyEvents.find(key);
	if (it == m_keyEvents.end()) return false;
	return it->second == state;
}

bool Input::isButtonDown(int button) const
{
	auto it = m_buttons.find(button);
	if (it == m_buttons.end()) return false;
	return it->second;
}

bool Input::getButtonEvent(int button, bool state) const
{
	auto it = m_buttonEvents.find(button);
	if (it == m_buttonEvents.end()) return false;
	return it->second == state;
}

void Input::setMouseGrabbed(bool grabbed) const
{
	glfwSetInputMode(m_window->getGLFWWindow(), GLFW_CURSOR, grabbed ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}

bool Input::isMouseGrabbed() const
{
	return glfwGetInputMode(m_window->getGLFWWindow(), GLFW_CURSOR) == GLFW_CURSOR_DISABLED;
}

void Input::refresh()
{
	m_keyEvents.clear();
	m_buttonEvents.clear();
	
	m_dx = m_x - m_lx;
	m_dy = m_y - m_ly;
	m_lx = m_x;
	m_ly = m_y;
}

void Input::setKeyEvent(int key, bool state)
{
	m_keys[key] = state;
	m_keyEvents[key] = state;
}

void Input::setButtonEvent(int button, bool state)
{
	m_buttons[button] = state;
	m_buttonEvents[button] = state;
}

void Input::setMouseEvent(int x, int y)
{
	m_x = x;
	m_y = y;
}