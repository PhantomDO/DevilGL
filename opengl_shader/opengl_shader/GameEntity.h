#pragma once
#include "Entity.h"
#include "Transform.h"

class GameEntity : public Entity
{
public:
	std::shared_ptr<Transform> transform;

	GameEntity()
		: transform(std::make_shared<Transform>())
	{
	}
};
