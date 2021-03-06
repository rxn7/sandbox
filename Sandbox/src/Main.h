#pragma once

#include "core/Libs.h"

bool initGlfw();
bool initGl();
bool initImGui();

//void spawnBlock(const glm::vec3& pos);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouseCallback(GLFWwindow* window, double x, double y);
void drawImGui();
void update();
void draw();