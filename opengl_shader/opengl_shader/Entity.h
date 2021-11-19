#pragma once
#include <vector>

#include "Component.h"
#include "Debug.h"
#include "MeshRenderer.h"
#include "Transform.h"

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
	Arg& AddComponent(Arg&& component);

	template<typename  Arg>
	Arg& GetComponent();

	template<typename  Arg>
	bool TryGetComponent(Arg& component);

public:

	Entity()
		: m_InstanceID(Entity_Count++), transform(std::make_shared<Transform>())
	{
	}
};
