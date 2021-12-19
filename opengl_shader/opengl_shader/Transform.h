#pragma once
#include <iostream>
#include <ostream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "json_glm.hpp"
#include "Component.h"

namespace Engine
{
	class Transform : public Component
	{
		CLASS_DECLARATION(Transform)

	public:
		
		NLOHMANN_DEFINE_TYPE_INTRUSIVE(Transform, m_Origin, position, rotation, scale)

	private:

		glm::vec4 m_Origin;

	public:
		glm::vec3 position;
		glm::quat rotation;
		glm::vec3 scale;

		glm::vec3 GetUp() const { return glm::normalize(glm::cross(GetRight(), GetForward())); }
		glm::vec3 GetRight() const { return glm::normalize(glm::cross(GetForward(), GetWorldUp())); }
		glm::vec3 GetForward() const { return rotation * GetWorldForward(); }

		glm::vec4 GetTransformedVector() const { return GetModelMatrix() * m_Origin; }
		glm::mat4 GetModelMatrix() const
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

		static glm::vec3 GetWorldUp() { return {0, 1, 0}; }
		static glm::vec3 GetWorldRight() { return {1, 0, 0}; }
		static glm::vec3 GetWorldForward() { return {0, 0, -1}; }

		Transform()
			:	Component(),
				m_Origin(glm::vec4(0,0,0,1)),
				position(glm::vec3(0)),
				rotation(glm::normalize(glm::quat(1, 0, 0, 0))),
				scale(glm::vec3(1))
		{
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

		//Transform& operator =(const Transform& tr)
		//{
		//	if (this != &tr)
		//	{
		//		this->m_Origin = tr.m_Origin;
		//		this->position = tr.position;
		//		this->rotation = tr.rotation;
		//		this->scale = tr.scale;
		//	}

		//	return *this;
		//}

	};
}
