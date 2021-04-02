#pragma once

#include "core/Libs.h"

bool initGlfw();
bool initGl();
bool initImGui();
bool init();

void errorCallback(int error, const char* desc);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouseCallback(GLFWwindow* window, double x, double y);
void mouseBtnCallback(GLFWwindow* window, int button, int action, int mods);
void drawImGui();
void drawCrosshair();
void update();
void draw();
void clear();