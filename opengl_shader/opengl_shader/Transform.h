#pragma once
#include <iostream>
#include <ostream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Component.h"
#include "Entity.h"

class Transform : public Component
{
private:

	glm::vec4 m_Origin;

public:
	glm::vec3 position;
	glm::quat rotation;
	glm::vec3 scale;

	glm::vec3 GetUp() const { return glm::normalize(glm::cross(GetRight(), GetForward())); }
	glm::vec3 GetRight() const { return glm::normalize(glm::cross(GetForward(), GetWorldUp())); }
	glm::vec3 GetForward() const { return rotation * GetWorldForward(); }
	
	glm::vec4 GetTransformedVector() { return GetModelMatrix() * m_Origin; }
	glm::mat4 GetModelMatrix()
	{
		return	glm::translate(glm::mat4(1.0f), position) * 
				glm::mat4_cast(rotation) * 
				glm::scale(glm::mat4(1.0f), scale);
	}
	
	void SetPositionAndRotation(const glm::vec3& pos, const glm::vec3& rot)
	{
		position = pos;
		rotation = glm::normalize(glm::quat(1, rot.x, rot.y, rot.z));
	}


public:

	static glm::vec3 GetWorldUp() { return glm::vec3(0, 1, 0); }
	static glm::vec3 GetWorldRight() { return glm::vec3(1, 0, 0); }
	static glm::vec3 GetWorldForward() { return glm::vec3(0, 0, -1); }

	Transform()
		: m_Origin(glm::vec4(glm::vec3(0), 1.0f)),
		scale (glm::vec3(1))
	{
		SetPositionAndRotation(glm::vec3(0), glm::vec3(0));
	}
	
	Transform(const Transform& tr)
		:	m_Origin(tr.m_Origin), position(tr.position), rotation(tr.rotation), scale(tr.scale)
	{		
	}

	explicit Transform(std::shared_ptr<Transform> tr)
		:	m_Origin(std::move(tr->m_Origin)), position(std::move(tr->position)), rotation(std::move(tr->rotation)), scale(std::move(tr->scale))
	{		
	}

	Transform(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scl)
		: m_Origin(glm::vec4(pos, 1.0f))
	{
		SetPositionAndRotation(pos, rot);
		scale = scl;
	}

	friend std::ostream& operator <<(std::ostream& os, const Transform& tr)
	{
		os << "Transform { position: ("
			<< tr.position.x << ", " << tr.position.y << ", " << tr.position.z << "), "
			<< "rotation: ("
			<< tr.rotation.w << ", " << tr.rotation.x << ", " << tr.rotation.y << ", " << tr.rotation.z << "), "
			<< "scale: ("
			<< tr.scale.x << ", " << tr.scale.y << ", " << tr.scale.z << ") }";

		return os;
	}

	Transform& operator =(const Transform& tr)
	{
		if (this != &tr)
		{
			this->position = tr.position;
			this->rotation = tr.rotation;
			this->scale = tr.scale;
			this->m_Origin = tr.m_Origin;
		}

		return *this;
	}

};
