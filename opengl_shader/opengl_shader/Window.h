#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	float GetFovY() const { return m_FovY; }
	void SetFovY(const float& yFov) { m_FovY = yFov; }

	GLuint GetMeshProgramID() const { return m_MeshProgramID; }
	void SetMeshProgramID(const GLuint& meshProgramID) { m_MeshProgramID = meshProgramID; }
	
	GLuint GetLightProgramID() const { return m_LightProgramID; }
	void SetLightProgramID(const GLuint& lightProgramID) { m_LightProgramID = lightProgramID; }

	GLFWwindow* GetWindowPtr() const { return m_Window; }
	
public:
	
	Window(const int& width, const int& height);

private:

	float m_FovY = 45.f;
	GLuint m_MeshProgramID;
	GLuint m_LightProgramID;
	GLFWwindow* m_Window;
};
