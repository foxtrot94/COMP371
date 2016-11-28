#pragma once

#include <vector>

#include "glm.hpp"
#include "Utils.h"

//Main class for abstracting the Textures
class GLTexture {
	//OpenGL Vertex Array Object
	uint glTexture;

	//Texture Pixel Vertices
	//std::vector<float> Texels;

	//Texture image data loaded from SOIL
	uchar* ImageData;

	//Original dimensions of the texture
	int width, height;

public:
	//ctor
	GLTexture();

	//dtor
	~GLTexture();

	//Check whether or not the Texture was loaded correctly
	bool isInRenderingContext();
	//Assign this texture data a GL Context
	void setContextTexture(uint glTex);

	//Load this texture from disk
	void loadImageData(std::string filename);

	//Read the set of vertices kept in Main Memory
	uchar* readImageData();

	//Retrieve dimensions of the window.
	int getWidth();
	int getHeight();

	//Get the context
	uint getContext() { return glTexture; }
};