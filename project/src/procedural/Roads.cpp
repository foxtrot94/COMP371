#include "procedural\Road.h"
#include "Bounds.h"

Road::Road()
{
}

Road::~Road()
{
}

void Road::Generate(Bounds perimeter) 
{

}

void Road::init()
{
	// "..\..\models\raw\Roads\Roads.obj"
	mesh = loadOBJ("models\\raw\\Roads\\Roads.obj");
}