#include "Component.h"
#include "MeshRenderer.h"

const std::size_t Engine::Component::Type = std::hash<std::string>()(TO_STRING(Component));


void to_json(nlohmann::json&, const Engine::Component&)
{
	Engine::Debug::Log("called to_json for component");
}

void from_json(nlohmann::json const&, Engine::Component&)
{
	Engine::Debug::Log("called from_json for component");
}
