#include <vector>
#include <iostream>

#include "core/Libs.h"

#include "core/Camera.h"
#include "core/Shader.h"
#include "core/Mesh.h"
#include "core/Texture.h"
#include "core/Transform.h"
#include "core/Input.h"


#include "BlocksDataBase.cpp"
#include "Block.h"
#include "BlockType.h"
#include "Main.h"

#define HEIGHT 720
#define WIDTH 1280

GLFWwindow* window;
bool queueSpawn;
uint16_t* p_selectedBlock;

void spawnBlock(const Shader& shader, const uint16_t& type, const glm::vec3& pos, std::vector<Mesh*>& vector) {
	Vertex vertices[36];
	Block block = Block(type);
	
	for (int i = 0; i<36; i++)
		vertices[i] = Vertex(Vertices::blockVertices[i], BlocksDB::BLOCK_TYPES[type].m_texCoords[i]);

	Mesh* m = new Mesh(shader, vertices, sizeof(vertices) / sizeof(vertices[0]));
	
	m->getTransform()->setPos(pos);
	m->getTransform()->setScale(glm::vec3(0.2f, 0.2f, 0.2f));

	vector.push_back(m);
}

int main() {
	if (!initGlfw() || !initGl() || !initImGui()) {
		std::cerr << "Error has occured during initialisation" << std::endl;
		return -1;
	}

	uint16_t currentType = 0;
	p_selectedBlock = &currentType;
	Shader shader("res/shaders/defaultShader");
	Camera camera(glm::vec3(0,1,-5), 70, (float)WIDTH/(float)HEIGHT, 0.01f, 100.0f);
	Texture texture("res/textures/test.png"); 
	texture.bind(0);
	std::vector<Mesh*> meshes;
	
	spawnBlock(shader, currentType, glm::vec3(0,0,0), meshes);

	float entityMovement=0;
	float entityRotation = 0;
	float dt = 0;
	double lastFrame = glfwGetTime();
	glm::vec3 moveDir(0,0,0);
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		moveDir = glm::vec3(0,0,0);
		float moveDt = dt*10;
		
		if (Input::getKey(GLFW_KEY_W)) moveDir.z += 1;
		if (Input::getKey(GLFW_KEY_S)) moveDir.z -= 1;
		if (Input::getKey(GLFW_KEY_A)) moveDir.x += 1;
		if (Input::getKey(GLFW_KEY_D)) moveDir.x -= 1;

		camera.move(moveDir * moveDt);
		
		if (queueSpawn) {
			spawnBlock(shader, currentType, camera.getPosition(), meshes);
			queueSpawn = false;
		}

		for (int m = 0; m<meshes.size(); m++) {
			meshes[m]->draw(camera);
			meshes[m]->getTransform()->getPos().y = sinf(entityMovement)/5;
			
			meshes[m]->getTransform()->getRot().y = entityRotation;
			meshes[m]->getTransform()->getRot().x = entityRotation;
			meshes[m]->getTransform()->getRot().z = entityRotation;
		}
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	
		double now = glfwGetTime();
		dt = now - lastFrame;
		lastFrame = now;

		entityMovement += dt * 2;
		entityRotation += dt;
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

		switch (key) {
		case GLFW_KEY_SPACE:
			queueSpawn = true;
			break;
		
		case GLFW_KEY_1:
			*p_selectedBlock = 0;
			break;

		case GLFW_KEY_2:
			*p_selectedBlock = 1;
			break;

		case GLFW_KEY_3:
			*p_selectedBlock = 2;
			break;

		case GLFW_KEY_4:
			*p_selectedBlock = 3;
			break;
		}
	} else if (action == GLFW_RELEASE) {
		Input::setKey(key, false);
	}
}

bool initImGui() {
	return true;
}