#include "main.h"
#include "utils.h"

#include "base\Engine.h"

//Entry point
int main()
{
	std::cout << "" << std::endl;
	LightweightEngine* le = new LightweightEngine();

	le->Init("Shin Sekai - COMP371 OpenGL Project");
	le->LoadWorld();
	le->Run();

	delete le;
	return 0;
}