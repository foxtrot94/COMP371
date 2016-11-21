#include "main.h"
#include "utils.h"

#include "base\Engine.h"

//Entry point
int main()
{
	LightweightEngine* le = new LightweightEngine();
	le->Init();
	le->Run();
	return 0;
}