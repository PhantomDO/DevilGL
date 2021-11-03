#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Transform.h"

class Camera
{

public:
	GLfloat fov;
	GLfloat nearClip;
	GLfloat farClip;
	glm::vec3 up;
	Transform transform;

	Camera();

public:
	glm::mat4 GetProjectionMatrix() const { return m_ProjectionMatrix; }
	void SetProjectionMatrix(const int& width, const int& height);

	glm::mat4 GetViewMatrix() const { return m_ViewMatrix; }
	void SetViewMatrix();

private:
	glm::mat4 m_ProjectionMatrix;
	glm::mat4 m_ViewMatrix;
};
