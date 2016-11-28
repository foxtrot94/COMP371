#include "..\..\include\base\Texture.h"

GLTexture::GLTexture()
{
	glTexture = NULL;
	glTextureBuffer = NULL;
}

GLTexture::~GLTexture()
{
}

bool GLTexture::isInRenderingContext()
{
	return glTexture != NULL && glTextureBuffer != NULL;
}

bool GLTexture::isInitialized()
{
	return Texels.size()>0;
}

void GLTexture::setTexels(std::vector<float> texels)
{
	if (!isInitialized())
		this->Texels = texels;
}

void GLTexture::setTexels(std::vector<vec2> vec2Texels)
{
	if (!isInitialized())
	{
		convertVec2ToVecFloat(vec2Texels, this->Texels);
	}
		
}

std::vector<float> GLTexture::readLocalTexels()
{
	return this->Texels;
}

void GLTexture::setImageData(std::vector<unsigned char*> pixels, int width, int height)
{
	this->ImageData = pixels;
	this->width = width;
	this->height = height;
}

std::vector<unsigned char*> GLTexture::readImageData()
{
	return this->ImageData;
}

int GLTexture::getWidth()
{
	return this->width;
}

int GLTexture::getHeight()
{
	return this->height;
}

void GLTexture::setContextTexture(uint glTex)
{
	glTexture = glTex;
}

uint GLTexture::readContextTexture()
{
	return glTexture;
}

void GLTexture::DestroyContext()
{
	//TODO: This should destroy the object and cleanup
}

void GLTexture::setContextBuffer(uint texelBuffer, uint size)
{
	if (size != Texels.size())
	{
		//exception caught
		return;
	}
	this->glTextureBuffer = texelBuffer;
}

void GLTexture::convertVec2ToVecFloat(std::vector<vec2> &inputVector, std::vector<float> &outputVector)
{
	outputVector.clear();
	outputVector.resize(0);
	for (vec2 texel : inputVector){
		outputVector.push_back(texel.s);
		outputVector.push_back(texel.t);
	}
}