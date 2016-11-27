#pragma once

#include "..\glm\glm.hpp"

#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include "base\Renderer.h"
#include "base\Objects.h"


typedef Renderer::Window* EngWindPtr;


class Camera : public EngineObject
{
public:
	const glm::vec3 INITIAL_CAMERA_POS = glm::vec3(0.0f, 1.7f, 3.0f);
	const glm::vec3 CAMERA_FRONT = glm::vec3(0.0f, 0.0f, -1.0f);
	const glm::vec3 CAMERA_UP = glm::vec3(0.0f, 1.0f, 0.0f);
	const GLfloat INITIAL_YAW = -90.0f;	// Yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right (due to how Eular angles work) so we initially rotate a bit to the left.
	const GLfloat INITIAL_PITCH = 0.0f;
	const GLfloat DEFAULT_FOV = 90.0f;
	const float CAM_SPEED_CONSTANT = 50.0f;

    float cameraSensitivity = 0.5f;
	float cameraSpeed = 0.0f;

	//Tech Debt: Why is this a public inner struct?
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


	float GetCameraSpeed();
	void Update(const float& deltaTime);
	
	GLfloat GetYaw();
	void SetYaw(GLfloat camYaw);

	GLfloat GetPitch();
	void SetPitch(GLfloat camPitch);

	vec3 GetCameraFront();
	void SetCameraFront(vec3 front);

	float GetCameraSensitivity();
	void SetCameraSensitivity(float sens);

	//Insert 'p' for positive or "n" for negative in operation
	//Specify axis 'z' or 'x' 
	void Camera::chooseDirection(char operation, char axis);

	//Get the View matrix
	mat4 GetView();
	//Get the projection matrix
	mat4 GetProjection(EngWindPtr engineWindow);

private:
	int width, height;
	Camera(int width, int height) :
		width(width), height(height)
	{
		initialize();
	};

	void initialize() {
		camPam = CameraParameters(
			INITIAL_CAMERA_POS, CAMERA_FRONT, CAMERA_UP,
			INITIAL_YAW, INITIAL_PITCH,
			width, height,
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
