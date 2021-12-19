#pragma once
#include <optional>
#include <vector>

#include "Transform.h"
#include <nlohmann/json.hpp>

namespace Engine
{
	class Entity
	{

	protected:
		int m_InstanceID;
		bool m_RootInScene;

	public:
		NLOHMANN_DEFINE_TYPE_INTRUSIVE(Entity, m_InstanceID, m_RootInScene, name, tag, parent, components)

	public:
		static int ENTITY_COUNT;

	public:
		std::vector<std::shared_ptr<Component>> components;
		std::string name;
		std::string tag;
		int parent;

	public:
		int GetInstanceID() const { return m_InstanceID; }
		bool CompareTag(const std::string& tag) const { return this->tag == tag; }
		
		template <class ComponentType, class ... Args>
		ComponentType& AddComponent(Args&& ... params);

		template<class ComponentType>
		ComponentType& GetComponent();

		template<class ComponentType>
		bool TryGetComponent(ComponentType& component);

		template<class ComponentType>
		bool RemoveComponent();

		template<class ComponentType>
		std::vector<ComponentType*> GetComponents();
		
		template<class ComponentType>
		int RemoveComponents();

	public:

		Entity(const std::string& name = "Entity")
			: m_InstanceID(++ENTITY_COUNT), m_RootInScene(true), name(name), tag("Unknown"), parent(-1)
		{
		}
	};

	template <class ComponentType, typename ... Args>
	ComponentType& Entity::AddComponent(Args&&... params)
	{
		components.emplace_back(std::make_shared<ComponentType>(std::forward<Args>(params)...));
		return *static_cast<ComponentType*>(components.back().get());
	}

	template <class ComponentType>
	ComponentType& Entity::GetComponent()
	{
		for (auto&& component : components)
		{
			if (component->IsClassType(ComponentType::Type))
			{
				return *static_cast<ComponentType*>(component.get());
			}
		}

		return *std::shared_ptr<ComponentType>(nullptr);
	}

	template <class ComponentType>
	bool Entity::RemoveComponent()
	{
		if (components.empty()) return false;

		auto& index = std::find_if(
			components.begin(), components.end(),
			[classType = ComponentType::Type](auto& component) {
				return component->IsClassType(classType);
		});

		const bool success = index != components.end();
		if (success) components.erase(index);
		return success;
	}

	template <class  ComponentType>
	bool Entity::TryGetComponent(ComponentType& component)
	{
		for (auto&& comp : components)
		{
			if (comp->IsClassType(ComponentType::Type))
			{
				component = *static_cast<ComponentType*>(comp.get());
				return true;
			}
		}

		component = *std::shared_ptr<ComponentType>(nullptr);
		return false;
	}
	
	template <class ComponentType>
	std::vector<ComponentType*> Entity::GetComponents()
	{
		std::vector<ComponentType*> componentsOfType;

		for (auto&& component : components)
		{
			if (component->IsClassType(ComponentType::Type))
			{
				componentsOfType.emplace_back(static_cast<ComponentType*>(component.get()));
			}
		}

		return componentsOfType;
	}

	template <class ComponentType>
	int Entity::RemoveComponents()
	{
		if (components.empty()) return 0;

		int numRemoved = 0;
		bool success = false;

		do
		{
			auto& index = std::find_if(
				components.begin(), components.end(),
				[classType = ComponentType::Type](auto& component) {
				return component->IsClassType(classType);
			});

			success = index != components.end();
			if (success) 
			{
				components.erase(index);
				++numRemoved;
			}
		} while (success);

		return numRemoved;
	}
}
