#include <vector>
#include <iostream>

#include "core/Libs.h"

#include "core/rendering/Camera.h"
#include "core/rendering/Shader.h"
#include "core/rendering/Mesh.h"
#include "core/rendering/Texture.h"
#include "core/Transform.h"
#include "core/Input.h"
#include "core/imgui/imgui.h"
#include "core/imgui/imgui_impl_glfw.h"
#include "core/imgui/imgui_impl_opengl3.h"

#include "BlocksContainer.cpp"
#include "Block.h"
#include "BlockType.h"
#include "Main.h"
#include "Chunk.h"
#include "World.h"

#define HEIGHT 720
#define WIDTH 1280

#define SENSITIVITY 0.1f

bool showDebug=true;
bool showCursor = false;

float entityRotation, entityMovement;
float moveSpeed=10;
float dt;
double lastMouseX=0, lastMouseY=0;

GLFWwindow* p_window;
Shader* p_shader;
Camera* p_camera;
World* p_world;

int main() {
	srand(time(NULL));

	if (!initGlfw() || !initGl() || !initImGui()) {
		std::cerr << "Error has occured during initialisation" << std::endl;
		return -1;
	}

	Shader shader("res/shaders/defaultShader");
	p_shader = &shader;
	
	Camera camera(glm::vec3(0,20,-5), 70, (float)WIDTH/(float)HEIGHT, 0.01f, 100.0f);
	p_camera = &camera;
	
	Texture texture("res/textures/test.png"); 
	texture.bind();

	World world;
	p_world = &world;

	float now=0, lastFrame=0;
	while (!glfwWindowShouldClose(p_window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		update();
		draw();

		glfwSwapBuffers(p_window);
		glfwPollEvents();
		
		now = glfwGetTime();
		dt = now - lastFrame;
		lastFrame = now;
	}

	glfwTerminate();
}

void draw() {
	p_world->draw(*p_shader, *p_camera);
	drawImGui();
}

void update() {
	glfwSetInputMode(p_window, GLFW_CURSOR, showCursor ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);

	glm::vec3 moveDir(0, 0, 0);
	float rot = 0, moveAmount = dt*moveSpeed;

	if (Input::getKey(GLFW_KEY_W)) moveDir += p_camera->getForward();
	if (Input::getKey(GLFW_KEY_S)) moveDir -= p_camera->getForward();
	if (Input::getKey(GLFW_KEY_A)) moveDir += p_camera->getLeft();
	if (Input::getKey(GLFW_KEY_D)) moveDir += p_camera->getRight();
	if (Input::getKey(GLFW_KEY_SPACE)) moveDir += glm::vec3(0, 1, 0);
	if (Input::getKey(GLFW_KEY_LEFT_SHIFT)) moveDir -= glm::vec3(0, 1, 0);

	p_camera->move(moveDir * moveAmount);
	
	entityMovement += dt * 2;
	entityRotation += dt;
}

void drawImGui() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	if (showDebug) {
		ImGui::Begin("Debug");

		if (ImGui::CollapsingHeader("Stats", ImGuiTreeNodeFlags_DefaultOpen)) {
			
			ImGui::Text("Camera pos: x:%.4g, y:%.4g, z:%.4g", p_camera->getPosition().x, p_camera->getPosition().y, p_camera->getPosition().z);
			ImGui::Text("Camera forward: x:%.4g, y:%.4g, z:%.4g", p_camera->getForward().x, p_camera->getForward().y, p_camera->getForward().z);
			ImGui::Text("Yaw: %.4g, Pitch:%.4g", p_camera->m_yaw, p_camera->m_pitch);
			
			if (ImGui::CollapsingHeader("Performance", ImGuiTreeNodeFlags_DefaultOpen)) {
				ImGui::Text("Fps: %.4g", 1.0f/dt);
				ImGui::Text("Frame delta: %f", dt);
				//ImGui::Text("Chunks count: %u", p_chunks->size());
			}
		}

		if (ImGui::CollapsingHeader("Variables", ImGuiTreeNodeFlags_DefaultOpen)) {
			ImGui::DragFloat("Move Speed", &moveSpeed, 1, 1, 100);
		}

		ImGui::End();
	}

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void windowSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	p_camera->recalculatePerspective(width, height);
}

void mouseCallback(GLFWwindow* window, double x, double y) {
	float xOffset = x - lastMouseX;
	float yOffset = lastMouseY - y;

	lastMouseX = x;
	lastMouseY = y;

	if (glfwGetInputMode(p_window, GLFW_CURSOR) != GLFW_CURSOR_DISABLED)
		return;

	xOffset *= SENSITIVITY;
	yOffset *= SENSITIVITY;

	p_camera->rotate(xOffset, yOffset);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		Input::setKey(key, true);

		switch (key) {
		case GLFW_KEY_ESCAPE:
			showCursor = !showCursor;
			break;

		case GLFW_KEY_TAB:
			showDebug = !showDebug;
			break;
		}
	} else if (action == GLFW_RELEASE) {
		Input::setKey(key, false);
	}
}

bool initGlfw() {
	if (!glfwInit()) {
		std::cerr << "Couldn't initialize the GLFW." << std::endl;
		return false;
	}

	p_window = glfwCreateWindow(WIDTH, HEIGHT, "Rotthin's Sandbox", NULL, NULL);
	if (!p_window) {
		std::cerr << "Couldn't create the window." << std::endl;
		return false;
	}
	
	glfwGetCursorPos(p_window, &lastMouseX, &lastMouseY);

	glfwSetCursorPosCallback(p_window, mouseCallback);
	glfwSetWindowSizeCallback(p_window, windowSizeCallback);
	glfwSetKeyCallback(p_window, keyCallback);

	glfwMakeContextCurrent(p_window);

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
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	return true;
}

bool initImGui() {
	if (!IMGUI_CHECKVERSION())
		return false;

	auto context = ImGui::CreateContext();
	ImGui::SetCurrentContext(context);

	ImGuiIO& io = ImGui::GetIO();

	ImGui_ImplGlfw_InitForOpenGL(p_window, true);
	ImGui_ImplOpenGL3_Init("#version 130");

	return true;
}