#pragma once
#include <memory>
#include <string>
#include <filesystem>
#include <sstream>

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

	static std::vector<std::string> GetAssetFromDirectory(const std::string& directory)
	{
		std::vector<std::string> paths;
		for (const auto& entry : std::filesystem::directory_iterator(directory))
		{
			std::string path = entry.path().generic_u8string();
			std::replace(path.begin(), path.end(), '\\', '/');
			paths.emplace_back(path);
		}
		return paths;
	}

	static std::string ChoiceListFromDirectory(const std::string& directory, std::vector<std::string>& assets)
	{
		assets = GetAssetFromDirectory(directory);

		if (assets.empty()) 
		{
			Debug::LogError(Tools::StringFormat("No assets found in %s", directory));
			return "";
		}

		uint32_t count = 0;
		std::stringstream ss;
		ss << "Choose between those assets : " << std::endl;
		for (auto& asset : assets)
		{
			ss << "\t- [" << count << "] " << asset << std::endl;
			count++;
		}

		ss << "Which one (-1 if you don't choose) ? ";

		return ss.str();
	}
};
