#include "Camera.h"

#include <GLFW/glfw3.h>

#include "Bounds.h"

#include <cereal/types/polymorphic.hpp>
#include <cereal/archives/json.hpp>

CEREAL_REGISTER_TYPE(Engine::Camera)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Engine::GameEntity, Engine::Camera)

Engine::Camera::Camera(const std::string& name)
	:	GameEntity(name), fov(45.0f), nearClip(0.1f), farClip(1000.0f),
		m_ProjectionMatrix(), m_ViewMatrix(),
		yaw(-90.f), pitch(0.f), speed(2.5f), sensitivity(0.1f)
{
}

void Engine::Camera::ProcessKeyboardEvent(const int& key, const float& dt)
{
	auto& tr = GetTransform();
	const GLfloat velocity = dt * speed;
	switch (key)
	{
	case GLFW_KEY_S:
		tr.position -= tr.GetForward() * velocity;
		SetViewMatrix();
		break;
	case GLFW_KEY_W:
		tr.position += tr.GetForward() * velocity;
		SetViewMatrix();
		break;
	case GLFW_KEY_A:
		tr.position -= tr.GetRight() * velocity;
		SetViewMatrix();
		break;
	case GLFW_KEY_D:
		tr.position += tr.GetRight() * velocity;
		SetViewMatrix();
		break;
	default: ;
	}
}

void Engine::Camera::ProcessMouseMouvement(glm::vec2& offset, GLboolean constrain)
{
	offset *= sensitivity;

	yaw += offset.x;
	pitch += offset.y;

	if (pitch > 89.0f) pitch = 89.0f;
	if (pitch < -89.0f) pitch = -89.0f;

	UpdateView();
}

void Engine::Camera::ProcessMouseScroll(const float& yFov)
{
	fov -= yFov;
	if(fov < 1.0f) fov = 1.0f;
	if(fov > 45.0f) fov = 45.0f;
}

void Engine::Camera::UpdateView()
{
	const glm::quat qPitch = glm::angleAxis(glm::radians(pitch), glm::vec3(1, 0, 0));
	const glm::quat qYaw = glm::angleAxis(glm::radians(yaw), glm::vec3(0, 1, 0));
	//const glm::quat qRoll = glm::angleAxis(glm::radians(roll), glm::vec3(0, 0, 1));

	const glm::quat orientation = qPitch * qYaw;
	auto tr = GetComponent<Transform>();
	tr.rotation = glm::normalize(orientation);
	SetViewMatrix();
}

void Engine::Camera::SetProjectionMatrix(const int& width, const int& height)
{
	m_ProjectionMatrix = glm::perspective(glm::radians(fov),
	                                      static_cast<float>(width) / static_cast<float>(height),
	                                      nearClip, farClip);
}

void Engine::Camera::SetViewMatrix()
{
	const auto tr = GetComponent<Transform>();
	m_ViewMatrix = glm::lookAt(tr.position, tr.position + tr.GetForward(), tr.GetWorldUp());
}
