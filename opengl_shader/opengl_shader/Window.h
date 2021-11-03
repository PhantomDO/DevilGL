#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Camera.h"
#include "ShaderProgram.h"

class Window
{
public:

	ShaderProgram GetMeshProgram() const { return m_MeshProgram; }
	void SetMeshProgram(const ShaderProgram& meshProgram) { m_MeshProgram = meshProgram; }
	
	ShaderProgram GetLightProgram() const { return m_LightProgram; }
	void SetLightProgram(const ShaderProgram& lightProgram) { m_LightProgram = lightProgram; }

	GLFWwindow* GetWindowPtr() const { return m_Window; }
	
public:
	
	Window(const int& width, const int& height);
	Camera camera;
	
private:

	int m_Width, m_Height;

	ShaderProgram m_MeshProgram;
	ShaderProgram m_LightProgram;
	GLFWwindow* m_Window;
};
