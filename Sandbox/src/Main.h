#pragma once

#include "Libs.h"

bool initGlfw();
bool initGl();
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);