#pragma once

#include <vector>

#include "base/Mesh.h"
#include "Utils.h"

//Just an object that can be handled by the engine and placed in world
class EngineObject {
public: //For now
	glm::mat4 Model;
};

//Main object
class WorldGenericObject : public EngineObject {
protected:
	//Primary mesh which makes up this object
	GLMesh mesh;

public:
	GLMesh* getMesh();


	//Commenting out for now - Use only if short on time.
	//friend class Renderer;
};

//Base Procedural Class for creating any Procedural Object
class ProceduralObject : public WorldGenericObject {
private:
	//Seed used to generate object
	long seed;

	//TODO: Incorporate RNG here

	//TODO: Anything else to track state

protected:
	//Function that should be called to instance this object
	//Override and place procedural logic
	virtual void Generate() = 0;

public:
	//Default ctor
	ProceduralObject(); //TODO: Remove and replace with ctor that takes bounds

	//Virt dtor
	virtual ~ProceduralObject();
};