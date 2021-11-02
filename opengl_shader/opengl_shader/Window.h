#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "ShaderProgram.h"

class Window
{
public:
	float GetFovY() const { return m_FovY; }
	void SetFovY(const float& yFov) { m_FovY = yFov; }

	ShaderProgram GetMeshProgram() const { return m_MeshProgram; }
	void SetMeshProgram(const ShaderProgram& meshProgram) { m_MeshProgram = meshProgram; }
	
	ShaderProgram GetLightProgram() const { return m_LightProgram; }
	void SetLightProgram(const ShaderProgram& lightProgram) { m_LightProgram = lightProgram; }

	GLFWwindow* GetWindowPtr() const { return m_Window; }

	glm::mat4 GetMVPMatrix() const { return m_MVPMatrix; }

	glm::mat4 GetProjectionMatrix() const { return m_ProjectionMatrix; }
	void SetProjectionMatrix(const float& nearClip, const float& farClip);

	glm::mat4 GetModelMatrix() const { return m_ModelMatrix; }
	void SetModelMatrix(glm::mat4 modelMatrix);

	glm::mat4 GetViewMatrix() const { return m_ViewMatrix; }
	void SetViewMatrix(const glm::vec3& cameraPosition, const glm::vec3& cameraTarget, const glm::vec3& up);
	
public:
	
	Window(const int& width, const int& height);

private:

	float m_FovY = 45.f;
	int m_Width, m_Height;

	glm::mat4 m_MVPMatrix;
	glm::mat4 m_ProjectionMatrix;
	glm::mat4 m_ModelMatrix;
	glm::mat4 m_ViewMatrix;

	ShaderProgram m_MeshProgram;
	ShaderProgram m_LightProgram;
	GLFWwindow* m_Window;
};
