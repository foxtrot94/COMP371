#pragma once

#include "..\glfw\glfw3.h"
#include "glm.hpp"

//Handles keyboard input
void KeyInputCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

//Reads cursor position as it changes
void CursorPositionCallback(GLFWwindow* window, double x, double y);

//Handles input from the mouse buttons
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

void SetInputCallbacks(GLFWwindow* window);
