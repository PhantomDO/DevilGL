#pragma once
#include "Entity.h"
#include <cereal/types/base_class.hpp>

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

		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(cereal::base_class<Entity>(this));
		}
	};
}
