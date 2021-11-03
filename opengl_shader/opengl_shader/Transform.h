#pragma once
#include <iostream>
#include <ostream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Transform
{
public:

	static glm::vec3 GetWorldUp() { return glm::vec3(0, 1, 0); }
	static glm::vec3 GetWorldRight() { return glm::vec3(1, 0, 0); }
	static glm::vec3 GetWorldForward() { return glm::vec3(0, 0, -1); }

public:
	glm::vec3 position;
	glm::quat rotation;
	glm::vec3 scale;
	glm::mat4 matrix;

	glm::vec3 GetUp() const { return rotation * GetWorldUp(); }
	glm::vec3 GetRight() const { return rotation * GetWorldRight(); }
	glm::vec3 GetForward() const { return rotation * GetWorldForward(); }

	void SetForward(const glm::vec3& value) { rotation = glm::quatLookAt(glm::normalize(value), glm::vec3(0,1,0)); }

	void SetPositionAndRotation(const glm::vec3& pos, const glm::vec3& rot)
	{
		position = pos;
		//SetForward(rot);
	}

	Transform(const glm::vec3& pos = glm::vec3(0), const glm::vec3& rot = glm::vec3(0), const glm::vec3& scl = glm::vec3(1))
		: position(pos), rotation(glm::quat(1, rot.x, rot.y, rot.z)), scale(scl), matrix(glm::mat4(1.0f))
	{
		//SetForward(rot);
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
};
