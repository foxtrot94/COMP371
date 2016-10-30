#pragma once

#include <vector>
#include "typedefs.h"
#include "glm.hpp"

//Just an object that can be put on the world
class GenericObject {
	glm::mat4 Model;

	friend class Renderer;
};

//Main object
class WorldGenericObject : public GenericObject {
private:
	uint VertexBufferObject;
	uint VertexArrayObject;
	std::vector<float> Vertices;

	friend class Renderer;
};