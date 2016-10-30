#pragma once

#include <vector>

#include "..\glew\glew.h"	// include GL Extension Wrangler
#include "..\glfw\glfw3.h"	// include GLFW helper library
#include "..\glm\glm.hpp"

#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

class WorldGenericObject;

//Main class for dealing with the OpenGL renderer and displaying stuff on screen
class Renderer {
private:
	int windowHeight, windowWidth;

public:
	//Initialize GLFW
	void Initialize();

	//Draw an ordered list of points
	void Draw(std::vector<float> Points, GLenum DrawMode);

	//Draw an ordered list of points
	void Draw(WorldGenericObject* Object);
};