#include "Window.h"

#include <cstdlib>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Helper.h"
#include "Tools.h"
#include "Debug.h"

Window::Window(const int& width, const int& height, bool debugGL)
{	
	if (!glfwInit()) 
	{
		std::exit(EXIT_FAILURE);
	}

	glGetString(GL_VERSION); //Fonction de la bibliothèque OpenGL du système

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 16); //Multisample
	glfwWindowHint(GLFW_VISIBLE, GL_TRUE);

	if (debugGL)
	{
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	}

	m_Width = width;
	m_Height = height;
	m_Window = glfwCreateWindow(width, width, "Hello World", NULL, NULL);
	if (!m_Window) 
	{
		Helper::Terminate("Impossible de créer la fenêtre !");
	}

	glfwMakeContextCurrent(m_Window);
	glewExperimental = GL_TRUE;
	
	GLenum err;
	if((err = glewInit()) != GLEW_OK) /* Problem: glewInit failed, something is seriously wrong. */
	{
		Helper::Terminate(std::string("Error: ") + reinterpret_cast<const char*>(glewGetErrorString(err)));
	}
	
	Helper::RendererInfo();

	glEnable(GL_MULTISAMPLE);
	if (debugGL)
	{
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(Tools::GLMessageCallback, 0);
		Debug::Log("Enabled OpenGL debugging");
	}

	camera = Camera();

	if (std::shared_ptr<Transform> tr; camera.TryGetComponent(tr))
	{
		tr->position = glm::vec3(0, 0, 10);
		camera.SetProjectionMatrix(width, height);
		camera.SetViewMatrix();
	}

	glViewport(0,0, m_Width, m_Height);

	glfwSetWindowUserPointer(m_Window, this);
	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	mousePosition = glm::vec2(width / 2, height / 2);

}

