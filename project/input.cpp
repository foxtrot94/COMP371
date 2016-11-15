#include <iostream>
#include "main.h"
#include "input.h"

bool SHIFT_WAS_PRESSED = false; //Globals are not great. But this is C
bool MOUSE_L_PRESSED = false;
bool MOUSE_R_PRESSED = false;

const float CAMERA_STEP = 1.f;

glm::vec3 CAMERA_INITIAL_TRANSLATION;
glm::vec3 CAMERA_INITIAL_DIRECTION;

void Input::resetCamera(){
	cameraTranslation = CAMERA_INITIAL_TRANSLATION;
	cameraDirectionPoint = CAMERA_INITIAL_DIRECTION;
}

void Input::moveFwd()
{
	cameraTranslation.y += CAMERA_STEP;
}

void Input::moveBwd()
{
	cameraTranslation.y -= CAMERA_STEP;
}

void Input::turnLeft()
{
	std::cout << "turning left" << std::endl;
}

void Input::turnRight()
{
	std::cout << "turning right" << std::endl;
}

void Input::strafeLeft()
{
	std::cout << "dodge left" << std::endl;
}

void Input::strafeRight()
{
	std::cout << "dodge right" << std::endl;
}

void Input::leftMouseClick()
{
	std::cout << "shoot" << std::endl;
}

void Input::rightMouseClick()
{
	std::cout << "aim" << std::endl;
}

void Input::moveCamera(glm::vec2 direction){
	std::cout << "x : " << direction.x;
	std::cout << "y : " << direction.y << std::endl;

}

void Input::setCamera(Camera* newCamera){
	mainCamera = newCamera;
}

//This is essentially just a huge switch case to handle input correctly
void KeyInputCallback(GLFWwindow * window, int key, int scancode, int action, int mode)
{
	Input* instance = Input::getInstance();

	static char lastKey = 0;
	char pressKey = 0;
	if (action == GLFW_PRESS) {
	switch (key)
	{
	case GLFW_KEY_W:
	case GLFW_KEY_UP:
		instance->moveFwd();
		std::cout << cameraTranslation.y << std::endl;
		break;
	case GLFW_KEY_S:
	case GLFW_KEY_DOWN:
		instance->moveBwd();
		std::cout << cameraTranslation.y << std::endl;
		break;
	case GLFW_KEY_LEFT:
		instance->turnLeft();
		break;
	case GLFW_KEY_RIGHT:
		instance->turnRight();
		break;
	case GLFW_KEY_A:
		instance->strafeLeft();
		break;
	case GLFW_KEY_D:
		instance->strafeRight();
		break;
	case GLFW_KEY_R:
		instance->resetCamera();
		break;
		
	case GLFW_KEY_ESCAPE:
		glfwSetWindowShouldClose(window, GL_TRUE);
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



	default:
		//std::cout << "Unhandled input" << std::endl;
		break;
	}


	if (pressKey && lastKey!=pressKey) {
		std::cout << "pressed " << pressKey << std::endl;
		lastKey = pressKey;
	}

	}  // IF (action==press)
}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {

	Input* instance = Input::getInstance();

	if (action == GLFW_PRESS) {
		switch (button)
		{
		case GLFW_MOUSE_BUTTON_LEFT:
			instance->leftMouseClick();
			break;
		case GLFW_MOUSE_BUTTON_RIGHT:
			instance->rightMouseClick();
			break;
		default:
			break;
		};

	} //IF (action = press)

}

void CursorPositionCallback(GLFWwindow * window, double x, double y){

	Input* instance = Input::getInstance();

	static bool firstInput = true;
	static double lastX, lastY;

	if (firstInput)
	{
		lastX = x;
		lastY = y;
		firstInput = false;
		return;
	}

	//get the deltas
	double deltaX = x - lastX;
	double deltaY = y - lastY;

	instance->moveCamera(glm::vec2(deltaX, deltaY));
	

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

