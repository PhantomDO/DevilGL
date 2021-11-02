#include "Camera.h"

Camera::Camera(const GLfloat& fov, const glm::vec3& position, const glm::vec3& up)
{
	this->fov = fov;
	transform = Transform(position);
}

void Camera::SetProjectionMatrix(const int& width, const int& height)
{
	m_ProjectionMatrix = glm::perspective(glm::radians(fov),
	                                      static_cast<float>(width) / static_cast<float>(height),
	                                      nearClip, farClip);
	m_MVPMatrix = m_ProjectionMatrix * m_ViewMatrix * m_ModelMatrix;
}

void Camera::SetModelMatrix(glm::mat4 modelMatrix)
{
	m_ModelMatrix = modelMatrix;
	m_MVPMatrix = m_ProjectionMatrix * m_ViewMatrix * m_ModelMatrix;
}

void Camera::SetViewMatrix()
{
	m_ViewMatrix = glm::lookAt(transform.position, transform.rotation, up);
	m_MVPMatrix = m_ProjectionMatrix * m_ViewMatrix * m_ModelMatrix;
}
