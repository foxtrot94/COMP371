#include "CubeTest.h"

void CubeTest::Generate(Bounds perimeter)
{
	totalTime = 0.f;
	std::vector<vec3> vertices;

	vertices.push_back(vec3(0.5f, -0.5f, -0.5f));
	vertices.push_back(vec3(0.5f, -0.5f, -0.5f));
	vertices.push_back(vec3(0.5f, 0.5f, -0.5f));
	vertices.push_back(vec3(0.5f, 0.5f, -0.5f));
	vertices.push_back(vec3(-0.5f, 0.5f, -0.5f));
	vertices.push_back(vec3(-0.5f, -0.5f, -0.5f));

	vertices.push_back(vec3(-0.5f, -0.5f, 0.5f));
	vertices.push_back(vec3(0.5f, -0.5f, 0.5f));
	vertices.push_back(vec3(0.5f, 0.5f, 0.5f));
	vertices.push_back(vec3(0.5f, 0.5f, 0.5f));
	vertices.push_back(vec3(-0.5f, 0.5f, 0.5f));
	vertices.push_back(vec3(-0.5f, -0.5f, 0.5f));

	vertices.push_back(vec3(-0.5f, 0.5f, 0.5f));
	vertices.push_back(vec3(-0.5f, 0.5f, -0.5f));
	vertices.push_back(vec3(-0.5f, -0.5f, -0.5f));
	vertices.push_back(vec3(-0.5f, -0.5f, -0.5f));
	vertices.push_back(vec3(-0.5f, -0.5f, 0.5f));
	vertices.push_back(vec3(-0.5f, 0.5f, 0.5f));

	vertices.push_back(vec3(0.5f, 0.5f, 0.5f));
	vertices.push_back(vec3(0.5f, 0.5f, -0.5f));
	vertices.push_back(vec3(0.5f, -0.5f, -0.5f));
	vertices.push_back(vec3(0.5f, -0.5f, -0.5f));
	vertices.push_back(vec3(0.5f, -0.5f, 0.5f));
	vertices.push_back(vec3(0.5f, 0.5f, 0.5f));

	vertices.push_back(vec3(-0.5f, -0.5f, -0.5f));
	vertices.push_back(vec3(0.5f, -0.5f, -0.5f));
	vertices.push_back(vec3(0.5f, -0.5f, 0.5f));
	vertices.push_back(vec3(0.5f, -0.5f, 0.5f));
	vertices.push_back(vec3(-0.5f, -0.5f, 0.5f));
	vertices.push_back(vec3(-0.5f, -0.5f, -0.5f));

	vertices.push_back(vec3(-0.5f, 0.5f, -0.5f));
	vertices.push_back(vec3(0.5f, 0.5f, -0.5f));
	vertices.push_back(vec3(0.5f, 0.5f, 0.5f));
	vertices.push_back(vec3(0.5f, 0.5f, 0.5f));
	vertices.push_back(vec3(-0.5f, 0.5f, 0.5f));
	vertices.push_back(vec3(-0.5f, 0.5f, -0.5f));

	//colors.push_back(vec3(1.f, 0.f, 0.f));
	//colors.push_back(vec3(0.f, 1.f, 0.f));
	vec3 brown(0.f / 255.f, 0.f / 255.f, 200.f / 255.f);

	//NOT ACTUALLY COLORS BUT NORMALS
	std::vector<vec3> colors;

	colors.push_back(vec3(0.0f, 0.0f, -1.0f));
	colors.push_back(vec3(0.0f, 0.0f, -1.0f));
	colors.push_back(vec3(0.0f, 0.0f, -1.0f));
	colors.push_back(vec3(0.0f, 0.0f, -1.0f));
	colors.push_back(vec3(0.0f, 0.0f, -1.0f));
	colors.push_back(vec3(0.0f, 0.0f, -1.0f));

	colors.push_back(vec3(0.0f, 0.0f, 1.0f));
	colors.push_back(vec3(0.0f, 0.0f, 1.0f));
	colors.push_back(vec3(0.0f, 0.0f, 1.0f));
	colors.push_back(vec3(0.0f, 0.0f, 1.0f));
	colors.push_back(vec3(0.0f, 0.0f, 1.0f));
	colors.push_back(vec3(0.0f, 0.0f, 1.0f));

	colors.push_back(vec3(-1.0f, 0.0f, 0.0f));
	colors.push_back(vec3(-1.0f, 0.0f, 0.0f));
	colors.push_back(vec3(-1.0f, 0.0f, 0.0f));
	colors.push_back(vec3(-1.0f, 0.0f, 0.0f));
	colors.push_back(vec3(-1.0f, 0.0f, 0.0f));
	colors.push_back(vec3(-1.0f, 0.0f, 0.0f));

	colors.push_back(vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(vec3(1.0f, 0.0f, 0.0f));

	colors.push_back(vec3(0.0f, -1.0f, 0.0f));
	colors.push_back(vec3(0.0f, -1.0f, 0.0f));
	colors.push_back(vec3(0.0f, -1.0f, 0.0f));
	colors.push_back(vec3(0.0f, -1.0f, 0.0f));
	colors.push_back(vec3(0.0f, -1.0f, 0.0f));
	colors.push_back(vec3(0.0f, -1.0f, 0.0f));

	colors.push_back(vec3(0.0f, 1.0f, 0.0f));
	colors.push_back(vec3(0.0f, 1.0f, 0.0f));
	colors.push_back(vec3(0.0f, 1.0f, 0.0f));
	colors.push_back(vec3(0.0f, 1.0f, 0.0f));
	colors.push_back(vec3(0.0f, 1.0f, 0.0f));
	colors.push_back(vec3(0.0f, 1.0f, 0.0f));

	mesh.setVertices(vertices);
	mesh.setVertexColor(colors);
	mesh.setColor(glm::vec3(0.f / 255.f, 0.f / 255.f, 200.f / 255.f));

	Model = mat4(1.f);
};
