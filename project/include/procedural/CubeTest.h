#pragma once

#include "base/Objects.h"
#include <iostream>

//Replicates the learnopengl.com triangle in our framework
class CubeTest : public ProceduralObject {
private:
	float totalTime;
public:
	CubeTest() {}
	void Generate(Bounds perimeter) override;
	~CubeTest() {}


};