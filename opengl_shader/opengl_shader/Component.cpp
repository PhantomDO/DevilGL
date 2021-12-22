#include "Component.h"
#include "MeshRenderer.h"

const std::size_t Engine::Component::Type = std::hash<std::string>()(TO_STRING(Component));

