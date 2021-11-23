﻿#include "Window.h"

#include <cstdlib>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Helper.h"

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
	glfwWindowHint(GLFW_SAMPLES, 16); //Multisample
	glfwWindowHint(GLFW_VISIBLE, GL_TRUE);

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

	camera = Camera();
	std::cout << "FOV " << camera.fov << std::endl;
	camera.transform.position = glm::vec3(0, 0, 10);
	camera.SetProjectionMatrix(width, height);
	camera.SetViewMatrix();

	std::cout << camera.transform << std::endl;

	glViewport(0,0, m_Width, m_Height);

	glfwSetWindowUserPointer(m_Window, this);

}

