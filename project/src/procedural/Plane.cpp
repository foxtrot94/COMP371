#include "procedural/Plane.h"

void Plane::Generate(Bounds perimeter)
{
	//Make a new plane. Fixed size for now
	vec3 topRight(perimeter.getXmax(),0.f, perimeter.getYmax());
	vec3 bottomLeft(perimeter.getXmin(), 0.f, perimeter.getYmin());
	
	std::vector<vec3> vertices;
	std::vector<vec2> texels;
	
	vertices.push_back(vec3(bottomLeft));
	texels.push_back(vec2(0.0f,1.0f));

	vertices.push_back(vec3(topRight));
	texels.push_back(vec2(1.0f,0.0f));

	//Top left
	vertices.push_back(vec3(bottomLeft.x, 0.f, topRight.z));
	texels.push_back(vec2(0.0f,0.f));

	vertices.push_back(vec3(bottomLeft));
	texels.push_back(vec2(0.0f, 1.0f));

	//Bottom Right
	vertices.push_back(vec3(topRight.x, 0.f, bottomLeft.z));
	texels.push_back(vec2(1.0f,1.0f));

	vertices.push_back(vec3(topRight));
	texels.push_back(vec2(1.0f, 0.0f));

	vec3 brown(87.f/255.f, 59.f/255.f, 12.f/255.f);
	
	std::vector<vec3> colors(vertices.size(), brown);

	mesh.setVertices(vertices);
	mesh.setVertexColor(colors);
	mesh.setMeshTexels(texels);
}
