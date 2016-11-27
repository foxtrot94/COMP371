#pragma once

#include "Utils.h"

//Defines a set of bounds in the real world
class Bounds {
	vec2 topRight;
	vec2 bottomLeft;

public:
	Bounds(float xmin, float xmax, float ymin, float ymax);
	Bounds(vec2 min, vec2 max);
	Bounds(vec3 min, vec3 max);

	float getXmax();
	float getYmax();
	float getXmin();
	float getYmin();

	float getArea();
};