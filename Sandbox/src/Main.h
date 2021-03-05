#pragma once

#include "core/Libs.h"

bool initGlfw();
bool initGl();
bool initImGui();
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);