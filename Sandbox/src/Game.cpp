#include "Game.h"

Game* Game::mp_instance;

Game::Game() {
	mp_instance = this;
}

Game::~Game() {
	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	glfwDestroyWindow(mp_window);
	glfwTerminate();

	delete mp_shader;
	delete mp_tex;
	delete mp_player;
	delete mp_world;

	Blocks::ClearBlockTypes();
}

bool Game::Start() {
	if (!Init()) {
		Close();
		return false;
	}

	while (!glfwWindowShouldClose(mp_window)) {
		StartFrame();

		Update();
		Draw();
		
		EndFrame();
	}

	return true;
}

void Game::StartFrame() {
	glfwPollEvents();
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void Game::Update() {
	glfwSetInputMode(mp_window, GLFW_CURSOR, m_showCursor ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);

	glm::vec3 moveDir(0, 0, 0);
	glm::vec3 forward = glm::normalize(glm::vec3(mp_player->GetCamera().GetForward().x, 0, mp_player->GetCamera().GetForward().z));
	glm::vec3 up = glm::vec3(0, 1, 0);
	glm::vec3 left = mp_player->GetCamera().GetLeft();

	if (Input::GetKey(GLFW_KEY_W) || m_keepFlying) moveDir += forward;
	if (Input::GetKey(GLFW_KEY_S)) moveDir -= forward;
	if (Input::GetKey(GLFW_KEY_A)) moveDir += left;
	if (Input::GetKey(GLFW_KEY_D)) moveDir -= left;
	if (Input::GetKey(GLFW_KEY_SPACE)) moveDir += glm::vec3(0, 1, 0);
	if (Input::GetKey(GLFW_KEY_LEFT_SHIFT)) moveDir -= up;

	if (glm::length(moveDir)>0) {
		mp_player->SetTargetVelocity(glm::normalize(moveDir) * m_moveSpeed * m_dt);
	} else {
		mp_player->SetTargetVelocity(glm::vec3(0));
	}

	mp_player->Update(m_dt);

	mp_world->Update();
	mp_world->CheckViewDistance(mp_player->GetCamera());
}

void Game::Draw() {
	mp_world->Draw(*mp_shader, mp_player->GetCamera());
	DrawImGui();
}

void Game::DrawImGui() {
	if (!m_showGui) return;

	// Start new frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// Debug
	if (m_showDebug) {
		ImGui::Begin("Debug");
		// Stats
		if (ImGui::CollapsingHeader("Stats", ImGuiTreeNodeFlags_DefaultOpen)) {
			if (ImGui::CollapsingHeader("Performance", ImGuiTreeNodeFlags_DefaultOpen)) {
				ImGui::Text("Fps: %.4g", 1.0f / m_dt);
				ImGui::Text("Frame delta: %f", m_dt);
				ImGui::Text("Chunk count: %u", mp_world->m_chunks.size());
			}

			ImGui::Text("Player pos: x:%f, y:%f, z:%f", mp_player->GetPosition().x, mp_player->GetPosition().y, mp_player->GetPosition().z);
			ImGui::Text("Vel: x:%f, y:%f, z:%f", mp_player->GetVeloctiy().x, mp_player->GetVeloctiy().y, mp_player->GetVeloctiy().z);
			ImGui::Text("Trgt vel: x:%f, y:%f, z:%f", mp_player->GetTargetVelocity().x, mp_player->GetTargetVelocity().y, mp_player->GetTargetVelocity().z);
			ImGui::Text("Camera forward: x:%.4g, y:%.4g, z:%.4g", mp_player->GetCamera().GetForward().x, mp_player->GetCamera().GetForward().y, mp_player->GetCamera().GetForward().z);
		}

		// Settings
		if (ImGui::CollapsingHeader("Settings", ImGuiTreeNodeFlags_DefaultOpen)) {
			ImGui::SliderFloat("Move Speed", &m_moveSpeed, 1, 100, "%.0f", 1);

			// Shaders
			if (ImGui::BeginCombo("Shader", "Choose Shader")) {
				if (ImGui::Selectable("Default")) {
					mp_shader = new Shader("res/shaders/default");
				} else if (ImGui::Selectable("No Fog")) {
					delete mp_shader;
					mp_shader = new Shader("res/shaders/noFog");
				}
				ImGui::EndCombo();
			}

			// Texture Packs
			if (ImGui::BeginCombo("Texture", "Choose Texture")) {
				for (uint8_t i = 0; i < m_texturePacks.size(); i++) {
					std::string name = m_texturePacks[i].substr(m_texturePacks[i].find_last_of("/\\")+1);
					if (ImGui::Selectable(name.c_str())) {
						delete mp_tex;
						mp_tex = new Texture(m_texturePacks[i]);
						mp_tex->Bind();
					}
				}
				ImGui::EndCombo();
			}
		}
		ImGui::End();
	}

	DrawCrosshair();

	// Render
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Game::DrawCrosshair() {
	ImDrawList* drawList = ImGui::GetForegroundDrawList();
	ImVec2 offset(static_cast<float>(m_width)/2, static_cast<float>(m_height)/2);
	drawList->AddLine(ImVec2(offset.x-15, offset.y), ImVec2(offset.x+15, offset.y), IM_COL32(255, 255, 255, 255), 4);
	drawList->AddLine(ImVec2(offset.x, offset.y-15), ImVec2(offset.x, offset.y+15), IM_COL32(255, 255, 255, 255), 4);
}

void Game::EndFrame() {
	glfwSwapBuffers(mp_window);
	CalculateDelta();
}

bool Game::Init() {
	if (!InitGlfw()||!InitGl()||!InitImGui()) {
		std::cerr<<"ERROR: Initialization failed."<<std::endl;
		return false;
	}

	for (const auto& f:std::filesystem::directory_iterator("res/textures")) {
		m_texturePacks.push_back(f.path().string());
	}

	if (m_texturePacks.size()<1) {
		std::cerr<<"ERROR: Couldn't find any texture packs. Try to reinstall the game."<<std::endl;
		return false;
	}

	mp_player = new Player(Camera(START_POS, 90, (float) m_width/(float) m_height, 0.3f, 1000));
	mp_shader = new Shader("res/shaders/default");
	mp_tex = new Texture(m_texturePacks[0]);
	mp_world = new World(mp_player->GetCamera(), mp_window);
	mp_tex->Bind();

	return true;
}

void Game::Close() {
	glfwSetWindowShouldClose(mp_window, true);
}

bool Game::InitImGui() {
	if (!IMGUI_CHECKVERSION()) {
		return false;
	}

	mp_imguiContext = ImGui::CreateContext();
	ImGui::SetCurrentContext(mp_imguiContext);

	ImGui_ImplGlfw_InitForOpenGL(mp_window, true);
	ImGui_ImplOpenGL3_Init("#version 130");

	return true;
}

bool Game::InitGl() {
	if (glewInit()!=GLEW_OK) {
		std::cerr<<"Couldn't initialize the GLEW."<<std::endl;
		return false;
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glClearColor(0.69f, 0.878f, 0.902f, 1.0f);

	glLoadIdentity();
	glViewport(0, 0, WIDTH, HEIGHT);
	glMatrixMode(GL_PROJECTION);

	return true;
}

bool Game::InitGlfw() {
	if (!glfwInit()) {
		std::cerr<<"Couldn't initialize the GLFW."<<std::endl;
		return false;
	}

	mp_window = glfwCreateWindow(WIDTH, HEIGHT, "Rotthin's Sandbox", glfwGetPrimaryMonitor(), NULL);
	if (!mp_window) {
		std::cerr<<"Couldn't create the window."<<std::endl;
		return false;
	}

	glewExperimental = true;

	glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwMakeContextCurrent(mp_window);

	glfwSwapInterval(0);
	glfwGetCursorPos(mp_window, &m_lastMouseX, &m_lastMouseY);
	glfwMaximizeWindow(mp_window);

	glfwSetMouseButtonCallback(mp_window, GlfwMouseBtnCallback);
	glfwSetCursorPosCallback(mp_window, GlfwMouseCallback);
	glfwSetWindowSizeCallback(mp_window, GlfwWindowSizeCallback);
	glfwSetKeyCallback(mp_window, GlfwKeyCallback);
	glfwSetErrorCallback(GlfwErrorCallback);

	return true;
}

void Game::CalculateDelta() {
	m_now = (float) glfwGetTime();
	m_dt = m_now-m_lastFrame;
	m_lastFrame = m_now;
}

#pragma region GLFW_CALLBACKS

void Game::GlfwErrorCallback(int error, const char* desc) {
	mp_instance->GlfwErrorCallbackImpl(error, desc);
}

void Game::GlfwErrorCallbackImpl(int error, const char* desc) {
	std::cerr<<"GLFW ERROR "<<error<<": "<<desc<<std::endl;
}

void Game::GlfwKeyCallback(GLFWwindow* p_window, int key, int scancode, int action, int mods) {
	mp_instance->GlfwKeyCallbackImpl(p_window, key, scancode, action, mods);
}

void Game::GlfwKeyCallbackImpl(GLFWwindow* p_window, int key, int scancode, int action, int mods) {
	if (action==GLFW_PRESS) {
		Input::SetKey(key, true);

		switch (key) {
		case GLFW_KEY_ESCAPE:
			m_showCursor = !m_showCursor;
			break;

		case GLFW_KEY_TAB:
			m_showDebug = !m_showDebug;
			break;

		case GLFW_KEY_F1:
			m_showGui = !m_showGui;
			break;

		case GLFW_KEY_F2:
			m_keepFlying = !m_keepFlying;
			break;

		case GLFW_KEY_R:
			mp_player->GetCamera().SetPosition(START_POS);
			break;

		case GLFW_KEY_K:
			break;
		}
	} else if (action==GLFW_RELEASE) {
		Input::SetKey(key, false);
	}
}

void Game::GlfwMouseCallback(GLFWwindow* p_window, double x, double y) {
	mp_instance->GlfwMouseCallbackImpl(p_window, x, y);
}

void Game::GlfwMouseCallbackImpl(GLFWwindow* p_window, double x, double y) {
	double xOffset = x-m_lastMouseX;
	double yOffset = m_lastMouseY-y;

	m_lastMouseX = x;
	m_lastMouseY = y;

	// Dont move the camera if cursor isn't disabled.
	if (glfwGetInputMode(p_window, GLFW_CURSOR) != GLFW_CURSOR_DISABLED) {
		return;
	}

	xOffset *= SENSITIVITY;
	yOffset *= SENSITIVITY;

	mp_player->GetCamera().OnMouseMovement(xOffset, yOffset);
}

void Game::GlfwMouseBtnCallback(GLFWwindow* p_window, int button, int action, int mods) {
	mp_instance->GlfwMouseBtnCallbackImpl(p_window, button, action, mods);
}

void Game::GlfwMouseBtnCallbackImpl(GLFWwindow* p_window, int button, int action, int mods) {

}

void Game::GlfwWindowSizeCallback(GLFWwindow* p_window, int w, int h) {
	mp_instance->GlfwWindowSizeCallbackImpl(p_window, w, h);
}

void Game::GlfwWindowSizeCallbackImpl(GLFWwindow* p_window, int w, int h) {
	m_width = w;
	m_height = h;

	glViewport(0, 0, std::max(600, w), std::max(600, h));

	mp_player->GetCamera().SetAspect((float) std::max(600, w)/(float) std::max(600, h));
}

#pragma endregion GLFW_CALLBACKS