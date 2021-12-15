#include "Transform.h"

CLASS_DEFINITION(Engine::Component, Engine::Transform)

void to_json(nlohmann::json&, const Engine::Transform&)
{
	Engine::Debug::Log("called to_json for Transform");
}

void from_json(nlohmann::json const&, Engine::Transform&)
{
	Engine::Debug::Log("called from_json for Transform");
}