#include "Libs.h"
#include <iostream>
#include "Main.h"
#include "core/Camera.h"
#include "core/Shader.h"
#include "core/Mesh.h"
#include "core/Texture.h"
#include "core/Transform.h"
#include "BlockType.h"
#include "BlocksDataBase.cpp"
#include "Block.h"
#include "Libs.h"
#include "core/Input.h"
#include <vector>

#define HEIGHT 720
#define WIDTH 1280

GLFWwindow* window;
bool queueSpawn;

void spawnBlock(const Shader& shader, const uint16_t& type, const glm::vec3& pos, std::vector<Mesh*>& vector) {
	Vertex vertices[36];
	Block block = Block(type);
	
	for (int i = 0; i<36; i++)
		vertices[i] = Vertex(Vertices::blockVertices[i], BlocksDB::BLOCK_TYPES[type].m_texCoords[i]);

	Mesh* m = new Mesh(shader, vertices, sizeof(vertices) / sizeof(vertices[0]));
	
	m->getTransform()->setPos(pos);

	vector.push_back(m);
}

int main() {
	if (!initGlfw() || !initGl()) {
		std::cerr << "Error has occured during initialisation" << std::endl;
		return -1;
	}

	Shader shader("../res/shaders/defaultShader");
	Camera camera(glm::vec3(0,0,-5), 70, (float)WIDTH/(float)HEIGHT, 0.01f, 100.0f);
	Texture texture("../res/textures/test.png"); 
	texture.bind(0);
	std::vector<Mesh*> meshes;
	
	spawnBlock(shader, TYPE_COBBLESTONE, glm::vec3(0,0,0), meshes);

	float dt = 0;
	double lastFrame = glfwGetTime();
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		float moveDt = dt*10;

		if (Input::getKey(GLFW_KEY_W)) camera.move(glm::vec3(0,0, moveDt));
		if (Input::getKey(GLFW_KEY_S)) camera.move(glm::vec3(0,0,-moveDt));
		if (Input::getKey(GLFW_KEY_A)) camera.move(glm::vec3(moveDt,0,0));
		if (Input::getKey(GLFW_KEY_D)) camera.move(glm::vec3(-moveDt,0,0));
		
		if (Input::getPressedKey(GLFW_KEY_SPACE)) {
			std::cout << "Spawning a cube" << std::endl;
			spawnBlock(shader, TYPE_GRASS, camera.getPosition(), meshes);
		}

		if (queueSpawn) {
			spawnBlock(shader, TYPE_GRASS, camera.getPosition(), meshes);
			queueSpawn = false;
		}

		for (int m = 0; m<meshes.size(); m++)
			meshes[m]->draw(camera);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	
		double now = glfwGetTime();
		dt = now - lastFrame;
		lastFrame = now;
	}

	glfwTerminate();

	for (int m = 0; m<meshes.size(); m++)
		delete meshes[m];
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
	glfwSetKeyCallback(window, keyCallback);

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

	glClearColor(0.53f, 0.8f, 0.92f, 1);
	
	glViewport(0, 0, WIDTH, HEIGHT);

	return true;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		Input::setKey(key, true);

		if (key == GLFW_KEY_SPACE)
			queueSpawn = true;
	}

	else if (action == GLFW_RELEASE) {
		Input::setKey(key, false);
	}
}