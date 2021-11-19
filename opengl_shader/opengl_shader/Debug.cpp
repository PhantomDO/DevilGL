#include "Debug.h"

#include <iostream>
#include <ostream>

void Debug::Log(const std::string& log)
{
	std::cout << log << std::endl;
}

void Debug::LogError(const std::string& log)
{
	std::cerr << log << std::endl;
}
