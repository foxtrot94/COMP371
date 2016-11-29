#pragma once

#include "base/Objects.h"
//#include <stdlib.h>
#include <time.h>

//#include "SOIL.h" 
// Uncomment this once merged with master

class Building : public ProceduralObject {
private:
	// Variables useful for this class
	std::vector<vec3> buildingVertices, buildingNormals;
	std::vector<vec2> buildingUV;
	float curHeight, curSize;
	int angleNumber, diagNumber;

	glm::vec2 buildingPos;

	// Class funtions
	void buildCube(float size, vec3 pos);

	void fourPillarsPattern(float& curSize, float& curHeight, bool copyP);

	void cubePattern(float& curSize, float& curHeight, bool copyP);

	void halfCubeHeightPattern(float& curSize, float& curHeight, bool copyP);

	void plusSignPattern(float& curSize, float& curHeight, bool copyP);

	void diagonalOrHalfPattern(float& curSize, float& curHeight, bool copyP);

	void anglePattern(float& curSize, float& curHeight, bool copyP);

	float findSize(float s);

	int randNumber(int min, int max);

public:

	Building();

	~Building();

	void Generate(Bounds perimeter);
};
