#pragma once
#include <vector>

#include "Debug.h"
#include "MeshRenderer.h"
#include "Transform.h"

class Entity
{

protected:
	int m_InstanceID;
	bool m_RootInScene;
	std::vector<std::shared_ptr<Component>> m_Components;

public:
	static int ENTITY_COUNT;

public:
	std::string name;
	std::string tag;

public:
	int GetInstanceID() const { return m_InstanceID; }
	bool CompareTag(const std::string& tag) const { return this->tag == tag; }

	template <class Arg>
	std::shared_ptr<Arg> AddComponent(const std::shared_ptr<Arg>& component);

	template<typename Arg>
	std::shared_ptr<Arg> GetComponent();

	template<typename Arg>
	bool TryGetComponent(std::shared_ptr<Arg>& component);

public:

	Entity(std::string&& name = "")
		: m_InstanceID(++ENTITY_COUNT), m_RootInScene(false), name(std::move(name))
	{
	}
};

template <typename Arg>
std::shared_ptr<Arg> Entity::AddComponent(const std::shared_ptr<Arg>& component)
{
	if (std::shared_ptr<Component> baseComponent = std::dynamic_pointer_cast<Component>(std::make_shared<Arg>(component)))
	{
		m_Components.emplace_back(std::move(component));
		return GetComponent<Arg>();
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
