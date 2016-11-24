#pragma once

#include "base/Objects.h"

// Replicates the learnopengl.com triangle in our framework
class TriangleTest : WorldGenericObject {
private:

public:
	TriangleTest() {
		std::vector<vec3> vertices, colors;
		vertices.push_back(vec3(-0.5f, -0.5f, 0.0f));
		vertices.push_back(vec3(0.5f, -0.5f, 0.0f));
		vertices.push_back(vec3(0.0f, 0.5f, 0.0f));

		colors.push_back(vec3(1.f, 0.f, 0.f));
		colors.push_back(vec3(0.f, 1.f, 0.f));
		colors.push_back(vec3(0.f, 0.f, 1.f));

		mesh.setVertices(vertices);
		mesh.setVertexColor(colors);

		Model = mat4(1.f);
	}

	~TriangleTest() {}
};