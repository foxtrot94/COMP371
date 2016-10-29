#pragma once

#include "..\glfw\glfw3.h"	// include GLFW helper library
#include <string>

struct GLFWwindow;

// Have some common utils for general stuff

//Simple representation of an image. Data is a 3-tuple of floats such that dataSize is width*height*pixelCount
struct SimpleImage {
	float* Data;
	int dataSize;
	int pixelInfoCount;
	int width;
	int height;
};

//shorthand for unsigned int
typedef unsigned int uint;

//Check if a file exists
bool FileExists(std::string filename);

//Deals with initializing GLFW and setting input
bool AppInit(std::string windowName, const unsigned int minHeight, const unsigned int minWidth, GLFWwindow** outWindow);

//Open any shader file and just compile it. Returns the pointer value to where the shader is.
GLuint OpenAndCompile(std::string filename, GLuint GLShaderType);

//Link the shaders with a program object so they become usable.
//After this call, the pointers to the given shaders are freed and the program object in use is returned
GLuint UseShaders(GLuint vertexShader, GLuint fragmentShader);