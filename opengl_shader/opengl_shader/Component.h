#pragma once
#include <memory>

class Entity;

class Component
{
public:
	std::shared_ptr<Entity> entity;
	
	Component() : entity(nullptr) {}
	virtual ~Component() = default;
};

