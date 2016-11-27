#pragma once

#include <vector>

#include "Utils.h"
#include "objloader.hpp"

#include "..\glew\glew.h"	// include GL Extension Wrangler
#include "..\glfw\glfw3.h"	// include GLFW helper library
#include "..\glm\glm.hpp"
#include "CImg.h"
//#include "..\..\soil\SOIL.h" // include Simple OpenGL Image Library


class SkyBox
{
private:
	//OpenGL Vertex Array Object (for SkyBox)
	uint glArray;

	//Primary Vertex Buffer Object
	uint glVertexBuffer;

	//Local Array of Vertices
	std::vector<vec3> vertices;

	//Loads images for the CubeMap texture
	std::vector<const char*> loadTextureImages();
	
	//Fills and send a CubeMap texture
	void sendCubeMapTextures(std::vector<const char*> faces);

	//Loads Texture Images onto CubeMap (necessary for sendCubeMapTextures)
	uint loadCubeMap(std::vector<const char*> faces);

public:
	SkyBox();
	~SkyBox();

	//Populate skybox with the vertices
	void loadVertices();

	//Generate Vertex Array Object
	void genArray();

	//Retrieve the VAO for Rendering by OpenGL
	uint getContextArray();

	//Send Vertex Buffer Data to the GPU
	void sendVertexBuffer();

	//Main function that loads textures and sends it to the GPU
	void loadTextures();

	//Return the size of the vertex buffer
	uint getVertexBufferSize();
};