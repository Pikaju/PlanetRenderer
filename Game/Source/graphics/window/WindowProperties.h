#pragma once

class WindowProperties
{
public:
	WindowProperties(const char* title, int width, int height, bool vsync = true, bool resizable = true, bool fullscreen = false);
	~WindowProperties();

	inline const char* getTitle() const { return m_title; }
	inline int getWidth() const { return m_width; }
	inline int getHeight() const { return m_height; }
	inline bool getVSync() const { return m_vsync; }
	inline bool getResizable() const { return m_resizable; }
	inline bool getFullscreen() const { return m_fullscreen; }
private:
	const char* m_title;
	int m_width;
	int m_height;
	bool m_vsync;
	bool m_resizable;
	bool m_fullscreen;
};

