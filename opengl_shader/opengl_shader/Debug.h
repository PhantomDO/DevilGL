#pragma once
#include <string>

class Debug
{
public:
	static void Log(const std::string& log);
	static void LogError(const std::string& log);
};
