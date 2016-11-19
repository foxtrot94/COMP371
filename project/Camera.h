#pragma once

#include "..\glew\glew.h"	// include GL Extension Wrangler
#include "..\glfw\glfw3.h"	// include GLFW helper library
#include "..\glm\glm.hpp"

#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "base\Renderer.h"

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
		CameraParameters(glm::vec3 pos,glm::vec3 f, glm::vec3 u, GLfloat y,GLfloat p, GLfloat lx,GLfloat ly, GLfloat fo) :
			cameraPos(pos), cameraFront(f), cameraUp(u), yaw(y), pitch(p), lastX(lx), lastY(ly), fov(fo){}

	};

	static Camera* getInstance(EngWindPtr givenEngineWindow)
	{
		static Camera* instance;
		if (instance == nullptr)
		{
			static EngWindPtr engineWindow = givenEngineWindow;
			instance = new Camera(givenEngineWindow->width, givenEngineWindow->height);

		}
		return instance;
	}
	
	
private:
	int width, height;
	Camera(int width, int height) :
		width(width), height(height)
	{
		initialize();
	};

	CameraParameters camPam;

	void initialize() {
		camPam = CameraParameters(
			INITIAL_CAMERA_POS, INITIAL_CAMERA_FRONT, INITIAL_CAMERA_CAMERA_UP,
			INITIAL_YAW, INITIAL_PITCH,
			width / 2.0f, height / 2.0f,
			DEFAULT_FOV);
	}

};

