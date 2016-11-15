#include "base\Objects.h"

ProceduralObject::ProceduralObject() {

}

ProceduralObject::~ProceduralObject() {

}

GLMesh * WorldGenericObject::getMesh()
{
	return &(this->mesh);
}
