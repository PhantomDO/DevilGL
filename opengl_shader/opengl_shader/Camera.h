#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Transform.h"

class Camera
{

public:
	GLfloat fov = 45.0f;
	GLfloat nearClip = 0.1f;
	GLfloat farClip = 1000.0f;
	glm::vec3 up = glm::vec3(0, 1, 0);
	Transform transform;

	Camera() = default;

	Camera(const GLfloat& fov, const glm::vec3& position, const glm::vec3& up = glm::vec3(0, 1, 0));

public:
	glm::mat4 GetMVPMatrix() const { return m_MVPMatrix; }

	glm::mat4 GetProjectionMatrix() const { return m_ProjectionMatrix; }
	void SetProjectionMatrix(const int& width, const int& height);

	glm::mat4 GetModelMatrix() const { return m_ModelMatrix; }
	void SetModelMatrix(glm::mat4 modelMatrix = glm::mat4(1.0f));

	glm::mat4 GetViewMatrix() const { return m_ViewMatrix; }
	void SetViewMatrix();

private:
	glm::mat4 m_MVPMatrix;
	glm::mat4 m_ProjectionMatrix;
	glm::mat4 m_ModelMatrix;
	glm::mat4 m_ViewMatrix;
};
