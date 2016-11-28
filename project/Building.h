#pragma once

#include "base/Objects.h"

#include <time.h>

class Building : ProceduralObject {
private:
	// Variables useful for this class
	std::vector<vec3> buildingVertices, colors;
	float curHeight, curSize;
	int angleNumber, diagNumber;

	glm::vec2 buildingPos;

	void buildCube(float size, vec3 pos) { // pos is the offset
		// Front square
		buildingVertices.push_back(vec3(buildingPos.x + pos.x - size, pos.y + size, buildingPos.y + pos.z - size)); //top left near 
		buildingVertices.push_back(vec3(buildingPos.x + pos.x - size, pos.y - size, buildingPos.y + pos.z - size)); //bottom left near
		buildingVertices.push_back(vec3(buildingPos.x + pos.x + size, pos.y - size, buildingPos.y + pos.z - size)); //bottom right near
		buildingVertices.push_back(vec3(buildingPos.x + pos.x - size, pos.y + size, buildingPos.y + pos.z - size)); //top left near
		buildingVertices.push_back(vec3(buildingPos.x + pos.x + size, pos.y - size, buildingPos.y + pos.z - size)); //bottom right near
		buildingVertices.push_back(vec3(buildingPos.x + pos.x + size, pos.y + size, buildingPos.y + pos.z - size)); //top right near
		// Back square
		buildingVertices.push_back(vec3(buildingPos.x + pos.x - size, pos.y + size, buildingPos.y + pos.z + size)); //top left far 
		buildingVertices.push_back(vec3(buildingPos.x + pos.x - size, pos.y - size, buildingPos.y + pos.z + size)); //bottom left far
		buildingVertices.push_back(vec3(buildingPos.x + pos.x + size, pos.y - size, buildingPos.y + pos.z + size)); //bottom right far
		buildingVertices.push_back(vec3(buildingPos.x + pos.x - size, pos.y + size, buildingPos.y + pos.z + size)); //top left far
		buildingVertices.push_back(vec3(buildingPos.x + pos.x + size, pos.y - size, buildingPos.y + pos.z + size)); //bottom right far
		buildingVertices.push_back(vec3(buildingPos.x + pos.x + size, pos.y + size, buildingPos.y + pos.z + size)); //top right far
		// Left square
		buildingVertices.push_back(vec3(buildingPos.x + pos.x - size, pos.y + size, buildingPos.y + pos.z - size)); //top left near 
		buildingVertices.push_back(vec3(buildingPos.x + pos.x - size, pos.y - size, buildingPos.y + pos.z - size)); //bottom left near
		buildingVertices.push_back(vec3(buildingPos.x + pos.x - size, pos.y - size, buildingPos.y + pos.z + size)); //bottom left far
		buildingVertices.push_back(vec3(buildingPos.x + pos.x - size, pos.y - size, buildingPos.y + pos.z + size)); //bottom left far
		buildingVertices.push_back(vec3(buildingPos.x + pos.x - size, pos.y + size, buildingPos.y + pos.z - size)); //top left near
		buildingVertices.push_back(vec3(buildingPos.x + pos.x - size, pos.y + size, buildingPos.y + pos.z + size)); //top left far
		// Right square
		buildingVertices.push_back(vec3(buildingPos.x + pos.x + size, pos.y + size, buildingPos.y + pos.z - size)); //top right near
		buildingVertices.push_back(vec3(buildingPos.x + pos.x + size, pos.y - size, buildingPos.y + pos.z - size)); //bottom right near
		buildingVertices.push_back(vec3(buildingPos.x + pos.x + size, pos.y - size, buildingPos.y + pos.z + size)); //bottom right far
		buildingVertices.push_back(vec3(buildingPos.x + pos.x + size, pos.y - size, buildingPos.y + pos.z + size)); //bottom right far
		buildingVertices.push_back(vec3(buildingPos.x + pos.x + size, pos.y + size, buildingPos.y + pos.z + size)); //top right far
		buildingVertices.push_back(vec3(buildingPos.x + pos.x + size, pos.y + size, buildingPos.y + pos.z - size)); //top right near
		// Top square
		buildingVertices.push_back(vec3(buildingPos.x + pos.x + size, pos.y + size, buildingPos.y + pos.z - size)); //top right near
		buildingVertices.push_back(vec3(buildingPos.x + pos.x + size, pos.y + size, buildingPos.y + pos.z + size)); //top right far
		buildingVertices.push_back(vec3(buildingPos.x + pos.x - size, pos.y + size, buildingPos.y + pos.z + size)); //top left far
		buildingVertices.push_back(vec3(buildingPos.x + pos.x - size, pos.y + size, buildingPos.y + pos.z + size)); //top left far
		buildingVertices.push_back(vec3(buildingPos.x + pos.x - size, pos.y + size, buildingPos.y + pos.z - size)); //top left near 
		buildingVertices.push_back(vec3(buildingPos.x + pos.x + size, pos.y + size, buildingPos.y + pos.z - size)); //top right near
		// Bottom square
		buildingVertices.push_back(vec3(buildingPos.x + pos.x + size, pos.y - size, buildingPos.y + pos.z - size)); //bottom right near
		buildingVertices.push_back(vec3(buildingPos.x + pos.x + size, pos.y - size, buildingPos.y + pos.z + size)); //bottom right far
		buildingVertices.push_back(vec3(buildingPos.x + pos.x - size, pos.y - size, buildingPos.y + pos.z + size)); //bottom left far
		buildingVertices.push_back(vec3(buildingPos.x + pos.x - size, pos.y - size, buildingPos.y + pos.z + size)); //bottom left far
		buildingVertices.push_back(vec3(buildingPos.x + pos.x - size, pos.y - size, buildingPos.y + pos.z - size)); //bottom left near
		buildingVertices.push_back(vec3(buildingPos.x + pos.x + size, pos.y - size, buildingPos.y + pos.z - size)); //bottom right near

		// TODO: Texture Coordinates instead of colors
		for(int i = 0; i < 6; i++) {
			colors.push_back(vec3(1.f, 0.f, 0.f));
			colors.push_back(vec3(0.f, 1.f, 0.f));
			colors.push_back(vec3(0.f, 0.f, 1.f));
			colors.push_back(vec3(1.f, 0.f, 0.f));
			colors.push_back(vec3(0.f, 1.f, 0.f));
			colors.push_back(vec3(0.f, 0.f, 1.f));
		}
	}

