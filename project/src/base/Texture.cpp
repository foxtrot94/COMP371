#include "..\..\include\base\Texture.h"

GLTexture::GLTexture()
{
}

GLTexture::~GLTexture()
{
}

bool GLTexture::isInRenderingContext()
{
	return false;
}

bool GLTexture::isInitialized()
{
	return false;
}

void GLTexture::setTexels(std::vector<float> texels)
{
}

std::vector<float> GLTexture::readLocalTexels()
{
	return std::vector<float>();
}

void GLTexture::setImageData(std::vector<const char*> pixels, int width, int height)
{
	return;
}

std::vector<const char*> GLTexture::readImageData()
{
	return std::vector<const char*>();
}

int GLTexture::getWidth()
{
	return 0;
}

int GLTexture::getHeight()
{
	return 0;
}

void GLTexture::setContextTexture(uint glTex)
{
	glTexture = glTex;
}

void GLTexture::DestroyContext()
{
}

void GLTexture::setContextBuffer(uint texelBuffer, uint size)
{
}
