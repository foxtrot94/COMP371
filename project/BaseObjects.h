#pragma once

#include <vector>

#include "utils.h"

//Just an object that can be put on the world
class EngineObject {
	glm::mat4 Model;
};

//Main object
class WorldGenericObject : public EngineObject {
private:
	uint VertexBufferObject;
	uint VertexArrayObject;
	std::vector<float> Vertices;

	//Commenting out for now - Use only if short on time.
	//friend class Renderer;
};