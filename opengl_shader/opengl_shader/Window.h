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

	glm::mat4 GetViewMatrix() const { return m_ViewMatrix; }
	void SetViewMatrix();
	
public:
	
	Window(const int& width, const int& height);

private:

	float m_FovY = 45.f;

	glm::mat4 m_ViewMatrix;

	ShaderProgram m_MeshProgram;
	ShaderProgram m_LightProgram;
	GLFWwindow* m_Window;
};
