#pragma once

#include <string>
#include "..\..\soil\SOIL.h"
#include "glm.hpp"

//Simple representation of an image. Data should be a 3-tuple of floats such that dataSize is width*height*pixelCount
struct SimpleImage {
	float* Data;
	int dataSize;
	int pixelInfoCount;
	int width;
	int height;
};

//Check if a file exists
bool FileExists(std::string filename);

///////////////////////////////////////
//Typedefs & shorthands
///////////////////////////////////////

typedef unsigned int uint;

//Common glm namespaced items being used
using glm::mat4;
using glm::vec3;
using glm::vec2;
using glm::normalize;
