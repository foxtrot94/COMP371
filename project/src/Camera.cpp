#include "Camera.h"


//Get delta time from update and use it for operations
float Camera::GetCameraSpeed()
{
	return cameraSpeed;
}

void Camera::SetCameraSpeed(float time)
{
	cameraSpeed = time * CAM_SPEED_CONSTANT;
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



// Front and Back Operations
void Camera::increaseZ(float camSpeed)
{
	
	camPam.cameraPos += camPam.cameraFront * camSpeed;
	
}
void Camera::decreaseZ(float camSpeed)
{
	camPam.cameraPos -= camPam.cameraFront * camSpeed;
}

//Strafe Left and Right Operations
void Camera::decreaseX(float camSpeed)
{
	camPam.cameraPos -=  glm::normalize(glm::cross(camPam.cameraFront, camPam.cameraUp)) * camSpeed;
}

void Camera::increaseX(float camSpeed)
{
	camPam.cameraPos += glm::normalize(glm::cross(camPam.cameraFront, camPam.cameraUp)) * camSpeed;
}

