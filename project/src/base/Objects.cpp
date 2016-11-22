#include "base/Objects.h"
#include "gtc/matrix_transform.hpp"

ProceduralObject::ProceduralObject() {

}

ProceduralObject::~ProceduralObject() {

}

GLMesh * WorldGenericObject::getMesh()
{
	return &(this->mesh);
}

void WorldGenericObject::assignMesh(GLMesh * newMesh)
{
	this->mesh = *newMesh;
}

void EngineObject::translate(float x, float y, float z)
{
	vec3 translation(x, y, z);
	Model = glm::translate(Model, translation);
}

void EngineObject::translate(vec3 translation)
{
	Model = glm::translate(Model, translation);
}

void EngineObject::rotate(vec3 rotation)
{
	rotateX(rotation.x);
	rotateY(rotation.y);
	rotateZ(rotation.z);
}

void EngineObject::rotateX(float amt)
{
	float rads = glm::radians(amt);
	rotations.x += rads;
	Model = glm::rotate(Model, rads, vec3(1.f,0.f,0.f));
}

void EngineObject::rotateY(float amt)
{
	float rads = glm::radians(amt);
	rotations.y += rads;
	Model = glm::rotate(Model, rads, vec3(0.f, 1.f, 0.f));
}

void EngineObject::rotateZ(float amt)
{
	float rads = glm::radians(amt);
	rotations.z += rads;
	Model = glm::rotate(Model, rads, vec3(0.f, 0.f, 1.f));
}

void EngineObject::scale(vec3 scale)
{
	scales = scale;
	Model = glm::scale(Model, scale);
}

vec3 EngineObject::getTranslation()
{
	return vec3(Model[3]);
}
