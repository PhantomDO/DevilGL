#pragma once
#include "Entity.h"

namespace Engine
{
	
	class GameEntity : public Entity
	{
	private:

		Transform& m_Transform;

	public:

		Transform& GetTransform() const { return m_Transform; }

	public:
		GameEntity(const std::string& name = "Game Entity") : Entity(name)
		{
			AddComponent<Transform>();
			m_Transform = GetComponent<Transform>();
		}
	};
}
