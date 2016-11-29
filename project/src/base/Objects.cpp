#include <time.h>

#include "base/Objects.h"
#include "gtc/matrix_transform.hpp"

long ProceduralObject::ID = 0;

ProceduralObject::ProceduralObject(/*Bounds bounds, vec3 center*/)/* : perimeter(bounds)*/ {
	ID += 1;
	seed = time(NULL) + ID;
}

ProceduralObject::~ProceduralObject() {

}

bool ProceduralObject::wasGenerated()
{
	return this->mesh.isInitialized();
}

GLMesh * WorldGenericObject::getMesh()
{
	return &(this->mesh);
}

GLTexture * WorldGenericObject::getTexture()
{
	return &(this->texture);
}

void WorldGenericObject::assignMesh(GLMesh * newMesh)
{
	this->mesh = *newMesh;
}

void WorldGenericObject::assignTexture(GLTexture * newTexture)
{
	texture = *newTexture;
}

void WorldGenericObject::paintColor(vec3 Color)
{
	uint count = mesh.readLocalVertices().size();
	std::vector<vec3> colors(count, Color);
	mesh.setVertexColor(colors);
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
