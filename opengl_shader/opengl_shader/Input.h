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
		
		auto window = *(static_cast<Window*>(glfwGetWindowUserPointer(pWindow)));
		glm::vec3 camPos = window.mainCamera.transform.position;

		// Trouver l'utilité
		switch (key)
		{
		/*case GLFW_KEY_DOWN:
			window.mainCamera.transform.position -= glm::vec3(0, 1.0f, 0);
			core.GetMatrixs().ViewMatrix = glm::lookAt(cam.GetTransform().GetPosition(), tr.GetPosition(), cam.GetVec3Up());
			glUniformMatrix4fv(core.GetUniformMatrixs().nViewMatrix, 1, GL_FALSE, glm::value_ptr(core.GetMatrixs().ViewMatrix));
			break;
		case GLFW_KEY_UP:
			window.GetCamera().transform.position += glm::vec3(0, 1.0f, 0);
			core.GetMatrixs().ViewMatrix = glm::lookAt(cam.GetTransform().GetPosition(), tr.GetPosition(), cam.GetVec3Up());
			glUniformMatrix4fv(core.GetUniformMatrixs().nViewMatrix, 1, GL_FALSE, glm::value_ptr(core.GetMatrixs().ViewMatrix));
			break;
		case GLFW_KEY_LEFT:
			window.GetCamera().transform.position -= glm::vec3(1.0f, 0, 0);
			core.GetMatrixs().ViewMatrix = glm::lookAt(cam.GetTransform().GetPosition(), tr.GetPosition(), cam.GetVec3Up());
			glUniformMatrix4fv(core.GetUniformMatrixs().nViewMatrix, 1, GL_FALSE, glm::value_ptr(core.GetMatrixs().ViewMatrix));
			break;
		case GLFW_KEY_RIGHT:
			window.GetCamera().transform.position += glm::vec3(1.0f, 0, 0);
			core.GetMatrixs().ViewMatrix = glm::lookAt(cam.GetTransform().GetPosition(), tr.GetPosition(), cam.GetVec3Up());
			glUniformMatrix4fv(core.GetUniformMatrixs().nViewMatrix, 1, GL_FALSE, glm::value_ptr(core.GetMatrixs().ViewMatrix));
			break;*/
		case GLFW_KEY_W:
			GLint modes[2];
			glGetIntegerv(GL_POLYGON_MODE, modes);
			modes[0] = modes[0] == GL_LINE ? GL_FILL : GL_LINE;
			glPolygonMode(GL_FRONT_AND_BACK, modes[0]);
			std::cerr << "glPolygonMode: " << modes[0] << ", " << modes[1] << std::endl;
			break;
		}
	}

	static void GetScrolling(GLFWwindow* pWindow, double x, double y)
	{
		Window& window_data = *static_cast<Window*>(glfwGetWindowUserPointer(pWindow));

		int width, height;
		glfwGetWindowSize(pWindow, &width, &height);
		window_data.mainCamera.fov += static_cast<float>(y);
		if(window_data.mainCamera.fov < 1.0f) window_data.mainCamera.fov = 1.0f;
		if(window_data.mainCamera.fov > 180.0f) window_data.mainCamera.fov = 180.0f;

		const GLint n_uniform_mesh_projection_matrix = glGetUniformLocation(window_data.GetMeshProgram().GetID(), "proj");
		window_data.GetMeshProgram().Use();
		glUniformMatrix4fv(n_uniform_mesh_projection_matrix, 1, GL_FALSE, glm::value_ptr(window_data.GetProjectionMatrix()));

		const GLint n_uniform_light_projection_matrix = glGetUniformLocation(window_data.GetLightProgram().GetID(), "proj");
		window_data.GetLightProgram().Use();
		glUniformMatrix4fv(n_uniform_light_projection_matrix, 1, GL_FALSE, glm::value_ptr(window_data.GetProjectionMatrix()));
	}

	static void GetSize(GLFWwindow* pWindow, int width, int height)
	{
		if(width * height == 0) return;

		const Window& window_data = *static_cast<Window*>(glfwGetWindowUserPointer(pWindow));

		glViewport(0, 0, width, height);
		
		const GLint n_uniform_mesh_projection_matrix = glGetUniformLocation(window_data.GetMeshProgram().GetID(), "proj");
		window_data.GetMeshProgram().Use();
		glUniformMatrix4fv(n_uniform_mesh_projection_matrix, 1, GL_FALSE, glm::value_ptr(window_data.GetProjectionMatrix()));

		const GLint n_uniform_light_projection_matrix = glGetUniformLocation(window_data.GetLightProgram().GetID(), "proj");
		window_data.GetLightProgram().Use();
		glUniformMatrix4fv(n_uniform_light_projection_matrix, 1, GL_FALSE, glm::value_ptr(window_data.GetProjectionMatrix()));
	}
};
