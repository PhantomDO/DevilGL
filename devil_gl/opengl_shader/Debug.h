#pragma once
#include <string>

namespace Engine
{
	class Debug
	{
	public:
		static void Log(const std::string& log);
		static void LogError(const std::string& log);
	};

}
