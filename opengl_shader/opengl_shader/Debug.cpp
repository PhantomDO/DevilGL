#include "Debug.h"

#include <iostream>
#include <ostream>

void Engine::Debug::Log(const std::string& log)
{
	std::cout << log << std::endl;
}

void Engine::Debug::LogError(const std::string& log)
{
	std::cerr << log << std::endl;
}
