#include "Camera.h"

Camera::Camera()
	:	fov(45.0f), nearClip(0.1f), farClip(1000.0f),
		up(glm::vec3(0,1,0)), transform(Transform()),
		m_ProjectionMatrix(), m_ViewMatrix()
{
}

void Camera::SetProjectionMatrix(const int& width, const int& height)
{
	m_ProjectionMatrix = glm::perspective(glm::radians(fov),
	                                      static_cast<float>(width) / static_cast<float>(height),
	                                      nearClip, farClip);
}

void Camera::SetViewMatrix()
{
	m_ViewMatrix = glm::lookAt(transform.GetPosition(), transform.GetPosition() + transform.GetForward(), up);
}
