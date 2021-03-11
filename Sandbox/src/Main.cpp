#include <vector>
#include <iostream>
#include <filesystem>

#include "core/Libs.h"

#include "core/render/Camera.h"
#include "core/render/Shader.h"
#include "core/render/Mesh.h"
#include "core/render/Texture.h"
#include "core/Transform.h"
#include "core/Input.h"
#include "core/imgui/imgui.h"
#include "core/imgui/imgui_impl_glfw.h"
#include "core/imgui/imgui_impl_opengl3.h"

#include "BlocksContainer.h"
#include "Block.h"
#include "BlockType.h"
#include "Main.h"
#include "Chunk.h"
#include "World.h"
#include "Player.h"

#define START_POS glm::vec3(0, 20, 0)

#define HEIGHT 1080
#define WIDTH 1920
#define SENSITIVITY 0.1f
#define MOVE_SPEED 10

int width = WIDTH, height = HEIGHT;

bool showGui = true, showDebug = true, showCursor = false, keepFlying = false;

float moveSpeed = 10;
float dt;
double lastMouseX = 0, lastMouseY = 0;

ImGuiContext* p_imguiContext;
GLFWwindow* p_window;
Shader* p_shader;
Shader* p_crosshairShader;
Player* p_player;
World* p_world;
Texture* p_tex;

std::vector<std::string> texturePacks;

int main() {
	if (!init()) {
		clear();
		return -1;
	}

	float now = 0, lastFrame = 0;
	/*Main loop */
	while (!glfwWindowShouldClose(p_window)) {
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		update();
		draw();
		
		glfwSwapBuffers(p_window);

		/* Calculate delta between frames. */
		now = (float)glfwGetTime();
		dt = now - lastFrame;
		lastFrame = now; 
	}
	
	clear();
	return 0;
}

void draw() {
	p_world->draw(*p_shader, p_player->getCamera());
	drawImGui(); 
}

void update() {
	glfwSetInputMode(p_window, GLFW_CURSOR, showCursor ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
	
	glm::vec3 moveDir(0, 0, 0);
	glm::vec3 forward = glm::normalize(glm::vec3(p_player->getCamera().getForward().x, 0, p_player->getCamera().getForward().z));
	glm::vec3 up = glm::vec3(0,1,0);
	glm::vec3 left = p_player->getCamera().getLeft();

	if (Input::getKey(GLFW_KEY_W) || keepFlying) moveDir += forward;
	if (Input::getKey(GLFW_KEY_S)) moveDir -= forward;
	if (Input::getKey(GLFW_KEY_A)) moveDir += left;
	if (Input::getKey(GLFW_KEY_D)) moveDir -= left;
	if (Input::getKey(GLFW_KEY_SPACE)) moveDir += glm::vec3(0, 1, 0);
	if (Input::getKey(GLFW_KEY_LEFT_SHIFT)) moveDir -= up;
	
	if(glm::length(moveDir) > 0){
		p_player->setTargetVelocity(glm::normalize(moveDir) * moveSpeed * dt);
	} else {
		p_player->setTargetVelocity(glm::vec3(0));
	}
	
	p_player->update(dt);
	
	p_world->checkViewDistance(p_player->getCamera());
}

void drawImGui() {
	if (!showGui) return;

	/* Start new frame */
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	/* Debug */
	if (showDebug) {
		ImGui::Begin("Debug");
		/* Stats */
		if (ImGui::CollapsingHeader("Stats", ImGuiTreeNodeFlags_DefaultOpen)) {
			if (ImGui::CollapsingHeader("Performance", ImGuiTreeNodeFlags_DefaultOpen)) {
				ImGui::Text("Fps: %.4g", 1.0f/dt);
				ImGui::Text("Frame delta: %f", dt);
				ImGui::Text("Chunk count: %u", p_world->m_chunks.size());
			}

			ImGui::Text("Player pos: x:%f, y:%f, z:%f", p_player->getPosition().x, p_player->getPosition().y, p_player->getPosition().z);
			ImGui::Text("Vel: x:%f, y:%f, z:%f", p_player->getVeloctiy().x, p_player->getVeloctiy().y, p_player->getVeloctiy().z);
			ImGui::Text("Trgt vel: x:%f, y:%f, z:%f", p_player->getTargetVelocity().x, p_player->getTargetVelocity().y, p_player->getTargetVelocity().z);
			ImGui::Text("Camera forward: x:%.4g, y:%.4g, z:%.4g", p_player->getCamera().getForward().x, p_player->getCamera().getForward().y, p_player->getCamera().getForward().z);
		}

		/* Settings */
		if (ImGui::CollapsingHeader("Settings", ImGuiTreeNodeFlags_DefaultOpen)) {
			ImGui::SliderFloat("Move Speed", &moveSpeed, 1, 10000, "%.0f", 1);
			
			/* Shaders */
			if (ImGui::BeginCombo("Shader", "Choose Shader")) {
				if (ImGui::Selectable("Default")) {
					delete p_shader;
					p_shader = new Shader("res/shaders/defaultShader");
				} else if (ImGui::Selectable("Transparent")) {
					delete p_shader;
					p_shader = new Shader("res/shaders/transparentShader");
				} else if (ImGui::Selectable("Inverted colors")) {
					delete p_shader;
					p_shader = new Shader("res/shaders/invertedShader");
				}
				ImGui::EndCombo();
			}

			/* Texture Packs */
			if (ImGui::BeginCombo("Texture", "Choose Texture")) {
				for (uint8_t i = 0; i<texturePacks.size(); i++) {
					std::string name = texturePacks[i].substr(texturePacks[i].find_last_of("/\\") + 1);
					if (ImGui::Selectable(name.c_str())) {
						delete p_tex;
						p_tex = new Texture(texturePacks[i]);
						p_tex->bind();
					}
				}
				ImGui::EndCombo();
			}
		}
		ImGui::End();
	}

	drawCrosshair();

	/* Render */
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

/* TODO: Make an actual shader for this and not do it in ImGui. */
void drawCrosshair() {
	ImDrawList* drawList = ImGui::GetForegroundDrawList();
	ImVec2 offset(width/2, height/2);
	drawList->AddLine(ImVec2(offset.x-15, offset.y), ImVec2(offset.x+15, offset.y), IM_COL32(255,255,255,255), 4);
	drawList->AddLine(ImVec2(offset.x, offset.y-15), ImVec2(offset.x, offset.y+15), IM_COL32(255,255,255,255), 4);
}

void windowSizeCallback(GLFWwindow* window, int w, int h) {
	width = w;
	height = h;

	glViewport(0, 0, w, h);

	p_player->getCamera().setAspect((float)w / (float)h);
}

void mouseCallback(GLFWwindow* window, double x, double y) {
	double xOffset = x - lastMouseX;
	double yOffset = lastMouseY - y;

	lastMouseX = x;
	lastMouseY = y;

	if (glfwGetInputMode(p_window, GLFW_CURSOR) != GLFW_CURSOR_DISABLED)
		return;

	xOffset *= SENSITIVITY;
	yOffset *= SENSITIVITY;
	
	p_player->getCamera().onMouseMovement(xOffset, yOffset);
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

		case GLFW_KEY_F1:
			showGui = !showGui;
			break;

		case GLFW_KEY_F2:
			keepFlying = !keepFlying;
			break;
		
		case GLFW_KEY_R:
			p_player->getCamera().setPosition(START_POS);
			break;

		case GLFW_KEY_K:
			break;
		}
	} else if (action == GLFW_RELEASE) {
		Input::setKey(key, false);
	}
}

