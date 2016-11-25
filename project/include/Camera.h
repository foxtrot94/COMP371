#pragma once

#include "..\glew\glew.h"	// include GL Extension Wrangler
#include "..\glfw\glfw3.h"	// include GLFW helper library
#include "..\glm\glm.hpp"

#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "base\Renderer.h"
#include "base\Objects.h"


typedef Renderer::Window* EngWindPtr;


class Camera 
{
public:

	const glm::vec3 INITIAL_CAMERA_POS = glm::vec3(0.0f, 0.0f, 3.0f);
	const glm::vec3 INITIAL_CAMERA_FRONT = glm::vec3(0.0f, 0.0f, -1.0f);
	const glm::vec3 INITIAL_CAMERA_CAMERA_UP = glm::vec3(0.0f, 1.0f, 0.0f);
	const GLfloat INITIAL_YAW = -90.0f;	// Yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right (due to how Eular angles work) so we initially rotate a bit to the left.
	const GLfloat INITIAL_PITCH = 0.0f;
	const GLfloat DEFAULT_FOV = 45.0f;
	const float CAM_SPEED_CONSTANT = 50.0f;

    float cameraSensitivity = 0.05f;
	float cameraSpeed = 0.0f;


	//Inner Camera parameters
	struct CameraParameters
	{
		glm::vec3 cameraPos;
		glm::vec3 cameraFront;
		glm::vec3 cameraUp;
		GLfloat yaw;
		GLfloat pitch;
		GLfloat lastX;
		GLfloat lastY;
		GLfloat fov;
		CameraParameters() {};
		CameraParameters(glm::vec3 pos, glm::vec3 f, glm::vec3 u, GLfloat y, GLfloat p, GLfloat lx, GLfloat ly, GLfloat fo) :
			cameraPos(pos), cameraFront(f), cameraUp(u), yaw(y), pitch(p), lastX(lx), lastY(ly), fov(fo) {}

	};
	CameraParameters camPam;

	static Camera* GetInstance(EngWindPtr givenEngineWindow)
	{
		static Camera* instance;
		if (instance == nullptr)
		{
			static EngWindPtr engineWindow = givenEngineWindow;
			instance = new Camera(givenEngineWindow->width, givenEngineWindow->height);

		}
		return instance;
	}


	float Camera::GetCameraSpeed();
	void Camera::SetCameraSpeed(float time);


	
	GLfloat Camera::GetYaw();
	void Camera::SetYaw(GLfloat camYaw);


	GLfloat Camera::GetPitch();
	void Camera::SetPitch(GLfloat camPitch);

	glm::vec3 Camera::GetCameraFront();
	void Camera::SetCameraFront(glm::vec3 front);

	float Camera::GetCameraSensitivity();
	void Camera::SetCameraSensitivity(float sens);





	//Insert 'p' for positive or "n" for negative in operation
	//Specify axis 'z' or 'x' 
	void Camera::chooseDirection(char operation, char axis);


private:
	int width, height;
	Camera(int width, int height) :
		width(width), height(height)
	{
		initialize();
	};

	

	void initialize() {
		camPam = CameraParameters(
			INITIAL_CAMERA_POS, INITIAL_CAMERA_FRONT, INITIAL_CAMERA_CAMERA_UP,
			INITIAL_YAW, INITIAL_PITCH,
			width / 2.0f, height / 2.0f,
			DEFAULT_FOV);
	}



	// Front and Back Operations
	void Camera::increaseZ(float camSpeed);
	void Camera::decreaseZ(float camSpeed);

	//Strafe Left and Right Operations
	void Camera::decreaseX(float camSpeed);
	void Camera::increaseX(float camSpeed);

	

	//void turnLeft();
	//void turnRight();



};
