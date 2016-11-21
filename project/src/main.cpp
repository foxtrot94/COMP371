#include "main.h"
#include "utils.h"

#include "base\Engine.h"

//Entry point
int main()
{
	LightweightEngine* le = new LightweightEngine();
	le->Init("Shin Sekai - COMP371 OpenGL Project");
	le->Run();
	return 0;
}