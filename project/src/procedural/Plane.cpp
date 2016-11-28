#include "procedural/Plane.h"
#include <fstream>
#include <iostream>

void Plane::Generate(Bounds perimeter)
{
	//Make a new plane. Fixed size for now
	vec3 topRight(perimeter.getXmax(),0.f, perimeter.getYmax());
	vec3 bottomLeft(perimeter.getXmin(), 0.f, perimeter.getYmin());
	
	std::vector<vec3> vertices;
	vertices.push_back(vec3(bottomLeft));
	vertices.push_back(vec3(topRight));
	vertices.push_back(vec3(bottomLeft.x, 0.f, topRight.z)); //top left
	vertices.push_back(vec3(bottomLeft));
	vertices.push_back(vec3(topRight.x, 0.f, bottomLeft.z)); //bottom right
	vertices.push_back(vec3(topRight)); 

	std::vector<vec2> texels;
	texels.push_back(vec2(0.0f, 0.0f)); //BL
	texels.push_back(vec2(1.0f, 1.0f)); //TR
	texels.push_back(vec2(0.0f, 1.0f));

	texels.push_back(vec2(0.0f, 0.0f));
	texels.push_back(vec2(1.0f, 0.0f));
	texels.push_back(vec2(1.0f, 1.0f));
	
	system("cd");
	int width, height;


	std::ifstream f("grass.jpg");
	if (!f.is_open()) {
		#if _DEBUG
			//Made this debug break to avoid debugging missing files. Check them to see what's wrong
			__debugbreak();
		#endif
	}
	f.close();

	unsigned char* image = SOIL_load_image("grass2.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	std::vector<unsigned char*> imageVector; imageVector.push_back(image);
	
	vec3 brown(87.f/255.f, 59.f/255.f, 12.f/255.f);
	
	std::vector<vec3> colors(vertices.size(), brown);
	
	mesh.setVertices(vertices);
	mesh.setVertexColor(colors);
	texture.setTexels(texels);
	texture.setImageData(imageVector, width, height);

}
