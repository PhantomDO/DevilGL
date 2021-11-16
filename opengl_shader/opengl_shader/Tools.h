#pragma once
#include <memory>
#include <string>

class Tools
{
public:
	template<typename ... Args>
	static std::string StringFormat(const std::string& format, Args ... args)
	{
		const int stringSize = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1;
		if (stringSize <= 0) throw "Error during formating";
		const auto size = static_cast<size_t>(stringSize);
		auto buffer = std::make_unique<char[]>(size);
		std::snprintf(buffer.get(), size, format.c_str(), args ...);
		// Return the stringBuffer without the \0
		return std::string(buffer.get(), buffer.get() + size - 1);
	}
};
