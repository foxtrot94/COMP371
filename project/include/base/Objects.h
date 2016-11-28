#pragma once

#include <vector>

#include "base/Mesh.h"
#include "base/Texture.h"

#include "Bounds.h"
#include "Utils.h"

//Just an object that can be handled by the engine and placed in world
class EngineObject {
protected:
	//Main model matrix
	mat4 Model;
	//Cached rotation along each axis (DEBUG)
	vec3 rotations;
	//Cached scale (DEBUG)
	vec3 scales;

public:
	//ctor
	EngineObject() {}
	//virt dtor
	virtual ~EngineObject() {}

	//Retrieve the model matrix
	inline mat4* getModel() { return &Model; }

	//Apply a translation
	void translate(float x, float y, float z);
	void translate(vec3 translation);

	//Rotate the object by a certain amount.
	//Use Degrees. Function will transform to radians
	void rotate(vec3 rotation);
	void rotateX(float amt);
	void rotateY(float amt);
	void rotateZ(float amt);

	//Scale the objects
	void scale(vec3 scale);

	//Update the object at each tick
	virtual void Update(const float& deltaTime) {}

	//DO NOT USE UNLESS ENABLING SSE COMPILATION
	//void * operator new (size_t size){
	//	return _aligned_malloc(sizeof(EngineObject),16);
	//}
	//void operator delete(void* mem) {
	//	_aligned_free(mem);
	//}
	
	//getters
	vec3 getTranslation();
	vec3 getRotations() { return rotations; }
	vec3 getScale() { return scales; }
};

//Main object
class WorldGenericObject : public EngineObject {
protected:
	//Primary mesh which makes up this object
	GLMesh mesh;
	GLTexture texture;

public:
	GLMesh* getMesh();
	GLTexture* getTexture();

	void assignMesh(GLMesh* newMesh);
	void assignTexture(GLTexture* newTexture);

	//Assign this object a particular color
	void paintColor(vec3 Color);
};

//Base Procedural Class for creating any Procedural Object
class ProceduralObject : public WorldGenericObject {
private:
	//Identifier/Primary Key
	static long ID;

	//Seed used to generate object
	long seed;

	//TODO: Incorporate RNG here

protected:
	//Bounds perimeter;

public:
	//Function that should be called to instance this object
	//Override and place procedural logic
	virtual void Generate(Bounds perimeter) = 0;

	//Default ctor
	ProceduralObject(/*Bounds bounds, vec3 center*/);

	//Virt dtor
	virtual ~ProceduralObject();

	virtual bool wasGenerated();
};