	// Make this one not repeatable cause ugly x)
	void fourPillarsPattern(float& curSize, float& curHeight, bool copyP) {
		// Determine size
		float size = curSize / 2;
		if(!copyP) {
			float size = findSize((curSize / 2));
		}
		// Calculate offset from size
		float offSet = size;
		// Set size
		size = size - (size * 0.2f);
		// Adjust height
		curHeight += size;
		// Build pattern
		buildCube(size, vec3(-offSet, curHeight, -offSet));
		buildCube(size, vec3(-offSet, curHeight, offSet));
		buildCube(size, vec3(offSet, curHeight, -offSet));
		buildCube(size, vec3(offSet, curHeight, -offSet));
		// Adjust current size and height
		curHeight += size;
		curSize = size * 2;
	}

	void cubePattern(float& curSize, float& curHeight, bool copyP) {
		// Determine new size
		float size = curSize;
		if(!copyP) {
			size = findSize(curSize);
		}
		// Adjust current size
		curHeight += size;
		// Build pattern
		buildCube(size, vec3(0, curHeight, 0));
		// Adjust current size and height
		curHeight += size;
		curSize = size;
	}

	void halfCubeHeightPattern(float& curSize, float& curHeight, bool copyP) {
		// Determine size
		float size = curSize / 2;
		if(!copyP) {
			size = findSize(curSize / 2);
		}
		// Adjust height
		curHeight += size;
		// Build pattern
		buildCube(size, vec3(-size, curHeight, -size));
		buildCube(size, vec3(-size, curHeight,  size));
		buildCube(size, vec3( size, curHeight, -size));
		buildCube(size, vec3( size, curHeight,  size));
		// Adjust current size and height
		curHeight += size;
		curSize = size * 2;
	}

	void plusSignPattern(float& curSize, float& curHeight, bool copyP) {
		// Determine size
		float size = curSize / 3;
		if(!copyP) {
			size = findSize(size);
		}
		// Adjust height
		curHeight += size;
		// Build pattern
		buildCube(size, vec3(-2 * size, curHeight, 0));
		buildCube(size, vec3( 2 * size, curHeight, 0));
		buildCube(size, vec3( 0, curHeight, -2 * size));
		buildCube(size, vec3( 0, curHeight,  2 * size));
		// Adjust current size and height
		curHeight += size;
		curSize = size * 3;
	}

