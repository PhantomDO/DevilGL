#include "Entity.h"

template <typename Arg>
Arg& Entity::AddComponent(Arg&& component)
{
	if (Component* baseComponent = dynamic_cast<Component*>(&component))
	{
		m_Components.emplace_back(std::move(component));
		return m_Components[m_Components.size() - 1];
	}

	Debug::LogError("Can't had this component to entity.");
	return nullptr;
}

template <typename Arg>
Arg& Entity::GetComponent()
{
	for (auto& component : m_Components)
	{
		if (Arg* typedComponent = dynamic_cast<Arg*>(&component))
		{
			return typedComponent;
		}
	}

	return nullptr;
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
