#pragma once
#include <GL/glew.h>
#include <glm/vec3.hpp>

#include "Transform.h"

class Camera
{
public:
	GLfloat fov = 45.0f;
	glm::vec3 up = glm::vec3(0, 1, 0);
	Transform transform;

	Camera() = default;

	Camera(const GLfloat& fov, const glm::vec3& position, const glm::vec3& up = glm::vec3(0,1,0))
	{
		this->fov = fov;
		transform = Transform(position);
	}
};
