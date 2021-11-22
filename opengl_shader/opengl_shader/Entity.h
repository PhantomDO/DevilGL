#pragma once
#include <vector>

#include "Component.h"
#include "Debug.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include <optional>

static int Entity_Count = -1;

class Entity
{
private:

	int m_InstanceID;
	std::vector<Component> m_Components;

public:
	std::shared_ptr<Transform> transform;
	int GetInstanceID() const { return m_InstanceID; }

	template<typename Arg>
	std::optional<Arg> AddComponent(Arg&& component);

	template<typename Arg>
	std::optional<Arg> GetComponent();

	template<typename Arg>
	bool TryGetComponent(Arg& component);

public:

	Entity()
		: m_InstanceID(Entity_Count++), transform(std::make_shared<Transform>())
	{
	}
};

template <typename Arg>
std::optional<Arg> Entity::AddComponent(Arg&& component)
{
	if (Component* baseComponent = dynamic_cast<Component*>(&component))
	{
		m_Components.emplace_back(std::move(component));
		//Arg* typedComponent = dynamic_cast<Arg*>(&m_Components[m_Components.size() - 1]);
		return GetComponent<MeshRenderer>();
	}

	Debug::LogError("Can't had this component to entity.");
	return {};
}

template <typename Arg>
std::optional<Arg> Entity::GetComponent()
{
	for (auto& component : m_Components)
	{
		if (Arg* typedComponent = dynamic_cast<Arg*>(&component))
		{
			return *typedComponent;
		}
	}

	return {};
}

template <typename Arg>
bool Entity::TryGetComponent(Arg& component)
{
	if (((component = GetComponent<Arg>())) && component != nullptr)
	{
		return true;
	}

	return false;
}