	void diagonalOrHalfPattern(float& curSize, float& curHeight, bool copyP) {
		// Determine size and pattern
		float size;
		if(!copyP) {
			size = findSize(curSize / 2);
			diagNumber = randNumber(1, 6); // Number to determine which pattern we use
		}
		else {
			size = curSize / 2;
		}
		// Adjust height
		curHeight += size;
		// Build pattern
		switch(diagNumber) {
			case 1 :
				buildCube(size, vec3(-size, curHeight, -size));
				buildCube(size, vec3( size, curHeight,  size));
				break;
			case 2 :
				buildCube(size, vec3( size, curHeight, -size));
				buildCube(size, vec3(-size, curHeight,  size));
				break;
			case 3 :
				buildCube(size, vec3(-size, curHeight, -size));
				buildCube(size, vec3(-size, curHeight,  size));
				break;
			case 4 :
				buildCube(size, vec3( size, curHeight, -size));
				buildCube(size, vec3( size, curHeight,  size));
				break;
			case 5 :
				buildCube(size, vec3(-size, curHeight, -size));
				buildCube(size, vec3( size, curHeight, -size));
				break;
			case 6 :
				buildCube(size, vec3( size, curHeight,  size));
				buildCube(size, vec3( size, curHeight, -size));
				break;
		}
		// Adjust current size and height
		curHeight += size;
		curSize = size * 2;
	}

	void anglePattern(float& curSize, float& curHeight, bool copyP) {
		// Determine size
		float size;
		if(!copyP) {
			size = findSize(curSize / 2);
			angleNumber = randNumber(1, 4);
		}
		else {
			size = curSize / 2;
		}
		// Adjust height
		curHeight += size;
		// Build pattern
		for(int i = 0; i < 3; i++)
		{
			if(i == angleNumber) {
				break;
			}
			switch(angleNumber) {
				case 1 :
					buildCube(size, vec3(-size, curHeight, -size));
					break;
				case 2 :
					buildCube(size, vec3( size, curHeight,  size));
					break;
				case 3 :
					buildCube(size, vec3( size, curHeight, -size));
					break;
				case 4 :
					buildCube(size, vec3(-size, curHeight,  size));
					break;
			}
		}
		// Adjust current size and height
		curHeight += size;
		curSize = size * 2;
	}

	float findSize(float s) {
		float newSize = 0;
		// Random to see if we change the size or if we keep the same size
		if (randNumber(1, 3) == 2) {
			return s;
		}
		else { // If it's the latter find a smaller size
			if(randNumber(1, 3) == 2) {
				newSize = s - (s * 0.125f);
			}
			else {
				newSize = s - (s * 0.25f);
			}
		}
		return newSize;
	}

	int randNumber(int min, int max)
	{
		int xRand;
		xRand = min + (rand() % max); // Randomizing the number between lowRange and highRange.
		return xRand;
	}

public:
	Building(int buildingH, float buildingS, glm::vec2 buildingP) {
		// TODO: Add texture mapping

		// Set the random generator seed
		srand(time(0));

		bool copyPattern, patternWasPillars = false;
		int switchPattern = randNumber(1, 6);
		// Initialize building position on the plane (x and z coordinates)
		buildingPos = buildingP;
		// Initial height
		curHeight = 0;
		// Initialize default curSize and curHeight
		curSize = buildingS; // Initialize the building size (1.0f = 1 meter)
		curHeight += curSize; // Initialize the building at a height of 0.0f on the y axis

		// Algorithm to make a building
		for(int countBuildingH = 0; countBuildingH < buildingH; countBuildingH++) {
			copyPattern = false;
			// 66.67% chance to copy last pattern
			if(randNumber(1, 3) != 3) {
				copyPattern = true;
			}
			// Random a new pattern
			if(!copyPattern) {
				// Make sure you don't rambom non compatible patterns to go over fou pillar pattern
				if(patternWasPillars)
				{
					switchPattern = randNumber(1, 4);
				}
				else {
					switchPattern = randNumber(1, 6);
				}
			}
			switch(switchPattern) {
				case 1 :
					patternWasPillars = true;
					fourPillarsPattern(curSize, curHeight, copyPattern);
					break;
				case 2 :
					cubePattern(curSize, curHeight, copyPattern);
					break;
				case 3 :
					halfCubeHeightPattern(curSize, curHeight, copyPattern);
					break;
				case 4 :
					plusSignPattern(curSize, curHeight, copyPattern);
					break;
				case 5 :
					diagonalOrHalfPattern(curSize, curHeight, copyPattern);
					break;
				case 6 :
					anglePattern(curSize, curHeight, copyPattern);
					break;
				default :
					break;
			}
		}
		// Set the building mesh
		mesh.setVertices(buildingVertices);
		mesh.setVertexColor(colors);

		Model = mat4(1.0f);
	}

	~Building() {}
};
