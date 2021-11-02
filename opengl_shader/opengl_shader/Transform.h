#pragma once
#include <glm/vec3.hpp>

class Transform
{
public:
	glm::vec3 position = glm::vec3(0);
	glm::vec3 rotation = glm::vec3(0);
	glm::vec3 scale = glm::vec3(1);

	void SetPositionAndRotation(const glm::vec3& pos, const glm::vec3& rot)
	{
		position = pos;
		rotation = rot;
	}

	Transform(const glm::vec3& pos = glm::vec3(0), const glm::vec3& rot = glm::vec3(0), const glm::vec3& scale = glm::vec3(1))
	{
		this->position = pos;
		this->rotation = rot;
		this->scale = scale;
	}
};