void mouseBtnCallback(GLFWwindow* window, int button, int action, int mods) {
}

bool init() {
	if (!initGlfw() || !initGl() || !initImGui()) {
		std::cerr << "ERROR: Initialization failed." << std::endl;
		return false;
	}

	for (const auto& f : std::filesystem::directory_iterator("res/textures")) {
		texturePacks.push_back(f.path().string());
	}

	if (texturePacks.size() < 1) {
		std::cerr << "ERROR: Couldn't find any texture packs. Try to reinstall the game." << std::endl;
		return false;
	}

	p_player = new Player(Camera(START_POS, 90, (float)width/(float)height, 0.3f, 1000));
	p_shader = new Shader("res/shaders/defaultShader");;
	p_tex	 = new Texture(texturePacks[0]);
	p_world	 = new World(p_player->getCamera());
	p_tex->bind(); 

	return true;
}

bool initGlfw() {
	if (!glfwInit()) {
		std::cerr << "Couldn't initialize the GLFW." << std::endl;
		return false;
	}
	
	p_window = glfwCreateWindow(WIDTH, HEIGHT, "Rotthin's Sandbox", /* glfwGetPrimaryMonitor() */ NULL, NULL);
	if (!p_window) {
		std::cerr << "Couldn't create the window." << std::endl;
		return false;
	}

	glewExperimental = true;

	glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); /* Use only OpenGL core */
	
	glfwMakeContextCurrent(p_window);
	
	glfwSwapInterval(0);
	glfwGetCursorPos(p_window, &lastMouseX, &lastMouseY);
	glfwMaximizeWindow(p_window);
	
	glfwSetMouseButtonCallback(p_window, mouseBtnCallback);
	glfwSetCursorPosCallback(p_window, mouseCallback);
	glfwSetWindowSizeCallback(p_window, windowSizeCallback);
	glfwSetKeyCallback(p_window, keyCallback);
	glfwSetErrorCallback(errorCallback);
	
	return true;
}

bool initGl() {
	if (glewInit() != GLEW_OK) {
		std::cerr << "Couldn't initialize the GLEW." << std::endl;
		return false;
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glClearColor(0, 160/255, 1.0, 1.0);

	glLoadIdentity();
	glViewport(0, 0, WIDTH, HEIGHT);
	glMatrixMode(GL_PROJECTION);

	return true;
}

bool initImGui() {
	if (!IMGUI_CHECKVERSION()) {
		return false;
	}

	p_imguiContext = ImGui::CreateContext();
	ImGui::SetCurrentContext(p_imguiContext);

	ImGui_ImplGlfw_InitForOpenGL(p_window, true);
	ImGui_ImplOpenGL3_Init("#version 130");
	
	return true;
}

void errorCallback(int error, const char* desc) {
	std::cerr << "GLFW ERROR "<< error << ": " << desc << std::endl;
}

void clear() {
	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	glfwDestroyWindow(p_window);
	glfwTerminate(); 

	delete p_shader;
	delete p_tex;
	delete p_player;
	delete p_world;

	Blocks::clearArray();
}