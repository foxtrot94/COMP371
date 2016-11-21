#pragma once

#include "base/Objects.h"
#include <iostream>

//Replicates the learnopengl.com triangle in our framework
class TriangleTest : public WorldGenericObject {
private:
	float totalTime;
public:
	TriangleTest() {
		totalTime = 0.f;
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

	virtual void Update(const float& deltaTime) override {
		std::cout << totalTime << std::endl;
		this->translate(deltaTime * glm::sin(totalTime+glm::radians(90.f)), 0.f, 0.f);
		totalTime += deltaTime;
	}
};