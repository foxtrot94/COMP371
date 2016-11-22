#include "Plane.h"

void Plane::Generate()
{
	//Make a new plane. Fixed size for now
	vec2 topRight(500.f, 500.f);
	vec2 bottomLeft(-topRight);
	
	std::vector<vec3> vertices;
	vertices.push_back(vec3(bottomLeft, 0.0f));
	vertices.push_back(vec3(topRight, 0.0f));
	vertices.push_back(vec3(bottomLeft.x, topRight.y, 0.0f));
	vertices.push_back(vec3(bottomLeft, 0.0f));
	vertices.push_back(vec3(topRight.x, bottomLeft.y, 0.0f));
	vertices.push_back(vec3(topRight, 0.0f));

	vec3 brown(150.f/255.f, 75.f/255.f, 0);
	
	std::vector<vec3> colors(vertices.size(), brown);

	mesh.setVertices(vertices);
	mesh.setVertexColor(colors);
	

}