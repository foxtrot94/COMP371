#include "base/Mesh.h"

GLMesh::GLMesh()
{
	glArray = NULL;
	glVertexBuffer = NULL;
	glColorBuffer = NULL;
}

GLMesh::~GLMesh()
{

}

bool GLMesh::isInRenderingContext()
{
	return glArray!=NULL && glColorBuffer!=NULL && glVertexBuffer!=NULL;
}

bool GLMesh::isInitialized()
{
	return Vertices.size()>0 && Colors.size()>0;
}

void GLMesh::setVertices(std::vector<vec3> vertices)
{
	if (!isInitialized())
		this->Vertices = vertices;
}

std::vector<vec3> GLMesh::readLocalVertices()
{
	return this->Vertices;
}

void GLMesh::setColor(glm::vec3 color)
{
	colorObject = color;
}

glm::vec3 GLMesh::getColor()
{
	return glm::vec3(colorObject);
}

void GLMesh::setVertexColor(std::vector<vec3> colors)
{
	this->Colors = colors;
}

std::vector<vec3> GLMesh::readLocalVertexColor()
{
	return this->Colors;
}

void GLMesh::setMeshTexels(std::vector<vec2> texels)
{
	Texels = texels;
}

std::vector<vec2> GLMesh::readLocalMeshTexels()
{
	return Texels;
}

void GLMesh::setContextArray(uint VAO)
{
	if(glArray==NULL)
		glArray = VAO;
}

void GLMesh::setContextBuffer(uint vertexBuffer, uint colorBuffer, uint size)
{
	if (size != Vertices.size()) {
		//std::current_exception
		return;
	}
	glVertexBuffer = vertexBuffer;
	glColorBuffer = colorBuffer;
	commonBufferSize = size;
}

void GLMesh::setTexelBuffer(uint texelBuffer, uint size)
{
	glTexelBuffer = texelBuffer;
	texelBufferSize = size;
}

void GLMesh::adjustTexelMappingConstant(float amt)
{
	for (vec2& texelDescriptor : Texels) {
		texelDescriptor *= amt;
	}
}

void GLMesh::DestroyContext()
{
	//TODO: This should destroy the object and cleanup
}
