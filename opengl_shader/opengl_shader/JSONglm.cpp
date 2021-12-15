
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <nlohmann/json.hpp>

namespace glm
{

	void from_json(const nlohmann::json& j, vec2& vec)
	{
		j.at("x").get_to(vec.x);
		j.at("y").get_to(vec.y);
	}

	void from_json(const nlohmann::json& j, vec3& vec)
	{
		j.at("x").get_to(vec.x);
		j.at("y").get_to(vec.y);
		j.at("z").get_to(vec.z);
	}

	void from_json(const nlohmann::json& j, vec4& vec)
	{
		j.at("x").get_to(vec.x);
		j.at("y").get_to(vec.y);
		j.at("z").get_to(vec.z);
		j.at("z").get_to(vec.w);
	}

}
