#pragma once
#include "Entity.h"

class GameEntity : public Entity
{
public:
	GameEntity()
		: Entity()
	{
		AddComponent(std::make_shared<Transform>());
	}
};
