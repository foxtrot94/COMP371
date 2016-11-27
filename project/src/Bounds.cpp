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
	//Not yet implemented
	__debugbreak();
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

float Bounds::getArea()
{
	return (topRight.x-bottomLeft.x)*(topRight.y-bottomLeft.x);
}

void Bounds::setCenter(vec3 point)
{
	center = point;
}

vec3 Bounds::getCenter()
{
	return center;
}
