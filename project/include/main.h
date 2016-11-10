#pragma once

#include "stdafx.h"

#include "..\glew\glew.h"	// include GL Extension Wrangler
#include "..\glfw\glfw3.h"	// include GLFW helper library
#include "..\glm\glm.hpp"

#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include "CImg.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>

//TODO: Remove Globals
//Globals are bad, but we can at least keep them all in one place
#ifndef __GLOBALS__
#define __GLOBALS__

const GLuint WIDTH = 800, HEIGHT = 600;

extern glm::vec3 cameraTranslation;
extern glm::vec3 cameraDirectionPoint;

extern glm::vec3 objectRotation;

extern float framerate;
extern float deltaTime;

#endif