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
	glm::vec3 m_Position;
	glm::quat m_Rotation;
	glm::vec3 m_Scale;

	glm::mat4 m_TranslationMat;
	glm::mat4 m_RotationMat;
	glm::mat4 m_ScaleMat;

	glm::vec4 m_Origin;

public:

	glm::vec3 GetUp() const { return m_Rotation * GetWorldUp(); }
	glm::vec3 GetRight() const { return m_Rotation * GetWorldRight(); }
	glm::vec3 GetForward() const { return m_Rotation * GetWorldForward(); }

	glm::vec3 GetPosition() const { return m_Position; }
	glm::quat GetRotation() const { return m_Rotation; }
	glm::vec3 GetScale() const { return m_Scale; }

	glm::mat4 GetModelMatrix() { return m_TranslationMat * m_RotationMat * m_ScaleMat; }
	glm::vec4 GetTransformedVector() { return GetModelMatrix() * m_Origin; }

	void SetPosition(const glm::vec3& position)
	{
		m_Position = position;
		m_TranslationMat = glm::translate(glm::mat4(1.0f), m_Position);
	}

	void SetRotation(const glm::quat& rotation)
	{
		m_Rotation = rotation;
		m_RotationMat = glm::mat4_cast(m_Rotation);
	}

	void SetScale(const glm::vec3& scale)
	{
		m_Scale = scale;
		m_ScaleMat = glm::scale(glm::mat4(1.0f), m_Scale);
	}

	void SetForward(const glm::vec3& value) { m_Rotation = glm::quatLookAt(glm::normalize(value), glm::vec3(0, 1, 0)); }

	void SetPositionAndRotation(const glm::vec3& pos, const glm::vec3& rot)
	{
		SetPosition(pos);
		SetRotation(glm::quat(1, rot.x, rot.y, rot.z));
	}


public:

	static glm::vec3 GetWorldUp() { return glm::vec3(0, 1, 0); }
	static glm::vec3 GetWorldRight() { return glm::vec3(1, 0, 0); }
	static glm::vec3 GetWorldForward() { return glm::vec3(0, 0, -1); }

	Transform()
		: m_Origin(glm::vec4(glm::vec3(0), 1.0f))
	{
		SetPositionAndRotation(glm::vec3(0), glm::vec3(0));
		SetScale(glm::vec3(1));
	}
	
	Transform(const Transform& tr)
		:	m_Position(tr.m_Position), m_Rotation(tr.m_Rotation), m_Scale(tr.m_Scale),
			m_TranslationMat(tr.m_TranslationMat), m_RotationMat(tr.m_RotationMat), m_ScaleMat(tr.m_ScaleMat),
			m_Origin(tr.m_Origin)
	{		
	}

	explicit Transform(std::shared_ptr<Transform> tr)
		:	m_Position(std::move(tr->m_Position)), m_Rotation(std::move(tr->m_Rotation)), m_Scale(std::move(tr->m_Scale)),
			m_TranslationMat(std::move(tr->m_TranslationMat)), m_RotationMat(std::move(tr->m_RotationMat)), m_ScaleMat(std::move(tr->m_ScaleMat)),
			m_Origin(std::move(tr->m_Origin))
	{		
	}

	Transform(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scl)
		: m_Origin(glm::vec4(pos, 1.0f))
	{
		SetPositionAndRotation(pos, rot);
		SetScale(scl);
	}

	friend std::ostream& operator <<(std::ostream& os, const Transform& tr)
	{
		os << "Transform { m_Position: ("
			<< tr.m_Position.x << ", " << tr.m_Position.y << ", " << tr.m_Position.z << "), "
			<< "m_Rotation: ("
			<< tr.m_Rotation.w << ", " << tr.m_Rotation.x << ", " << tr.m_Rotation.y << ", " << tr.m_Rotation.z << "), "
			<< "m_Scale: ("
			<< tr.m_Scale.x << ", " << tr.m_Scale.y << ", " << tr.m_Scale.z << ") }";

		return os;
	}

	Transform& operator =(const Transform& tr)
	{
		if (this != &tr)
		{
			this->m_Position = tr.m_Position;
			this->m_Rotation = tr.m_Rotation;
			this->m_Scale = tr.m_Scale;
			this->m_TranslationMat = tr.m_TranslationMat;
			this->m_RotationMat = tr.m_RotationMat;
			this->m_ScaleMat = tr.m_ScaleMat;
			this->m_Origin = tr.m_Origin;
		}

		return *this;
	}

};
