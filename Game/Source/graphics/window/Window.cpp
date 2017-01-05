#include "Window.h"

#include <glew.h>
#include <glfw3.h>

#include "../../debug/Debug.h"

Window::Window() : m_window(nullptr), m_input(this)
{
}

Window::~Window()
{
	cleanup();
}

void Window::init(const WindowProperties& properties)
{
	cleanup();
	if (!glfwInit()) {
		Debug::crash("Failed to initialize GLFW");
	}
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	
	m_window = glfwCreateWindow(properties.getWidth(), properties.getHeight(), properties.getTitle(), properties.getFullscreen() ? monitor : nullptr, nullptr);
	if (m_window == nullptr) {
		Debug::crash("Failed to create GLFW window");
		cleanup();
	}
	glfwSetWindowUserPointer(m_window, this);
	glfwSetKeyCallback(m_window, keyCallback);
	glfwSetMouseButtonCallback(m_window, buttonCallback);
	glfwSetCursorPosCallback(m_window, mouseCallback);

	int x = mode->width / 2 - properties.getWidth() / 2;
	int y = mode->height / 2 - properties.getHeight() / 2;
	glfwSetWindowPos(m_window, x, y);

	use();
	glfwSwapInterval(properties.getVSync() ? 1 : 0);
}

void Window::cleanup()
{
	if (m_window != nullptr) {
		glfwDestroyWindow(m_window);
		m_window = nullptr;
	}
	glfwTerminate();
}

void Window::update()
{
	m_input.refresh();
	glfwPollEvents();
}

void Window::swap() const
{
	glfwSwapBuffers(m_window);
}

void Window::use() const
{
	glfwMakeContextCurrent(m_window);
}

void Window::framebuffer() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	int width;
	int height;
	glfwGetFramebufferSize(m_window, &width, &height);
	glViewport(0, 0, width, height);
}


int Window::getWidth() const
{
	int width;
	int height;
	glfwGetFramebufferSize(m_window, &width, &height);
	return width;
}

int Window::getHeight() const
{
	int width;
	int height;
	glfwGetFramebufferSize(m_window, &width, &height);
	return height;
}

float Window::getAspectRatio() const
{
	int width;
	int height;
	glfwGetFramebufferSize(m_window, &width, &height);
	return (float)width / (float)height;
}

bool Window::isCloseRequested() const
{
	return glfwWindowShouldClose(m_window) != 0;
}

void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Window* w = (Window*)glfwGetWindowUserPointer(window);
	w->m_input.setKeyEvent(key, action != GLFW_RELEASE);
}

void Window::buttonCallback(GLFWwindow* window, int button, int action, int mods)
{
	Window* w = (Window*)glfwGetWindowUserPointer(window);
	w->m_input.setButtonEvent(button, action != GLFW_RELEASE);
}

void Window::mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	Window* w = (Window*)glfwGetWindowUserPointer(window);
	w->m_input.setMouseEvent((int)xpos, (int)ypos);
}