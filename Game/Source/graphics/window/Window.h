#pragma once

#include "WindowProperties.h"
#include "../../io/Input.h"

struct GLFWwindow;

class Window
{
public:
	Window();
	~Window();

	void init(const WindowProperties& properties);
	void cleanup();

	void update();
	void swap() const;

	void use() const;

	void framebuffer() const;

	inline const Input& getInput() const { return m_input; }
	inline GLFWwindow* getGLFWWindow() { return m_window; }

	int getWidth() const;
	int getHeight() const;
	float getAspectRatio() const;

	bool isCloseRequested() const;
protected:
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void buttonCallback(GLFWwindow* window, int button, int action, int mods);
	static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
private:
	GLFWwindow* m_window;
	Input m_input;
};

