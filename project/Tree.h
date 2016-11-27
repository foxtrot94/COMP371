#pragma once

#include "base/Objects.h"

#include <vector>
#include <glew.h>
#include <random>

//#include "SOIL.h"
//#include "Shader.h"
//#include "Camera.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/constants.hpp>
#include <gtc/quaternion.hpp>
//#include <gtx/quaternion.hpp>

#define PI 3.14159265

class Tree : WorldGenericObject {
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

	std::vector<vec3> colors, treeVertices;

    size_t verticesCount() {
        return vertices.size() / 3;
    }
    
    std::vector<GLfloat> uv;
    std::vector<GLfloat> vertices;
    
    std::vector<GLuint> indices;
    std::vector<float> ringShape;
    
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	GLuint texture;
	   
	void generateTree() {
		setTreeRingShape();
		branch(glm::quat(1.f, 0.f, 0.f, 0.f), position, -1, baseRadius, 0.f);
	}

	void setTreeRingShape() {
		float k = (1.0f - branchRoundness) * 0.5f;
		for (int i = 0; i < numOfSides; i++)
		{
			ringShape.push_back(10.f - ((float)rand() / (RAND_MAX) - 0.5f) * k);
		}
		ringShape.push_back(ringShape[0]);
	}

	void branch(glm::quat quaternion, glm::vec3 position, int lastRingVertexIndex, float radius, float textCoordV) {
		glm::vec3 offset;
		glm::vec2 textCoord(0.0f, textCoordV);
		float textureStepU = 1.0f / numOfSides;
		float angInc = 2.0f * PI * textureStepU;
		float ang = 0.0f;

		// Add ring vertices
		for(int i = 0; i <= numOfSides; i++, ang += angInc) {
			float r = ringShape[i] * radius;
			offset.x = r * cos(ang);
			offset.z = r * sin(ang);
			glm::vec3 vertexPos = position + quaternion * offset;

			vertices.push_back(vertexPos.x);
			vertices.push_back(vertexPos.y);
			vertices.push_back(vertexPos.z);

			uv.push_back(textCoord.x);
			uv.push_back(textCoord.y);

			textCoord.x += textureStepU;
		}

		if (lastRingVertexIndex >= 0)
		{
			// Create branch segment quad (two triangles)
			for (int currentRingVertexIndex = verticesCount() - numOfSides - 1; currentRingVertexIndex < verticesCount() - 1; currentRingVertexIndex++, lastRingVertexIndex++)
			{
				// First triangle
				indices.push_back(lastRingVertexIndex + 1); 
				indices.push_back(lastRingVertexIndex);
				indices.push_back(currentRingVertexIndex);
				// Second triangle
				indices.push_back(currentRingVertexIndex);
				indices.push_back(currentRingVertexIndex + 1);
				indices.push_back(lastRingVertexIndex + 1);
			}
		}

		// base case; end branch when minRadius or max number of vertices is reached
		radius *= radiusStep;
		if (radius < minRadius || verticesCount() + numOfSides >= maxNumVertices) {
			vertices.push_back(position.x);
			vertices.push_back(position.y);
			vertices.push_back(position.z);

			glm::vec2 capTextCoord = textCoord + glm::vec2(1.0f, 1.0f);
			uv.push_back(capTextCoord.x);
			uv.push_back(capTextCoord.y);

			for (int n = verticesCount() - numOfSides - 2; n < verticesCount() - 2; n++) {
				indices.push_back(n);
				indices.push_back(verticesCount() - 1);
				indices.push_back(n + 1);
			}
			return;
		}

		// recursive case; continue branch generation and apply twist
		textCoordV += 0.0625f * (segmentLength + segmentLength / radius);
		position += quaternion * glm::vec3(0.f, segmentLength, 0.f);

		float x = ((float)rand() / (RAND_MAX)-0.5f) * twisting;// * (PI / 180.f);
		float z = ((float)rand() / (RAND_MAX)-0.5f) * twisting;// * (PI / 180.f);

		glm::mat4 quatRotation = glm::mat4_cast(quaternion);
		quatRotation = glm::rotate(quatRotation, x, glm::vec3(1.f, 0.f, 0.f));
		quatRotation = glm::rotate(quatRotation, z, glm::vec3(0.f, 0.f, 1.f));
		glm::quat rotation = glm::quat_cast(quatRotation);

		lastRingVertexIndex = verticesCount() - numOfSides - 1;
		branch(rotation, position, lastRingVertexIndex, radius, textCoordV); // generate next part of the branch

		// Do we branch?
		float random = (float)rand() / (RAND_MAX);
		float prob = radius < minRadius * 4 ? branchProb * 2.5 : branchProb;
		if (verticesCount() + numOfSides >= maxNumVertices || random > prob) {
			return;
		}

		// Split into new branch
		x = (float)rand() / (RAND_MAX) * 70.f - 35.f;
		//x *= (PI / 180.f);
		z = (float)rand() / (RAND_MAX) * 70.f - 35.f;
		//z *= (PI / 180.f);

		quatRotation = glm::mat4_cast(quaternion);
		quatRotation = glm::rotate(quatRotation, x, glm::vec3(1.f, 0.f, 0.f));
		quatRotation = glm::rotate(quatRotation, z, glm::vec3(0.f, 0.f, 1.f));
		glm::quat branchRotation = glm::quat_cast(quatRotation);

		branch(branchRotation, position, lastRingVertexIndex, radius, textCoordV);
	}

public:
	//TRee(glm::vec3 _position) {
	Tree() {
		//position = _position;
		position = glm::vec3(0,-0.5f,0);

	    //Seed; // Random seed on which the generation is based
		maxNumVertices = 65000; // Maximum number of vertices for the tree mesh
		numOfSides = 16; // Number of sides for tree
		baseRadius = 2.0f; // Base radius in meters
		radiusStep = 0.9f; // Controls how quickly radius decreases
		minRadius = 0.02f; // Minimum radius for the tree's smallest branches
		branchRoundness = 0.8f; // Controls how round branches are
		segmentLength = 0.5f; // Length of branch segments
		twisting = 20.0f; // How much branches twist
		branchProb = 0.1f; // Branch probability
	
		generateTree();

		//std::vector<GLfloat> uvvertices;

		std::vector<vec3> treeNormals;
		std::vector<vec2> treeTextureCoord;

		for (int i = 0; i < indices.size(); i += 3) {
			int a = indices[i];
			int b = indices[i + 1];
			int c = indices[i + 2];

			glm::vec3 v1(vertices[a * 3], vertices[a * 3 + 1], vertices[a * 3 + 2]);
			glm::vec3 v2(vertices[b * 3], vertices[b * 3 + 1], vertices[b * 3 + 2]);
			glm::vec3 v3(vertices[c * 3], vertices[c * 3 + 1], vertices[c * 3 + 2]);
			// Vertices
			treeVertices.push_back(vec3(v1.x, v1.y, v1.z));
			treeVertices.push_back(vec3(v2.x, v2.y, v2.z));
			treeVertices.push_back(vec3(v3.x, v3.y, v3.z));

			// Colors
			colors.push_back(vec3(1.f, 0.f, 0.f));
			colors.push_back(vec3(0.f, 1.f, 0.f));
			colors.push_back(vec3(0.f, 0.f, 1.f));

			// Calculate normals
			glm::vec3 v2v1 = v2 - v1;
			glm::vec3 v3v1 = v3 - v1;
			glm::vec3 normal = glm::cross(v2v1, v3v1);
			// Normals
			treeNormals.push_back(vec3(normal.x, normal.y, normal.z));
			treeNormals.push_back(vec3(normal.x, normal.y, normal.z));
			treeNormals.push_back(vec3(normal.x, normal.y, normal.z));

			// Texture Coordinates
			treeTextureCoord.push_back(vec2(uv[a * 2], uv[a * 2 + 1]));
			treeTextureCoord.push_back(vec2(uv[b * 2], uv[b * 2 + 1]));
			treeTextureCoord.push_back(vec2(uv[c * 2], uv[c * 2 + 1]));
		}

		// Set the building mesh
		/*for (int i = 0; i < vertices.size(); i += 3) {

			treeVertices.push_back(vec3(vertices[i], vertices[i] + 1, vertices[i] + 2));

			colors.push_back(vec3(1.f, 0.f, 0.f));
			colors.push_back(vec3(0.f, 1.f, 0.f));
			colors.push_back(vec3(0.f, 0.f, 1.f));
		}*/

		mesh.setVertices(treeVertices);
		mesh.setVertexColor(colors);

		Model = mat4(1.f);
	}
    
	~Tree() {}

};

// Source: http://www.wasabimole.com/procedural-tree/how-to-generate-a-procedural-tree-in-unity-3d/
// Source: https://www.assetstore.unity3d.com/en/#!/content/32907