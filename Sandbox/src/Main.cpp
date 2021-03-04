#include "Libs.h"
#include <iostream>
#include "Main.h"
#include "Camera.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"

#define HEIGHT 720
#define WIDTH 1280

GLFWwindow* window;

int main() {
	if (!initGlfw() || !initGl()) {
		std::cerr << "Error has occured during initialisation" << std::endl;
		return -1;
	}

	Vertex vertices[] = {
		// Front
		Vertex(glm::vec3(-1,-1, -1),glm::vec2(0, 0)),               // bottom left
		Vertex(glm::vec3(-1, 1, -1),glm::vec2(0, 1)),	             // top left
		Vertex(glm::vec3( 1, 1, -1),glm::vec2(1.f/3.f, 1)),       // top right

		Vertex(glm::vec3( 1, 1,-1),glm::vec2(1.f/3.f, 1)),       // top right
		Vertex(glm::vec3( 1,-1,-1),glm::vec2(1.f/3.f, 0)),        // bottom right
		Vertex(glm::vec3(-1,-1,-1),glm::vec2(0, 0)),               // bottom left

		// Back
		Vertex(glm::vec3( 1,  1,  1),glm::vec2(1.f/3.f, 1)),      // top right
		Vertex(glm::vec3(-1,  1,  1),glm::vec2(0, 1)),	         // top left
		Vertex(glm::vec3(-1, -1,  1),glm::vec2(0, 0)),              // bottom left

		Vertex(glm::vec3(-1, -1,  1),glm::vec2(0, 0)),              // bottom left
		Vertex(glm::vec3( 1, -1,  1),glm::vec2(1.f/3.f, 0)),       // bottom right
		Vertex(glm::vec3( 1,  1,  1),glm::vec2(1.f/3.f, 1)),		 // top right

		// Left
		Vertex(glm::vec3(-1, 1, 1),  glm::vec2(0, 1)),	             // top left
		Vertex(glm::vec3(-1, 1,-1),  glm::vec2(1.f/3.f, 1)),	         // top right
		Vertex(glm::vec3(-1,-1, 1),	 glm::vec2(0,0)),				 // bottom left

		Vertex(glm::vec3(-1, 1,-1),  glm::vec2(1.f/3.f, 1)),			 // top right
		Vertex(glm::vec3(-1,-1,-1),  glm::vec2(1.f/3.f, 0)),			 // bottom right
		Vertex(glm::vec3(-1,-1, 1),  glm::vec2(0, 0)),	             // bottom left

		// Right
		Vertex(glm::vec3(1, 1, -1),  glm::vec2(1.f/3.f, 1)),	         // top right
		Vertex(glm::vec3(1, 1, 1),   glm::vec2(0, 1)),	             // top left
		Vertex(glm::vec3(1,-1, 1),   glm::vec2(0, 0)),	             // bottom left

		Vertex(glm::vec3(1, -1, 1),  glm::vec2(0, 0)),	             // bottom left
		Vertex(glm::vec3(1, -1, -1), glm::vec2(1.f/3.f, 0)),	     // bottom right
		Vertex(glm::vec3(1, 1, -1),  glm::vec2(1.f/3.f, 1)),	         // top right

		// Top
		Vertex(glm::vec3(-1, 1, -1), glm::vec2(1.f/3.f, 0)),	     // bottom left
		Vertex(glm::vec3(-1, 1, 1),  glm::vec2(1.f/3.f, 1)),	         // top left
		Vertex(glm::vec3(1,  1, 1),  glm::vec2(2.f/3.f, 1)),	         // top right

		Vertex(glm::vec3(1, 1, 1),   glm::vec2(2.f/3.f, 1)),	         // top right
		Vertex(glm::vec3(1, 1, -1),  glm::vec2(2.f/3.f, 0)),	         // bottom right
		Vertex(glm::vec3(-1, 1, -1), glm::vec2(1.f/3.f, 0)),	     // bottom left

		// Bottom
		Vertex(glm::vec3(-1, -1, 1), glm::vec2(2.f/3.f, 0)),	     // bottom left
		Vertex(glm::vec3(-1, -1, -1),glm::vec2(2.f/3.f, 1)),	     // top left
		Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 1)),				 // top right

		Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 1)),	             // top right
		Vertex(glm::vec3(1, -1, 1),  glm::vec2(2.f/3.f, 1)),			 // bottom right
		Vertex(glm::vec3(-1, -1, 1), glm::vec2(2.f/3.f, 0)),		 // bottom left
	};

	Camera camera(glm::vec3(0,0,-5), 70, (float)WIDTH/(float)HEIGHT, 0.01f, 100.0f);
	Mesh triangle(vertices, sizeof(vertices)/sizeof(vertices[0]));
	Shader shader("../res/shaders/defaultShader");
	Texture texture("../res/textures/test.png");
	Transform transform;

	float dt = 0;
	double lastFrame = glfwGetTime();
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		transform.getRot().x += dt;
		transform.getRot().y += dt;
		transform.getRot().z += dt;

		shader.bind();
		texture.bind(0);
		shader.update(transform, camera);
		triangle.draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	
		double now = glfwGetTime();
		dt = now - lastFrame;
		lastFrame = now;
	}

	glfwTerminate();
}

void windowSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

bool initGlfw() {
	if (!glfwInit()) {
		std::cerr << "Couldn't initialize the GLFW." << std::endl;
		return false;
	}

	window = glfwCreateWindow(WIDTH, HEIGHT, "Rotthin's Sandbox", NULL, NULL);
	if (!window) {
		std::cerr << "Couldn't create the window." << std::endl;
		return false;
	}

	glfwSetWindowSizeCallback(window, windowSizeCallback);

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	return true;
}

bool initGl() {
	if (glewInit() != GLEW_OK) {
		std::cerr << "Couldn't initialize the GLEW." << std::endl;
		return false;
	}

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glClearColor(0, 0.2f, 1, 1);
	
	glViewport(0, 0, WIDTH, HEIGHT);

	return true;
}