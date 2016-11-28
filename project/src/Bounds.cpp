#include "Bounds.h"

Bounds::Bounds(float xmin, float xmax, float ymin, float ymax)
{
	bottomLeft = vec2(xmin, ymin);
	topRight = vec2(xmax, ymax);
	center = vec3(0.f);
}

Bounds::Bounds(vec2 min, vec2 max)
{
	bottomLeft = min;
	topRight = max;
	center = vec3(0.f);
}

Bounds::Bounds(vec3 min, vec3 max)
{
	bottomLeft = vec2(min.x, min.z);
	topRight = vec2(max.x, max.z);
	center = vec3(0.f);
}

float Bounds::getXmax()
{
	return topRight.x;
}

float Bounds::getYmax()
{
	return topRight.y;
}

float Bounds::getXmin()
{
	return bottomLeft.x;
}

float Bounds::getYmin()
{
	return bottomLeft.y;
}

float Bounds::getXlength()
{
	return (topRight.x - bottomLeft.x);
}

float Bounds::getYlength()
{
	return (topRight.y - bottomLeft.y);
}

float Bounds::getArea()
{
	return (topRight.x-bottomLeft.x)*(topRight.y-bottomLeft.y);
}

void Bounds::setCenter(vec3 point)
{
	center = point;
}

vec3 Bounds::getCenter()
{
	return center;
}
