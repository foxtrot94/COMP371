#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "..\glew\glew.h"	// include GL Extension Wrangler
#include "..\glfw\glfw3.h"	// include GLFW helper library
#include "..\glm\glm.hpp"

#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include "Utils.h"


class WorldGenericObject;
class Shader;
class GLMesh;

//Main class for dealing with the OpenGL renderer and displaying stuff on screen
//tech debt: switch it up and put this as an interface for an underlying DirectX, OpenGL and Vulkan renderer
class Renderer {
public:
	//Inner struct for handling window contexts and updating them
	struct Window {
		GLFWwindow* glfwContext;
		int width, height;
		std::string name;
		Window(GLFWwindow* window, int w, int h, std::string str) {
			glfwContext = window;
			width = w;
			height = h;
			name = str;
		}
	};

protected:
	//Window Management
	int windowHeight, windowWidth;
	Window* mainWindow;

	//Singleton instance
	static Renderer* singleton;

	//OpenGL Shader Class wrapper
	Shader* shader;

	//Send a mesh object to the GPU memory and renderer context
	bool AddToRenderingContext(GLMesh* mesh);
public:
	//Protected Ctor
	Renderer(); //Debug purposes only

	//Dtor
	~Renderer();

	//Initialize the renderer
	Window* Initialize(std::string windowName, const unsigned int minHeight, const unsigned int minWidth);

	//Use a particular, compiled shader
	void UseShader(Shader* shader);

	//Takes new parameters from camera before rendering - TODO: Replace with actual Camera
	void UpdateCamera(mat4& view, mat4& projection);

	//Draw a single WorldGenericObject on screen
	void Render(WorldGenericObject* Object);

	//Draw a batch of WorldGenericObjects on screen
	void Render(std::vector<WorldGenericObject*> Objects);
};