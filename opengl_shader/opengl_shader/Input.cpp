#include "Input.h"

void Input::CursorPosCallback(GLFWwindow* pWindow, double x, double y)
{
	int windowSizeX, windowSizeY;
	glm::vec3& color = *(static_cast<glm::vec3*>(glfwGetWindowUserPointer(pWindow)));
		
	// recupere taille de la fenetre
	glfwGetWindowSize(pWindow, &windowSizeX, &windowSizeY);		
	color = Helper::HSVtoRGB(glm::vec3(color.r, static_cast<float>(x/windowSizeX), static_cast<float>(y/windowSizeY)));
}

void Input::GetKeyDown(GLFWwindow* pWindow, int key, int scanCode, int action, int mods)
{
	if(action == GLFW_RELEASE) return;
		
	Window& window = *(reinterpret_cast<Window*>(glfwGetWindowUserPointer(pWindow)));

	const auto cameraSpeed = 0.05f;
	
	// Trouver l'utilité
	switch (key)
	{
	case GLFW_KEY_S:
		window.camera.transform.position = window.camera.transform.position - window.camera.transform.GetForward() * cameraSpeed;
		window.camera.SetViewMatrix();
		break;
	case GLFW_KEY_W:
		window.camera.transform.position += window.camera.transform.GetForward() * cameraSpeed;
		window.camera.SetViewMatrix();
		break;
	case GLFW_KEY_A:
		window.camera.transform.position -= window.camera.transform.GetRight() * cameraSpeed;
		window.camera.SetViewMatrix();
		break;
	case GLFW_KEY_D:
		window.camera.transform.position += window.camera.transform.GetRight() * cameraSpeed;
		window.camera.SetViewMatrix();
		break;
	case GLFW_KEY_Q:
		window.camera.transform.position -= window.camera.transform.GetUp() * cameraSpeed;
		window.camera.SetViewMatrix();
		break;
	case GLFW_KEY_E:
		window.camera.transform.position += window.camera.transform.GetUp() * cameraSpeed;
		window.camera.SetViewMatrix();
		break;

	case GLFW_KEY_Z:
		GLint modes[2];
		glGetIntegerv(GL_POLYGON_MODE, modes);
		modes[0] = modes[0] == GL_LINE ? GL_FILL : GL_LINE;
		glPolygonMode(GL_FRONT_AND_BACK, modes[0]);
		std::cerr << "glPolygonMode: " << modes[0] << ", " << modes[1] << std::endl;
		break;
	}
}

void Input::GetScrolling(GLFWwindow* pWindow, double x, double y)
{
	Window& window = *(reinterpret_cast<Window*>(glfwGetWindowUserPointer(pWindow)));
	Camera& camera = window.camera;

	int width, height;
	glfwGetWindowSize(pWindow, &width, &height);
	std::cout << "Old Camera fov: " << camera.fov << std::endl;

	camera.fov += static_cast<float>(y);

	//if(camera.fov < 0.0f) camera.fov = 359.0f;
	//if(camera.fov > 360.0f) camera.fov = 1.0f;

	camera.SetProjectionMatrix(width, height);

	std::cout << "FoV Y value: " << y << ", Camera FoV: " << camera.fov << std::endl;
	//const GLint n_uniform_mesh_projection_matrix = glGetUniformLocation(window_data.GetMeshProgram().GetID(), "proj");
	//window_data.GetMeshProgram().Use();
	//glUniformMatrix4fv(n_uniform_mesh_projection_matrix, 1, GL_FALSE, glm::value_ptr(window_data.camera.GetProjectionMatrix()));

	//const GLint n_uniform_light_projection_matrix = glGetUniformLocation(window_data.GetLightProgram().GetID(), "proj");
	//window_data.GetLightProgram().Use();
	//glUniformMatrix4fv(n_uniform_light_projection_matrix, 1, GL_FALSE, glm::value_ptr(window_data.camera.GetProjectionMatrix()));
}

void Input::GetSize(GLFWwindow* pWindow, int width, int height)
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
