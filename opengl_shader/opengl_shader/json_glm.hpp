
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace glm
{
	void to_json(json& j, const vec2& vec)
	{
		j = { {"x", vec.x }, {"y", vec.y} };
	}

	void from_json(const json& j, vec2& vec)
	{
		vec.x = j.at("x").get<double>();
		vec.y = j.at("y").get<double>();
	}

	void to_json(json& j, const vec3& vec)
	{
		j = { {"x", vec.x }, {"y", vec.y}, {"z", vec.z} };
	}

	void from_json(const json& j, vec3& vec)
	{
		vec.x = j.at("x").get<double>();
		vec.y = j.at("y").get<double>();
		vec.z = j.at("z").get<double>();
	}

	void to_json(json& j, const vec4& vec)
	{
		j = { {"x", vec.x }, {"y", vec.y}, {"z", vec.z}, {"w", vec.w} };
	}

	void from_json(const json& j, vec4& vec)
	{
		vec.x = j.at("x").get<double>();
		vec.y = j.at("y").get<double>();
		vec.z = j.at("z").get<double>();
		vec.w = j.at("w").get<double>();
	}

	void to_json(json& j, const quat& vec)
	{
		j = { {"w", vec.w }, {"x", vec.x }, {"y", vec.y}, {"z", vec.z} };
	}

	void from_json(const json& j, quat& vec)
	{
		vec.w = j.at("w").get<double>();
		vec.x = j.at("x").get<double>();
		vec.y = j.at("y").get<double>();
		vec.z = j.at("z").get<double>();
	}
}
