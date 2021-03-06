#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <set>

#include "..\glew\glew.h"	// include GL Extension Wrangler
#include "..\glfw\glfw3.h"	// include GLFW helper library
#include "..\glm\glm.hpp"

#include "..\SkyBox.h"

#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include "Utils.h"


class WorldGenericObject;
class Camera;
class Shader;
class GLMesh;
class GLTexture;

//Main class for dealing with the OpenGL renderer and displaying stuff on screen
//tech debt: switch it up and put this as an interface for an underlying DirectX, OpenGL and Vulkan renderer
class Renderer {
public:
	//Inner struct for handling window contexts and updating them
	struct Window {
		GLFWwindow* glfwContext;
		int width, height;
		float fov;
		std::string name;
		//Ctor
		Window(GLFWwindow* window, int w, int h, std::string str) {
			glfwContext = window;
			width = w;
			height = h;
			name = str;
			//Default 
			fov = 90.f;
		}
		//Calculate Aspect Ratio
		inline float AspectRatio() {
			return ((float)width) / ((float)height);
		}
	};

protected:
	//Window Management
	Window* mainWindow;

	//Singleton instance
	static Renderer* singleton;

	//OpenGL Shader in Use
	Shader* shader;

	//OpenGL SkyBox Shader
	Shader* skyBoxShader;
	
	//SkyBox in use
	SkyBox* skybox;

	//List of elements being tracked in the OpenGL context
	std::vector<uint> ContextArrays;
	std::vector<uint> ContextBuffers;
	std::set<uchar*> RawTextureData;

	//Protected Ctor
	Renderer();

	//Send a mesh object to the GPU memory and renderer context
	bool AddToRenderingContext(GLMesh* mesh);

	bool AddToRenderingContext(GLTexture* texture);

public:
	//Singleton point of entry
	static Renderer* GetInstance();

	//Dtor
	~Renderer();

	//Initialize the renderer
	//Defaults to a standard 800x600 Window
	Window* Initialize(std::string windowName, const uint minWidth = 800, const uint minHeight = 600);

	//Retrieve the default drawing window
	Window* GetMainWindow();

	//Use a particular, compiled shader
	void UseShader(Shader* shader);

	//Use a particular, compiled skybox shader
	void UseSkyBoxShader(Shader* shader);

	void InitSkyBox();

	//Takes new parameters from camera before rendering - TODO: Replace with actual Camera class
	void UpdateCamera(mat4& view, mat4& projection);

	//Draw a single WorldGenericObject on screen
	void Render(WorldGenericObject* Object);

	//Batch draw of WorldGenericObjects on screen
	void Render(std::vector<WorldGenericObject*> Objects);

	//Draw the skybox cube
	void RenderSkyBox(Camera* camera);
};