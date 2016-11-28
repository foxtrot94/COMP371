#pragma once

#include "base/Objects.h"

#include <vector>
#include <glew.h>
#include <random>

//#include "SOIL.h" 
// Uncomment this once merged with master

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/constants.hpp>
#include <gtc/quaternion.hpp>
//#include <gtx/quaternion.hpp>

#define PI 3.14159265

class Tree : ProceduralObject {
private:
	// Variables useful for this class
	int maxNumVertices;
    int numOfSides;
    float baseRadius;
    float radiusStep;
    float minRadius;
    float branchRoundness;
    float segmentLength;
    float twisting;
    float branchProb;

	glm::vec3 position;

	std::vector<vec3> treeVertices, treeNormals, treeColors;
	std::vector<vec2> treeTextureCoord;

	size_t verticesCount();
    
    std::vector<float> uv;
    std::vector<float> vertices;
    std::vector<int> indices;
    std::vector<float> ringShape;
    
	void generateTree();

	void setTreeRingShape();

	void branch(glm::quat quaternion, glm::vec3 position, int lastRingVertexIndex, float radius, float textCoordV);

public:
	Tree();
    
	~Tree();
};

// Source: http://www.wasabimole.com/procedural-tree/how-to-generate-a-procedural-tree-in-unity-3d/
// Source: https://www.assetstore.unity3d.com/en/#!/content/32907