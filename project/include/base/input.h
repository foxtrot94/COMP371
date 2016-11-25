#pragma once
#include <iostream>
#include "Camera.h"
#include "glm.hpp"

class Camera;
struct GLFWwindow;

class Input{
private:
	Input() : MOUSE_L_PRESSED(false), MOUSE_R_PRESSED(false) {};
	bool MOUSE_L_PRESSED;
	bool MOUSE_R_PRESSED;
	bool SHIFT_BTN_PRESSED;
	Camera* mainCamera;

	static Input* instance;
public:
	static Input* GetInstance(){
		if (instance == nullptr){
			instance = new Input();
		}
		return instance; 
	}

	~Input(){}

	void resetCamera();
	void moveFwd();
	void moveBwd();
	void turnLeft();
	void turnRight();
	void strafeLeft();
	void strafeRight();

	void setCamera(Camera* newCamera);
	
	void leftMouseClick();
	void rightMouseClick();

	void moveCamera(glm::vec2 direction);

	void setMouseLeftBtnPressStatus(bool newLMouseBtnStatus) { MOUSE_L_PRESSED = newLMouseBtnStatus; }
	void setMouseRightBtnPressStatus(bool newRMouseBtnStatus) { MOUSE_R_PRESSED = newRMouseBtnStatus; }
	void setShiftBtnPressStatus(bool newShiftBtnStatus) { SHIFT_BTN_PRESSED = newShiftBtnStatus; }
};

//Handles keyboard input
void KeyInputCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

//Reads cursor position as it changes
void CursorPositionCallback(GLFWwindow* window, double x, double y);

//Handles input from the mouse buttons
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
