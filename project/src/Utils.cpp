#include <iostream>
#include <fstream>
#include <vector>

#include "utils.h"

//Checks if a file is on disk and is readable
bool FileExists(std::string filename)
{
	std::ifstream test(filename);
	bool status = test.is_open() && test.good();
	test.close();
	return status;
}
