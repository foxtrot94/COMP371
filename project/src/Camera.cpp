#include "Camera.h"


//Get delta time from update and use it for operations
float Camera::GetCameraSpeed()
{
	return cameraSpeed;
}

void Camera::Update(const float& deltaTime)
{
	cameraSpeed = (deltaTime) * CAM_SPEED_CONSTANT;
}

GLfloat Camera::GetYaw()
{
	return camPam.yaw;
}
void Camera::SetYaw(GLfloat camYaw)
{
	camPam.yaw = camYaw;
}

GLfloat Camera::GetPitch()
{
	return camPam.pitch;
}
void Camera::SetPitch(GLfloat camPitch)
{
	camPam.pitch = camPitch;

}

glm::vec3 Camera::GetCameraFront()
{
	return camPam.cameraFront;
}
void Camera::SetCameraFront(glm::vec3 front)
{
	camPam.cameraFront = front;
}

float Camera::GetCameraSensitivity()
{
	return cameraSensitivity;
}
void Camera::SetCameraSensitivity(float sens)
{
	cameraSensitivity = sens;
}

void Camera::chooseDirection(char operation, char axis)
{
	if (operation == 'p' && axis == 'x')
	{
		increaseX(GetCameraSpeed());
	}
	else if (operation == 'n' && axis == 'x')
	{
		decreaseX(GetCameraSpeed());
	}
	else if (operation == 'p' && axis == 'z')
	{
		
		increaseZ(GetCameraSpeed());
	}
	else if (operation == 'n' && axis == 'z')
	{
		decreaseZ(GetCameraSpeed());
	}
		

}

mat4 Camera::GetView()
{
	// camPam.cameraPos + camPam.cameraFront
	//if (isRoamStarted == false)
	//{
	//	return GetInitialView();
	//}
	//else if (isRoamStarted == true)
	//{
		return GetSpaceView();
	//}
	
}
mat4 Camera::GetInitialView()
{
	// camPam.cameraPos + camPam.cameraFront
	 return glm::lookAt(camPam.cameraPos, glm::vec3(0.0f), camPam.cameraUp);
}

mat4 Camera::GetSpaceView()
{
	
    return glm::lookAt(camPam.cameraPos, camPam.cameraPos + camPam.cameraFront, camPam.cameraUp);
}


mat4 Camera::GetProjection(EngWindPtr engineWindow)
{
	//TODO: Put near and far place as members of the camera internals
	return glm::perspective(camPam.fov, engineWindow->AspectRatio(), 0.1f, 20000.0f);
}

void Camera::SetArbitraryPosition(vec3 pos)
{
	camPam.cameraPos.x = pos.x;
	camPam.cameraPos.z = pos.z;
}



//Freezes Y, so you cant move up
void Camera::freezeY()
{
	
	if (isYFrozen == true)
	{
		camPam.cameraPos.y = 1.7f;
	}
	else if (isYFrozen == false)
	{
		
	}

}


// Front and Back Operations
void Camera::increaseZ(float camSpeed)
{
	
	camPam.cameraPos += camPam.cameraFront * camSpeed;
	freezeY();

	
}
void Camera::decreaseZ(float camSpeed)
{
	camPam.cameraPos -= camPam.cameraFront * camSpeed;
	freezeY();
}

//Strafe Left and Right Operations
void Camera::decreaseX(float camSpeed)
{
	camPam.cameraPos -=  glm::normalize(glm::cross(camPam.cameraFront, camPam.cameraUp)) * camSpeed;
	freezeY();
}

void Camera::increaseX(float camSpeed)
{
	camPam.cameraPos += glm::normalize(glm::cross(camPam.cameraFront, camPam.cameraUp)) * camSpeed;
	freezeY();
}


void Camera::debugMode(bool isOn)
{
	if (isOn == true)
	{
		CAM_SPEED_CONSTANT = 8000;
		isYFrozen = false;
	}
	else if (isOn == false)
	{
		camPam.cameraPos = glm::vec3(0.0f, 5.0f, 3.0f);
		CAM_SPEED_CONSTANT = 1000;
		isYFrozen = true;
	}
}

void Camera::startRoam()
{
	if (isRoamStarted == false)
	{
		camPam.cameraPos = glm::vec3(0.0f, 5.0f, 3.0f);
		isRoamStarted = true;
	}
		
}




