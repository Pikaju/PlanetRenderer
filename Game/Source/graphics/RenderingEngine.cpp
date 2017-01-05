#include "RenderingEngine.h"

#include <glew.h>

#include "../debug/Debug.h"

void RenderingEngine::init()
{
	if (glewInit() != GLEW_OK) {
		Debug::crash("Failed to intialize GLEW");
	}
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}

void RenderingEngine::cleanup()
{

}

void RenderingEngine::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}