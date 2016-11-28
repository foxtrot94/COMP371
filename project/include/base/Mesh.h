#pragma once

#include <vector>

#include "glm.hpp"
#include "Utils.h"

//Main class for abstracting rendering details
class GLMesh {
	//OpenGL Vertex Array Object
	uint glArray;
	//Primary Vertex Buffer Object
	uint glVertexBuffer;
	//Color Buffer Object
	uint glColorBuffer;
	//Texel Buffer Object
	uint glTexelBuffer;

	//Size of the mesh buffers. It is assumed they all correspond among each other
	//This set when assigning the OpenGL buffers
	uint commonBufferSize;

	//Size of the Texel Buffer
	uint texelBufferSize;

	//Local Array of Vertices
	std::vector<vec3> Vertices;

	//Local Array of Color
	std::vector<vec3> Colors;

	//Local Array of Texels
	std::vector<vec2> Texels;

public:
	//ctor
	GLMesh();

	//dtor
	~GLMesh();

	//Check whether or not the mesh has been sent to OpenGL 
	//(i.e. a call to glGenBuffers was made and the VAO and VBO attributes are non-null)
	bool isInRenderingContext();

	//Check if there are even points in this mesh and it can be drawn
	bool isInitialized();

	//Populate this mesh with a set of vertices
	void setVertices(std::vector<vec3> vertices);
	//Read the set of vertices kept in Main Memory
	std::vector<vec3> readLocalVertices();

	//Set Colors for each vertex being sampled
	void setVertexColor(std::vector<vec3> colors);
	//Read all colors of the vertex being sampled
	std::vector<vec3> readLocalVertexColor();

	//Set Texels for the mesh
	void setMeshTexels(std::vector<vec2> texels);
	//Read all colors of the vertex being sampled
	std::vector<vec2> readLocalMeshTexels();

	//Assign the mesh a VAO Pointer
	void setContextArray(uint VAO);

	//Assign the mesh buffers - Both are expected to be of the same size
	void setContextBuffer(uint vertexBuffer, uint colorBuffer, uint size);
	//Sets the Texel Buffer
	void setTexelBuffer(uint texelBuffer, uint size);
	//Adjusts the UV mapping so textures can be fitted correctly
	void adjustTexelMappingConstant(float amt);

	//Destroy the mesh glContext
	void DestroyContext();

	//Retrieve the VAO for Rendering by OpenGL
	uint getContextArray() { return glArray; }

	//Get Size
	uint getBufferSize() { return commonBufferSize; }
};