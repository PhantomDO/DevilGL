#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Helper.h"
#include "Window.h"

class Input
{
public:
	static void CursorPosCallback(GLFWwindow* pWindow, double x, double y)
	{
		int windowSizeX, windowSizeY;
		glm::vec3& color = *(static_cast<glm::vec3*>(glfwGetWindowUserPointer(pWindow)));
		
		// recupere taille de la fenetre
		glfwGetWindowSize(pWindow, &windowSizeX, &windowSizeY);		
		color = Helper::HSVtoRGB(glm::vec3(color.r, static_cast<float>(x/windowSizeX), static_cast<float>(y/windowSizeY)));
	}

	static void GetKeyDown(GLFWwindow* pWindow, int key, int scanCode, int action, int mods)
	{
		if(action == GLFW_RELEASE) return;

		auto color = *(reinterpret_cast<glm::vec3*>(glfwGetWindowUserPointer(pWindow)));
		float hValue = color.r;

		// Trouver l'utilité
		switch (key)
		{
		case GLFW_KEY_DOWN:
			hValue -= 1.0f;
			if (hValue < 0.0f) hValue = 359.0f;
			color = Helper::HSVtoRGB(glm::vec3(hValue, color.g, color.b));
			break;
		case GLFW_KEY_UP:
			hValue += 1.0f;
			if (hValue > 360.0f) hValue = 0.0f;
			color = Helper::HSVtoRGB(glm::vec3(hValue, color.g, color.b));
			break;
		case GLFW_KEY_W:
			GLint modes[2];
			glGetIntegerv(GL_POLYGON_MODE, modes);
			modes[0] = modes[0] == GL_LINE ? GL_FILL : GL_LINE;
			glPolygonMode(GL_FRONT_AND_BACK, modes[0]);
			break;
		default:
			break;
		}
	}

	static void GetScrolling(GLFWwindow* pWindow, double x, double y)
	{
		Window& window_data = *static_cast<Window*>(glfwGetWindowUserPointer(pWindow));

		int width, height;
		glfwGetWindowSize(pWindow, &width, &height);
		window_data.SetFovY(window_data.GetFovY() + static_cast<float>(y));
		if(window_data.GetFovY() < 1.0f) window_data.SetFovY(1.0f);
		if(window_data.GetFovY() > 180.0f) window_data.SetFovY(180.0f);

		glm::mat4 projection = glm::perspective(glm::radians(window_data.GetFovY()), 
			static_cast<float>(width) / static_cast<float>(height), 1.0f, 1000.0f);

		const GLint n_uniform_mesh_projection_matrix = glGetUniformLocation(window_data.GetMeshProgram().GetID(), "proj");
		window_data.GetMeshProgram().Use();
		glUniformMatrix4fv(n_uniform_mesh_projection_matrix, 1, GL_FALSE, glm::value_ptr(projection));

		const GLint n_uniform_light_projection_matrix = glGetUniformLocation(window_data.GetLightProgram().GetID(), "proj");
		window_data.GetLightProgram().Use();
		glUniformMatrix4fv(n_uniform_light_projection_matrix, 1, GL_FALSE, glm::value_ptr(projection));
	}

	static void GetSize(GLFWwindow* pWindow, int width, int height)
	{
		if(width * height == 0) return;

		const Window& window_data = *static_cast<Window*>(glfwGetWindowUserPointer(pWindow));

		glViewport(0, 0, width, height);

		glm::mat4 projection = glm::perspective(glm::radians(window_data.GetFovY()), static_cast<float>(width) / static_cast<float>(height), 1.0f, 1000.0f);

		const GLint n_uniform_mesh_projection_matrix = glGetUniformLocation(window_data.GetMeshProgram().GetID(), "proj");
		window_data.GetMeshProgram().Use();
		glUniformMatrix4fv(n_uniform_mesh_projection_matrix, 1, GL_FALSE, glm::value_ptr(projection));

		const GLint n_uniform_light_projection_matrix = glGetUniformLocation(window_data.GetLightProgram().GetID(), "proj");
		window_data.GetLightProgram().Use();
		glUniformMatrix4fv(n_uniform_light_projection_matrix, 1, GL_FALSE, glm::value_ptr(projection));
	}
};
