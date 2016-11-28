#include "main.h"
#include "utils.h"

#include "base\Engine.h"

#include "procedural\Grid.h"

//Entry point
int main()
{
	std::cout << "" << std::endl;
	WorldEngine* ShinSekai = new WorldEngine();

	ShinSekai->Init("Shin Sekai - COMP371 OpenGL Project");
	ShinSekai->LoadWorld();
	ShinSekai->Run();

	delete ShinSekai;
	return 0;
}