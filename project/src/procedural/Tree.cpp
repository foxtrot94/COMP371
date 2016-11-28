#include "Tree.h"

Tree::Tree()
{
	// Initialize class variables
	position = glm::vec3(0, -0.5f, 0);

	// For customization of trees these should be variables passed in when a new tree is called/created
	//Seed; // Random seed on which the generation is based : for debug purposes
	maxNumVertices = 65000; // Maximum number of vertices for the tree mesh : Range(1024, 65000)
	numOfSides = 16; // Number of sides for tree : Range(3, 32)
	baseRadius = 2.0f; // Base radius in meters : Range(0.25f, 4f)
	radiusStep = 0.9f; // Controls how quickly radius decreases : Range(0.75f, 0.95f)
	minRadius = 0.02f; // Minimum radius for the tree's smallest branches : Range(0.01f, 0.2f
	branchRoundness = 0.8f; // Controls how round branches are : Range(0f, 1f)
	segmentLength = 0.5f; // Length of branch segments : Range(0.1f, 2f)]
	twisting = 10.0f; // How much branches twist : Range(0f, 40f)
	branchProb = 0.1f; // Branch probability : Range(0f, 0.25f)

	// Generate a new tree mesh
	generateTree();
	// Calculate tree vertices, normals and uv from the previous function to pass in to our mesh class
	treeVertices.clear();
	treeColors.clear();
	treeNormals.clear();
	treeTextureCoord.clear();
	for (int i = 0; i < indices.size(); i += 3) {
		int a = indices[i];
		int b = indices[i + 1];
		int c = indices[i + 2];

		glm::vec3 v1(vertices[a * 3], vertices[a * 3 + 1], vertices[a * 3 + 2]);
		glm::vec3 v2(vertices[b * 3], vertices[b * 3 + 1], vertices[b * 3 + 2]);
		glm::vec3 v3(vertices[c * 3], vertices[c * 3 + 1], vertices[c * 3 + 2]);
		// Assign Vertices
		treeVertices.push_back(vec3(v1.x, v1.y, v1.z));
		treeVertices.push_back(vec3(v2.x, v2.y, v2.z));
		treeVertices.push_back(vec3(v3.x, v3.y, v3.z));
		// Assign Colors : initial debug purposes when we have no textures
		treeColors.push_back(vec3(1.f, 0.f, 0.f));
		treeColors.push_back(vec3(0.f, 1.f, 0.f));
		treeColors.push_back(vec3(0.f, 0.f, 1.f));
		// Calculate normals
		glm::vec3 v2v1 = v2 - v1;
		glm::vec3 v3v1 = v3 - v1;
		glm::vec3 normal = glm::cross(v2v1, v3v1);
		// Assign Normals
		treeNormals.push_back(vec3(normal.x, normal.y, normal.z));
		treeNormals.push_back(vec3(normal.x, normal.y, normal.z));
		treeNormals.push_back(vec3(normal.x, normal.y, normal.z));
		// Assign Texture Coordinates
		treeTextureCoord.push_back(vec2(uv[a * 2], uv[a * 2 + 1]));
		treeTextureCoord.push_back(vec2(uv[b * 2], uv[b * 2 + 1]));
		treeTextureCoord.push_back(vec2(uv[c * 2], uv[c * 2 + 1]));
	}

	// Load and set the tree texture
	// TODO:

	// Send in mesh vertices
	mesh.setVertices(treeVertices);
	mesh.setVertexColor(treeColors); // debug purposes when we have no textures

	// Send in mesh normals
	//mesh.setVertices(treeNormals);

	// Send in mesh texture coordinates
	//mesh.setTexels(treeTextureCoord);
	//mesh.setTexture(somethingsomething);

	Model = mat4(1.f);
}

Tree::~Tree()
{
}

size_t Tree::verticesCount() {
	return vertices.size() / 3;
}

void Tree::generateTree() {
	// Make sure vectors are empty
	uv.clear();
	vertices.clear();
	indices.clear();
	ringShape.clear();
	// Initial shape for the number of sides
	setTreeRingShape();
	// Recursive: creates ring vertices for the tree trunk
	// We use quaternion libraries to do rotations
	branch(glm::quat(1.0f, 0.0f, 0.0f, 0.0f), position, -1, baseRadius, 0.0f);
}

void Tree::setTreeRingShape() { // Initial ring shape
	float k = (1.0f - branchRoundness) * 0.5f;
	for (int i = 0; i < numOfSides; i++) {
		ringShape.push_back(10.0f - ((float)rand() / (RAND_MAX) - 0.5f) * k);
	}
	ringShape.push_back(ringShape[0]); // Center
}

void Tree::branch(glm::quat quaternion, glm::vec3 position, int lastRingVertexIndex, float radius, float textCoordV) {
	glm::vec3 offset;
	glm::vec2 textCoord(0.0f, textCoordV);
	float textureStepU = 1.0f / numOfSides;
	float angInc = 2.0f * (float)PI * textureStepU;
	float ang = 0.0f;

	// Add ring vertices
	for (int i = 0; i <= numOfSides; i++, ang += angInc) {
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

	if (lastRingVertexIndex >= 0) { // To protext us when there is only 1 ring vertex
		// Create a new branch segment quads (two triangles) formed between the last 2 vertex rings
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

	// Base case; end branch when minRadius or max number of vertices is reached
	radius *= radiusStep;
	if (radius < minRadius || verticesCount() + numOfSides >= maxNumVertices) {
		// Central vertex
		vertices.push_back(position.x);
		vertices.push_back(position.y);
		vertices.push_back(position.z);
		// Create a branch cap (twist the texture to create a ring effect just like what you see when you cut a tree)
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

	// Recursive case; continue branch generation and apply twist
	textCoordV += 0.0625f * (segmentLength + segmentLength / radius);
	position += quaternion * glm::vec3(0.f, segmentLength, 0.f);

	float x = ((float)rand() / (RAND_MAX) - 0.5f) * twisting;
	float z = ((float)rand() / (RAND_MAX) - 0.5f) * twisting;

	glm::mat4 quatRotation = glm::mat4_cast(quaternion);
	quatRotation = glm::rotate(quatRotation, x, glm::vec3(1.f, 0.f, 0.f));
	quatRotation = glm::rotate(quatRotation, z, glm::vec3(0.f, 0.f, 1.f));
	glm::quat rotation = glm::quat_cast(quatRotation);

	lastRingVertexIndex = verticesCount() - numOfSides - 1;
	branch(rotation, position, lastRingVertexIndex, radius, textCoordV); // generate next part of the branch

	// Check if we add a new branch
	float random = (float)rand() / (RAND_MAX);
	float prob = radius < minRadius * 4 ? branchProb * 2.5 : branchProb;
	if (verticesCount() + numOfSides >= maxNumVertices || random > prob) {
		return; // No we do not
	}

	// Split into new branch
	x = (float)rand() / (RAND_MAX) * 70.f - 35.f;
	z = (float)rand() / (RAND_MAX) * 70.f - 35.f;

	quatRotation = glm::mat4_cast(quaternion);
	quatRotation = glm::rotate(quatRotation, x, glm::vec3(1.f, 0.f, 0.f));
	quatRotation = glm::rotate(quatRotation, z, glm::vec3(0.f, 0.f, 1.f));
	glm::quat branchRotation = glm::quat_cast(quatRotation);

	branch(branchRotation, position, lastRingVertexIndex, radius, textCoordV);
}