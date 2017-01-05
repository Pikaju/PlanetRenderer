#include "WindowProperties.h"


WindowProperties::WindowProperties(const char* title, int width, int height, bool vsync, bool resizable, bool fullscreen) : m_title(title), m_width(width), m_height(height), m_vsync(vsync), m_resizable(resizable), m_fullscreen(fullscreen)
{
}

WindowProperties::~WindowProperties()
{
}
