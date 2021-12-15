#include "Input.h"

#include "Time.h"

void Engine::Input::CursorPosCallback(GLFWwindow* pWindow, double x, double y)
{
	int windowSizeX, windowSizeY;

	Engine::Window& window = *(reinterpret_cast<Engine::Window*>(glfwGetWindowUserPointer(pWindow)));
	//glm::vec3& color = *(static_cast<glm::vec3*>(glfwGetWindowUserPointer(pWindow)));
		
	// recupere taille de la fenetre
	glfwGetWindowSize(pWindow, &windowSizeX, &windowSizeY);

	glm::vec2 offset = glm::vec2(window.mousePosition.x - static_cast<float>(x),
		window.mousePosition.y - static_cast<float>(y)); // y reversed (bottom to up)

	window.mousePosition = glm::vec2(static_cast<float>(x), static_cast<float>(y));
	window.camera.ProcessMouseMouvement(offset);
	//color = Helper::HSVtoRGB(glm::vec3(color.r, static_cast<float>(x/windowSizeX), static_cast<float>(y/windowSizeY)));
}

void Engine::Input::GetKeyDown(GLFWwindow* pWindow, int key, int scanCode, int action, int mods)
{
	if(action == GLFW_RELEASE) return;

	Engine::Window& window = *(reinterpret_cast<Engine::Window*>(glfwGetWindowUserPointer(pWindow)));
	window.camera.ProcessKeyboardEvent(key, Engine::Time::deltaTime);
	
	// Trouver l'utilité
	switch (key)
	{
	case GLFW_KEY_Z:
		GLint modes[2];
		glGetIntegerv(GL_POLYGON_MODE, modes);
		modes[0] = modes[0] == GL_LINE ? GL_FILL : GL_LINE;
		glPolygonMode(GL_FRONT_AND_BACK, modes[0]);
		std::cerr << "glPolygonMode: " << modes[0] << ", " << modes[1] << std::endl;
		break;
	}
}

void Engine::Input::GetScrolling(GLFWwindow* pWindow, double x, double y)
{
	Window& window = *(reinterpret_cast<Window*>(glfwGetWindowUserPointer(pWindow)));

	int width, height;
	glfwGetWindowSize(pWindow, &width, &height);
	window.camera.ProcessMouseScroll(static_cast<float>(y));
	window.camera.SetProjectionMatrix(width, height);
}

void Engine::Input::GetSize(GLFWwindow* pWindow, int width, int height)
{
	if(width * height == 0) return;

	Window& window = *(reinterpret_cast<Window*>(glfwGetWindowUserPointer(pWindow)));

	glViewport(0, 0, width, height);
		
	const GLint n_uniform_mesh_projection_matrix = glGetUniformLocation(window.GetMeshProgram().GetID(), "proj");
	window.GetMeshProgram().Use();
	glUniformMatrix4fv(n_uniform_mesh_projection_matrix, 1, GL_FALSE, glm::value_ptr(window.camera.GetProjectionMatrix()));

	const GLint n_uniform_light_projection_matrix = glGetUniformLocation(window.GetLightProgram().GetID(), "proj");
	window.GetLightProgram().Use();
	glUniformMatrix4fv(n_uniform_light_projection_matrix, 1, GL_FALSE, glm::value_ptr(window.camera.GetProjectionMatrix()));
}
