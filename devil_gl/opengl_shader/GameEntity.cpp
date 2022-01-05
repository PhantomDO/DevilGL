#include "GameEntity.h"

#include <cereal/types/polymorphic.hpp>
#include <cereal/archives/json.hpp>

CEREAL_REGISTER_TYPE(Engine::GameEntity)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Engine::Entity, Engine::GameEntity)