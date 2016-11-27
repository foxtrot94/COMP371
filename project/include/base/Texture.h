#pragma once

#include <vector>

#include "glm.hpp"
#include "Utils.h"

//Main class for abstracting the Textures
//TECH DEBT: This has many of the same attributes as GLMesh
//			 Unfortunately didn't give much thought into this one
class GLTexture {
	//OpenGL Vertex Array Object
	uint glTexture;

	//Texture Pixel Vertices
	std::vector<float> Texels;

	//Texture image data
	std::vector<const char*> ImageData;
	//Original dimensions of the texture
	int width, height;

public:
	//ctor
	GLTexture();

	//dtor
	~GLTexture();

	//Check whether or not the mesh has been sent to OpenGL 
	//(i.e. a call to glGenBuffers was made and the VAO and VBO attributes are non-null)
	bool isInRenderingContext();

	//Check if there are even texels and an image and it can be drawn
	bool isInitialized();

	//Populate this with a set of texels (expects a tuple)
	void setTexels(std::vector<float> texels);
	//Read the set of vertices kept in Main Memory
	std::vector<float> readLocalTexels();

	//Populate this with a set of texels
	void setImageData(std::vector<const char*> pixels, int width, int height);
	//Read the set of vertices kept in Main Memory
	std::vector<const char*> readImageData();
	//Retrieve dimensions of the window.
	int getWidth();
	int getHeight();

	//Assign the mesh a VAO Pointer
	void setContextTexture(uint glTex);

	//Destroy the mesh glContext
	void DestroyContext();

	//Assign the mesh buffers - Both are expected to be of the same size
	void setContextBuffer(uint texelBuffer, uint size);

};