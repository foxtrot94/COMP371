#include "procedural/Plane.h"

void Plane::Generate(Bounds perimeter)
{
	//Make a new plane. Fixed size for now
	vec3 topRight(perimeter.getXmax(),0.f, perimeter.getYmax());
	vec3 bottomLeft(perimeter.getXmin(), 0.f, perimeter.getYmin());

	//TODO: Adjust for texel correction and repetition
	float xCorrection = 1.0;
	float yCorrection = 1.0;
	if (perimeter.getXlength()>perimeter.getYlength()) {
		xCorrection = perimeter.getXlength() / perimeter.getYlength();
		if (xCorrection<2.f) {
			xCorrection = 1.f;
		}
	}
	else {
		yCorrection = perimeter.getYlength() / perimeter.getXlength();
		if (xCorrection<2.f) {
			xCorrection = 1.f;
		}
	}
	
	std::vector<vec3> vertices;
	std::vector<vec2> texels;
	
	vertices.push_back(vec3(bottomLeft));
	texels.push_back(vec2(0.0f,1.0f*yCorrection));

	vertices.push_back(vec3(topRight));
	texels.push_back(vec2(1.0f*xCorrection,0.0f*yCorrection));

	//Top left
	vertices.push_back(vec3(bottomLeft.x, 0.f, topRight.z));
	texels.push_back(vec2(0.0f,0.f));

	vertices.push_back(vec3(bottomLeft));
	texels.push_back(vec2(0.0f, 1.0f*yCorrection));

	//Bottom Right
	vertices.push_back(vec3(topRight.x, 0.f, bottomLeft.z));
	texels.push_back(vec2(1.0f*xCorrection,1.0f*yCorrection));

	vertices.push_back(vec3(topRight));
	texels.push_back(vec2(1.0f, 0.0f));

	vec3 brown(87.f/255.f, 59.f/255.f, 12.f/255.f);
	
	std::vector<vec3> colors(vertices.size(), brown);

	mesh.setVertices(vertices);
	mesh.setVertexColor(colors);
	mesh.setMeshTexels(texels);
}
