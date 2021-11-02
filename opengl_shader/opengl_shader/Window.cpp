#include "Window.h"

#include <cstdlib>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Helper.h"


void Window::SetProjectionMatrix(const float& nearClip = 0.1f, const float& farClip = 100.0f)
{
	m_ProjectionMatrix = glm::perspective(glm::radians(mainCamera.fov), 
		static_cast<float>(m_Width) / static_cast<float>(m_Height), 
		nearClip, farClip);

	m_MVPMatrix = m_ProjectionMatrix * m_ViewMatrix * m_ModelMatrix;
}

void Window::SetModelMatrix(glm::mat4 modelMatrix = glm::mat4(1.0f))
{
	m_ModelMatrix = modelMatrix;
	m_MVPMatrix = m_ProjectionMatrix * m_ViewMatrix * m_ModelMatrix;
}

void Window::SetViewMatrix(const glm::vec3& cameraPosition, const glm::vec3& cameraTarget, const glm::vec3& up)
{
	m_ViewMatrix = glm::lookAt(cameraPosition, cameraTarget, up);
	m_MVPMatrix = m_ProjectionMatrix * m_ViewMatrix * m_ModelMatrix;
}

Window::Window(const int& width, const int& height)
{	
	if (!glfwInit()) 
	{
		std::exit(EXIT_FAILURE);
	}

	glGetString(GL_VERSION); //Fonction de la bibliothèque OpenGL du système

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_SAMPLES, 16); //Multisample
	//glfwWindowHint(GLFW_VISIBLE, GL_FALSE);

	m_Width = width;
	m_Height = height;
	m_Window = glfwCreateWindow(width, width, "Hello World", NULL, NULL);
	if (!m_Window) 
	{
		Helper::Terminate("Impossible de créer la fenêtre !");
	}
	
	glfwMakeContextCurrent(m_Window);
	glEnable(GL_MULTISAMPLE);
	glewExperimental = GL_TRUE;

	GLenum err;
	if((err = glewInit()) != GLEW_OK) /* Problem: glewInit failed, something is seriously wrong. */
	{
		Helper::Terminate(std::string("Error: ") + reinterpret_cast<const char*>(glewGetErrorString(err)));
	}
	
	Helper::RendererInfo();

	SetProjectionMatrix();
	SetViewMatrix(glm::vec3(0,0,-10), glm::vec3(0,0,1), glm::vec3(0,1,0));
	SetModelMatrix();

	glViewport(0,0, m_Width, m_Height);

	glfwSetWindowUserPointer(m_Window, this);
}

