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
		std::vector<std::unique_ptr<Component>> m_Components;

	public:
		//NLOHMANN_DEFINE_TYPE_INTRUSIVE(Entity, m_InstanceID, m_RootInScene, name, tag, parent, m_Components)

	public:
		static int ENTITY_COUNT;

	public:
		std::string name;
		std::string tag;
		int parent;

	public:
		int GetInstanceID() const { return m_InstanceID; }
		bool CompareTag(const std::string& tag) const { return this->tag == tag; }

		template <class ComponentType, typename... Args>
		void AddComponent(Args&&... params);

		template<class ComponentType>
		ComponentType& GetComponent();

		template<class ComponentType>
		bool RemoveComponent();

		template<class ComponentType>
		bool TryGetComponent(std::optional<ComponentType>& component);

	public:

		Entity(const std::string& name = "Entity")
			: m_InstanceID(++ENTITY_COUNT), m_RootInScene(true), name(name), tag("Unknown"), parent(-1)
		{
		}
	};

	template <class ComponentType, typename ... Args>
	void Entity::AddComponent(Args&&... params)
	{
		m_Components.emplace_back(std::make_unique<ComponentType>(std::forward<Args>(params)...));
	}

	template <class ComponentType>
	ComponentType& Entity::GetComponent()
	{
		for (auto&& component : m_Components)
		{
			if (component->IsClassType(ComponentType::Type))
			{
				return *static_cast<ComponentType*>(component.get());
			}
		}

		return *std::unique_ptr<ComponentType>(nullptr);
	}

	template <class ComponentType>
	bool Entity::RemoveComponent()
	{
		if (m_Components.empty()) return false;

		auto& index = std::find_if(
			m_Components.begin(), m_Components.end(),
			[classType = ComponentType::Type](auto& component) {
				return component->IsClassType(classType);
		});

		const bool success = index != m_Components.end();
		if (success) m_Components.erase(index);
		return success;
	}

	template <class  ComponentType>
	bool Entity::TryGetComponent(std::optional<ComponentType>& component)
	{
		component = GetComponent<ComponentType>();
		return component.has_value();
	}
}
