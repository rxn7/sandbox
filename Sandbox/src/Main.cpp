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

#include "BlocksContainer.cpp"
#include "Block.h"
#include "BlockType.h"
#include "Main.h"
#include "Chunk.h"
#include "World.h"

#define HEIGHT 1080
#define WIDTH 1920
#define SENSITIVITY 0.1f
#define MOVE_SPEED 10

int width = WIDTH, height = HEIGHT;

bool showDebug = true, showCursor = false;

float moveSpeed = 10;
float dt;
double lastMouseX = 0, lastMouseY = 0;

ImGuiContext* p_imguiContext;
GLFWwindow* p_window;
Shader* p_shader;
Camera* p_camera;
World* p_world;
Texture* p_tex;

std::vector<std::string> texturePacks;

int main() {
	if (!init()) {
		clear();
		return -1;
	}

	float now = 0, lastFrame = 0;
	/*Main loop*/
	while (!glfwWindowShouldClose(p_window)) {
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		update();
		draw();
		
		glfwSwapBuffers(p_window);

		/* Calculate delta between frames*/
		now = (float)glfwGetTime();
		dt = now - lastFrame;
		lastFrame = now; 
	}

	clear();
	return 0;
}

void draw() {
	p_world->draw(*p_shader, *p_camera);
	drawImGui();
}

void update() {
	glfwSetInputMode(p_window, GLFW_CURSOR, showCursor ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);

	glm::vec3 moveDir(0, 0, 0);
	glm::vec3 forward = glm::normalize(glm::vec3(p_camera->getForward().x, 0, p_camera->getForward().z));
	glm::vec3 up = glm::vec3(0,1,0);
	if (Input::getKey(GLFW_KEY_W)) moveDir += forward;
	if (Input::getKey(GLFW_KEY_S)) moveDir -= forward;
	if (Input::getKey(GLFW_KEY_A)) moveDir += p_camera->getLeft();
	if (Input::getKey(GLFW_KEY_D)) moveDir += p_camera->getRight();
	if (Input::getKey(GLFW_KEY_SPACE)) moveDir += glm::vec3(0, 1, 0);
	if (Input::getKey(GLFW_KEY_LEFT_SHIFT)) moveDir -= up;

	if (moveDir != glm::vec3()) {
		p_camera->move(moveDir * dt * moveSpeed);
	}
}

void drawImGui() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	/*Debug*/
	if (showDebug) {
		ImGui::Begin("Debug");
		/*Stats*/
		if (ImGui::CollapsingHeader("Stats", ImGuiTreeNodeFlags_DefaultOpen)) {
			if (ImGui::CollapsingHeader("Performance", ImGuiTreeNodeFlags_DefaultOpen)) {
				ImGui::Text("Fps: %.4g", 1.0f/dt);
				ImGui::Text("Frame delta: %f", dt);
			}

			ImGui::Text("Camera pos: x:%.4g, y:%.4g, z:%.4g", p_camera->getPosition().x, p_camera->getPosition().y, p_camera->getPosition().z);
			ImGui::Text("Camera forward: x:%.4g, y:%.4g, z:%.4g", p_camera->getForward().x, p_camera->getForward().y, p_camera->getForward().z);
			ImGui::Text("Yaw: %.4g, Pitch:%.4g", p_camera->m_yaw, p_camera->m_pitch);
		}

		/*Settings*/
		if (ImGui::CollapsingHeader("Settings", ImGuiTreeNodeFlags_DefaultOpen)) {
			ImGui::SliderFloat("Move Speed", &moveSpeed, 1, 100, "%.0f", 1);
			/*Camera FOV*/
			if (ImGui::SliderFloat("Camera Fov", &p_camera->m_fov, 1, 179, "%.0f", 1)) {
				p_camera->recalculatePerspective(width, height);
				p_camera->update();
			}

			/*Shaders*/
			if (ImGui::BeginCombo("Shader", "Choose Shader")) {
				if (ImGui::Selectable("Default")) {
					delete p_shader;
					p_shader = new Shader("res/shaders/defaultShader");
				}
				else if (ImGui::Selectable("Transparent")) {
					delete p_shader;
					p_shader = new Shader("res/shaders/transparentShader");
				}
				else if (ImGui::Selectable("Inverted colors")) {
					delete p_shader;
					p_shader = new Shader("res/shaders/invertedShader");
				}
				ImGui::EndCombo();
			}

			/*Texture Packs*/
			if (ImGui::BeginCombo("Texture", "Choose Texture")) {
				for (unsigned int i = 0; i<texturePacks.size(); i++) {
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
		
		/*Generate World*/
		if (ImGui::Button("Generate World")) {
			/*Delete all generated chunks before genereting new ones*/
			for (int i = 0; i<p_world->m_chunks.size(); i++) {
				delete p_world->m_chunks[i];
			}

			p_world->m_chunks.clear();
			p_world->generate();
		}

		ImGui::End();
	}

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void windowSizeCallback(GLFWwindow* window, int w, int h) {
	width = w;
	height = h;

	glViewport(0, 0, w, h);
	p_camera->recalculatePerspective(w, h);
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

	p_shader = new Shader("res/shaders/defaultShader");;
	p_camera = new Camera(glm::vec3(0, 20, -5), 90, (float)WIDTH/(float)HEIGHT, 0.1f, 100.0f);
	p_tex	 = new Texture(texturePacks[0]);
	p_world	 = new World();
	p_tex->bind();

	return true;
}

bool initGlfw() {
	if (!glfwInit()) {
		std::cerr << "Couldn't initialize the GLFW." << std::endl;
		return false;
	}
	
	p_window = glfwCreateWindow(WIDTH, HEIGHT, "Rotthin's Sandbox", /*glfwGetPrimaryMonitor()*/ NULL, NULL);
	if (!p_window) {
		std::cerr << "Couldn't create the window." << std::endl;
		return false;
	}

	glewExperimental = true;

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	glfwMakeContextCurrent(p_window);
	
	glfwSwapInterval(0);
	glfwGetCursorPos(p_window, &lastMouseX, &lastMouseY);
	glfwMaximizeWindow(p_window);
	
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

	glClearColor(0.53f, 0.8f, 0.92f, 1);

	glViewport(0, 0, WIDTH, HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

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
	delete p_camera;
	delete p_world;
	delete p_imguiContext;
}