
#include "graphics/model/Model.h"
#include "graphics/shader/Shader.h"
#include "graphics/RenderingEngine.h"
#include "graphics/window/Window.h"
#include "graphics/texture/Texture.h"
#include "math/Vec3.h"
#include "math/Camera.h"
#include "debug/Log.h"
#include "util/ThreadPool.h"

#include <glfw3.h>
#include <string>

#include "space/object/bumpsphere/BumpSphere.h"

int main()
{
	Window window;
	window.init(WindowProperties("Game", 1280, 720, true, true, false));
	RenderingEngine::init();

	VertexAttrib attributes[] = {
		{ VertexAttribType::FLOAT, 3 }
	};

	Vec3 vertices[] = {
		{ -1.0f, -1.0f, -1.0f },
		{ -1.0f, -1.0f, 1.0f },
		{ 1.0f, -1.0f, 1.0f },
		{ 1.0f, -1.0f, -1.0f }
	};

	unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3
	};

	Model model;
	model.init();
	model.setData(vertices, sizeof(vertices), indices, sizeof(indices) / sizeof(unsigned int), attributes, sizeof(attributes));

	Shader shader;
	shader.init();
	shader.addShader("Resources/shaders/Planet.vert", ShaderType::VERTEX);
	shader.addShader("Resources/shaders/Planet.frag", ShaderType::FRAGMENT);
	shader.link();

	Camera camera(Vec3(0.0f, 0.0f, -1030.0f));

	BumpSphere sphere(1024.0f);
	Texture grass;
	grass.load("Resources/textures/grass.png");
	Texture rock;
	rock.load("Resources/textures/rock.jpg");
	Texture snow;
	snow.load("Resources/textures/snow.jpg");

	grass.bind(0);
	rock.bind(1);
	snow.bind(2);

	ThreadPool threadPool;
	threadPool.startThreads(6);

	float currentTime = 0.0f;
	float lastTime = (float)glfwGetTime();
	float delta = 0.0f;
	float timer = 0.0f;
	unsigned int frames = 0;

	while (!window.isCloseRequested()) {
		currentTime = (float)glfwGetTime();
		delta = currentTime - lastTime;
		timer += delta;
		lastTime = currentTime;

		camera.debugUpdate(window.getInput(), delta);

		window.framebuffer();
		RenderingEngine::clear();

		//Mat4 projectionMatrix = Mat4::ortho(0.0f, 16.0f, 9.0f, 0.0f, -1.0f, 1.0f);
		Mat4 projectionMatrix = Mat4::perspective(window.getAspectRatio(), 90.0f, 0.125f, 16384.0f);
		Mat4 modelMatrix = Mat4::rotation(0.0f, 1.0f, 0.0f, currentTime * 0.0f);
		sphere.update(threadPool, (modelMatrix * Vec4(camera.getPosition(), 1.0f)).getXYZ(), delta);

		shader.enable();
		shader.setUniform("modelMatrix", modelMatrix);
		shader.setUniform("mvpMatrix", modelMatrix * camera.getViewMatrix() * projectionMatrix);
		shader.setUniform("textureGrass", 0);
		shader.setUniform("textureRock", 1);
		shader.setUniform("textureSnow", 2);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		sphere.render();
		shader.disable();

		window.update();
		window.swap();

		frames++;
		if (timer >= 1.0f) {
			timer -= 1.0f;
			Log::log((std::to_string(frames) + "fps").c_str());
			frames = 0;
		}
	}
	threadPool.stopThreads();

	RenderingEngine::cleanup();
	window.cleanup();
	return 0;
}