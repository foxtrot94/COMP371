#include "Plane.h"

void Plane::Generate()
{
	//Make a new plane. Fixed size for now
	vec3 topRight(500.f,0.f, 500.f);
	vec3 bottomLeft(-topRight);
	
	std::vector<vec3> vertices;
	vertices.push_back(vec3(bottomLeft));
	vertices.push_back(vec3(topRight));
	vertices.push_back(vec3(bottomLeft.x, 0.f, topRight.z));
	vertices.push_back(vec3(bottomLeft));
	vertices.push_back(vec3(topRight.x, 0.f, bottomLeft.z));
	vertices.push_back(vec3(topRight));

	vec3 brown(150.f/255.f, 75.f/255.f, 0);
	
	std::vector<vec3> colors(vertices.size(), brown);

	mesh.setVertices(vertices);
	mesh.setVertexColor(colors);
	

}
