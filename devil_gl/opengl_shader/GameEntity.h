#pragma once
#include "Entity.h"

namespace Engine
{
	class GameEntity : public Entity
	{
	public:

		Transform& GetTransform() { return GetComponent<Transform>(); }

	public:
		GameEntity(const std::string& name = "Game Entity")
			:	Entity(name)
		{
			AddComponent<Transform>();
		}
	};
}
