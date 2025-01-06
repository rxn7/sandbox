#pragma once

#define START_POS glm::vec3(0, 80, 0)
#define HEIGHT 1080
#define WIDTH 1920
#define SENSITIVITY 0.1f
#define MOVE_SPEED 10

#include "core/Libs.h"

#include <vector>
#include <filesystem>
#include <iostream>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "core/render/Texture.h"
#include "core/Input.h"

#include "Player.h"
#include "Chunk.h"
#include "World.h"

class Game {
public:
	Game();
	virtual ~Game();
	bool Start();

private:
	/// <summary> Calls initGlfw, initGl, InitImGui and initialzes the variables. </summary>
	bool Init();

	/// <summary> Initializes GLFW. </summary>
	bool InitGlfw();

	/// <summary> Initializes OpenGL. </summary>
	bool InitGl();

	/// <summary> Initializes OpenGL. </summary>
	bool InitImGui();

	/// <summary> Closes the window. </summary>
	void Close();

	/// <summary> Calls glfwPollEvents and glClear. </summary>
	void StartFrame();

	/// <summary> Does all the logic that has to be calculated every frame. </summary>
	void Update();

	/// <summary> Draws the world first, then ImGui. </summary>
	void Draw();

	/// <summary> Draws the ImGui. Note: ImGui is being drawn at the end. </summary>
	void DrawImGui();

	/// <summary> Draws the crosshair using the ImGui. </summary>
	void DrawCrosshair();

	/// <summary> Calls glfwSwapBuffers and calculateDelta. </summary>
	void EndFrame();

	/// <summary> Calculates delta between current frame and last frame. </summary>
	void CalculateDelta();

	#pragma region GLFW_CALLBACKS
	
	static void GlfwErrorCallback(int error, const char* desc);
	void GlfwErrorCallbackImpl(int error, const char* desc);
	
	static void GlfwKeyCallback(GLFWwindow* p_window, int key, int scancode, int action, int mods);
	void GlfwKeyCallbackImpl(GLFWwindow* p_window, int key, int scancode, int action, int mods);
	
	static void GlfwMouseCallback(GLFWwindow* p_window, double x, double y);
	void GlfwMouseCallbackImpl(GLFWwindow* p_window, double x, double y);
	
	static void GlfwMouseBtnCallback(GLFWwindow* p_window, int button, int action, int mods);
	void GlfwMouseBtnCallbackImpl(GLFWwindow* p_window, int button, int action, int mods);

	static void GlfwWindowSizeCallback(GLFWwindow* p_window, int w, int h);
	void GlfwWindowSizeCallbackImpl(GLFWwindow* p_window, int w, int h);
	
#pragma endregion GLFW_CALLBACKS

private:
	static Game* mp_instance;
	int m_width = WIDTH, m_height = HEIGHT;
	bool m_showGui = true, m_showDebug = true, m_showCursor = false, m_keepFlying = false;
	float m_moveSpeed = 10;
	float m_dt=0, m_now=0, m_lastFrame=0;
	double m_lastMouseX = 0, m_lastMouseY = 0;

	ImGuiContext* mp_imguiContext;
	GLFWwindow* mp_window;
	Shader* mp_shader;
	Player* mp_player;
	World* mp_world;
	Texture* mp_tex;

	std::vector<std::string> m_texturePacks;
};

