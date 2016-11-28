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

void GLMesh::setVertexColor(std::vector<vec3> colors)
{
	this->Colors = colors;
}

std::vector<vec3> GLMesh::readLocalVertexColor()
{
	return this->Colors;
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

void GLMesh::DestroyContext()
{
	//TODO: This should destroy the object and cleanup
}
