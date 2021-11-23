#pragma once
#include <vector>

#include "Component.h"
#include "Debug.h"
#include "MeshRenderer.h"
#include "Transform.h"

static int Entity_Count = -1;

class Entity
{
protected:
	int m_InstanceID;
	std::vector<std::shared_ptr<Component>> m_Components;

public:
	int GetInstanceID() const { return m_InstanceID; }

	template <class Arg>
	std::shared_ptr<Arg> AddComponent(const std::shared_ptr<Arg>& component);

	template<typename Arg>
	std::shared_ptr<Arg> GetComponent();

	template<typename Arg>
	bool TryGetComponent(std::shared_ptr<Arg>& component);

public:

	Entity()
		: m_InstanceID(Entity_Count++)
	{
	}
};

template <typename Arg>
std::shared_ptr<Arg> Entity::AddComponent(const std::shared_ptr<Arg>& component)
{
	if (std::shared_ptr<Component> baseComponent = std::dynamic_pointer_cast<Component>(std::make_shared<Arg>(component)))
	{
		m_Components.emplace_back(std::move(component));
		return GetComponent<MeshRenderer>();
	}

	Debug::LogError("Can't had this component to entity.");
	return {};
}

template <typename Arg>
std::shared_ptr<Arg> Entity::GetComponent()
{
	for (auto component : m_Components)
	{
		if (auto typedComponent = std::dynamic_pointer_cast<Arg>(component))
		{
			return typedComponent;
		}
	}

	return nullptr;
}

template <typename Arg>
bool Entity::TryGetComponent(std::shared_ptr<Arg>& component)
{
	component = GetComponent<Arg>();
	return component != nullptr;
}
