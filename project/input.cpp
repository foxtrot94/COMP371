#include <iostream>
#include "main.h"
#include "input.h"

bool SHIFT_WAS_PRESSED = false; //Globals are not great. But this is C
bool MOUSE_L_PRESSED = false;
bool MOUSE_R_PRESSED = false;

const float CAMERA_STEP = 1.f;

glm::vec3 CAMERA_INITIAL_TRANSLATION;
glm::vec3 CAMERA_INITIAL_DIRECTION;

//This is essentially just a huge switch case to handle input correctly
void KeyInputCallback(GLFWwindow * window, int key, int scancode, int action, int mode)
{
	static char lastKey = 0;
	char pressKey = 0;
	switch (key)
	{
	case GLFW_KEY_ESCAPE:
		break;

	case GLFW_KEY_R:
		cameraTranslation = CAMERA_INITIAL_TRANSLATION;
		cameraDirectionPoint = CAMERA_INITIAL_DIRECTION;
		break;

	case GLFW_KEY_X:
		pressKey = SHIFT_WAS_PRESSED ? 'X' : 'x';
		objectRotation = glm::vec3(SHIFT_WAS_PRESSED ? 1.0f : -1.0f, 0.f, 0.f);
		break;
	case GLFW_KEY_Y:
		pressKey = SHIFT_WAS_PRESSED ? 'Y' : 'y';
		objectRotation = glm::vec3(0.f, SHIFT_WAS_PRESSED ? 1.0f : -1.0f, 0.f);
		break;
	case GLFW_KEY_Z:
		pressKey = SHIFT_WAS_PRESSED ? 'Z' : 'z';
		objectRotation = glm::vec3(0.f, 0.f, SHIFT_WAS_PRESSED ? 1.0f : -1.0f);
		break;

	case GLFW_KEY_W:
		pressKey = 'w';
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case GLFW_KEY_T:
		pressKey = 't';
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case GLFW_KEY_P:
		pressKey = 'p';
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		break;

	case GLFW_KEY_LEFT_SHIFT:
	case GLFW_KEY_RIGHT_SHIFT:
		if (action == GLFW_PRESS) {
			SHIFT_WAS_PRESSED = true;
		}
		else if (action == GLFW_RELEASE) {
			SHIFT_WAS_PRESSED = false;
		}
		break;

	case GLFW_KEY_UP:
		cameraTranslation.y += CAMERA_STEP;
		break;
	case GLFW_KEY_DOWN:
		cameraTranslation.y -= CAMERA_STEP;
		break;
	case GLFW_KEY_LEFT:
		cameraTranslation.x -= CAMERA_STEP;
		break;
	case GLFW_KEY_RIGHT:
		cameraTranslation.x += CAMERA_STEP;
		break;

	case GLFW_KEY_PAGE_UP:
		cameraTranslation.z += CAMERA_STEP*10.f;
		break;
	case GLFW_KEY_PAGE_DOWN:
		cameraTranslation.z -= CAMERA_STEP*10.f;
		break;

	default:
		//std::cout << "Unhandled input" << std::endl;
		break;
	}

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (pressKey && lastKey!=pressKey) {
		std::cout << "pressed " << pressKey << std::endl;
		lastKey = pressKey;
	}
	
}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	switch (button)
	{
	case GLFW_MOUSE_BUTTON_RIGHT:
		if (action == GLFW_PRESS) {
			MOUSE_R_PRESSED = true;
		}
		else if (action == GLFW_RELEASE) {
			MOUSE_R_PRESSED = false;
		}
		break;

	case GLFW_MOUSE_BUTTON_LEFT:
		if (action == GLFW_PRESS) {
			MOUSE_L_PRESSED = true;
		}
		else if (action == GLFW_RELEASE) {
			MOUSE_L_PRESSED = false;
		}
		break;
	default:
		break;
	}

}

void CursorPositionCallback(GLFWwindow * window, double x, double y){
	static bool firstInput = true;
	static double lastX, lastY;
	//static double deltaY = 0.f, deltaX = 0.f;
	//std::cout << "x:" << x << " y:" << y << std::endl;

	if (firstInput)
	{
		lastX = x;
		lastY = y;
		firstInput = false;
		return;
	}

	//Avoid unknown behaviour for now...
	if (MOUSE_L_PRESSED && MOUSE_R_PRESSED) { return; }

	//get the deltas
	double deltaX = x - lastX;
	double deltaY = y - lastY;

	//Move forward and backward
	if (MOUSE_R_PRESSED) {
		//We're missing something here
		cameraTranslation.z += CAMERA_STEP * deltaY;
		
		//std::cout << deltaY << std::endl;
	}

	//Handle rotation
	if (MOUSE_L_PRESSED) {
		glm::mat4 rotMatrix(1.f);
		
		//For some reason, these work better flipped...
		//Will do the math later.
		glm::vec3 axis(deltaY, deltaX, 0.f);

		//std::cout << "x " << axis.x << " y " << axis.y << std::endl;

		rotMatrix = glm::rotate(rotMatrix, (float) (deltaTime*glm::distance(deltaX,deltaY)),axis);
		cameraDirectionPoint = glm::vec3(rotMatrix * glm::vec4(cameraDirectionPoint, 1.0f));
	}

	lastX = x;
	lastY = y;

}

void SetInputCallbacks(GLFWwindow* window) {
	CAMERA_INITIAL_DIRECTION = cameraDirectionPoint;
	CAMERA_INITIAL_TRANSLATION = cameraTranslation;

	glfwSetKeyCallback(window, &KeyInputCallback);
	glfwSetCursorPosCallback(window, &CursorPositionCallback);
	glfwSetMouseButtonCallback(window, &MouseButtonCallback);
}

