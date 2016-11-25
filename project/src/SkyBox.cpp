#include "..\include\SkyBox.h"


SkyBox::SkyBox()
{
	glArray = NULL;
	glVertexBuffer = NULL;
}


SkyBox::~SkyBox()
{
}

void SkyBox::loadVertices()
{
	//loading skybox from obj
	std::vector<glm::vec3> skybox_normals; //unused
	std::vector<glm::vec2> skybox_UVs; //unused

	bool result = loadOBJ("cube.obj", this->vertices, skybox_normals, skybox_UVs);
}

void SkyBox::genArray()
{
	if (glArray == NULL) {
		glGenVertexArrays(1, &glArray);
	}
}

void SkyBox::sendVertexBuffer()
{
	if (glArray == NULL) 
	{
		genArray();
	}
	if (vertices.size() == 0)
	{
		loadVertices();
	}
	else {
		glBindVertexArray(glArray);

		glGenBuffers(1, &glVertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, glVertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices.front(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);
	}
}

void SkyBox::loadTextures(){
	sendCubeMapTextures(loadTextureImages());
}

std::vector<const char*> SkyBox::loadTextureImages()
{
		//prepare skybox cubemap
		std::vector<const char*> faces;
		faces.push_back("right.jpg");
		faces.push_back("left.jpg");
		faces.push_back("top.jpg");
		faces.push_back("bottom.jpg");
		faces.push_back("back.jpg");
		faces.push_back("front.jpg");

		glActiveTexture(GL_TEXTURE1);

		return faces;
}

void SkyBox::sendCubeMapTextures(std::vector<const char*> faces)
{
	glActiveTexture(GL_TEXTURE1);
	uint cubemapTexture = loadCubeMap(faces);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
}

uint SkyBox::loadCubeMap(std::vector<const char*> faces)
{
	uint textureID;
	glGenTextures(1, &textureID);

	int width, height;
	unsigned char* image;

	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	for (uint i = 0; i < faces.size(); ++i)
	{
		//load image from memory
		image = SOIL_load_image(faces[i], &width, &height, 0, SOIL_LOAD_RGB);

		//send image to cubemap 
		glTexImage2D(
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
			GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image
			);

		SOIL_free_image_data(image); // remove currently loaded image from memory
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	return textureID;
}

uint SkyBox::getContextArray()
{
	return glArray;
}

uint SkyBox::getVertexBufferSize()
{
	return vertices.size();
}