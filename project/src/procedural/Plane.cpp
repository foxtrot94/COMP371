#include "procedural/Plane.h"

void Plane::Generate(Bounds perimeter)
{
	//Make a new plane. Fixed size for now
	vec3 topRight(perimeter.getXmax(),0.f, perimeter.getYmax());
	vec3 bottomLeft(perimeter.getXmin(), 0.f, perimeter.getYmin());
	
	std::vector<vec3> vertices;
	vertices.push_back(vec3(bottomLeft));
	vertices.push_back(vec3(topRight));
	vertices.push_back(vec3(bottomLeft.x, 0.f, topRight.z));
	vertices.push_back(vec3(bottomLeft));
	vertices.push_back(vec3(topRight.x, 0.f, bottomLeft.z));
	vertices.push_back(vec3(topRight));

	vec3 brown(87.f/255.f, 59.f/255.f, 12.f/255.f);
	
	std::vector<vec3> colors(vertices.size(), brown);

	mesh.setVertices(vertices);
	mesh.setVertexColor(colors);
}
