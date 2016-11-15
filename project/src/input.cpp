#include <iostream>
#include "main.h"
#include "input.h"

//TODO: Replace with actual input
void KeyInputCallback(GLFWwindow * window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}	
}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	switch (button)
	{
	default:
		break;
	}

}

void CursorPositionCallback(GLFWwindow * window, double x, double y){
	static bool firstInput = true;
	static double lastX, lastY;
	//static double deltaY = 0.f, deltaX = 0.f;
	//std::cout << "x:" << x << " y:" << y << std::endl;

}

void SetInputCallbacks(GLFWwindow* window) {
	glfwSetKeyCallback(window, &KeyInputCallback);
	glfwSetCursorPosCallback(window, &CursorPositionCallback);
	glfwSetMouseButtonCallback(window, &MouseButtonCallback);
}

