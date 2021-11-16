#include <iostream>
#include <string>

#include "Helper.h"
#include "Input.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Window.h"

//#ifdef WIN32
//This magic line is to force notebook computer that share NVidia and Intel graphics to use high performance GPU (NVidia).
//Intel graphics doesn't support OpenGL > 1.2
extern "C" _declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
//#endif

const GLfloat PI = 3.1415926535897932384626433832795f;

int main( int argc, char * argv[])
{
#ifdef WIN32
  //Passe la console en UTF-8, permettant d'afficher les accents.
  //Tous les fichiers de cette solution sont encodés en UTF-8.
	SetConsoleOutputCP(65001);
#endif
	const int window_width = 800;
	const int window_height = 600;
	Window* window = new Window(window_width, window_height);
		
	// pointeur sur les touche du claver
	glfwSetKeyCallback(window->GetWindowPtr(), Input::GetKeyDown);
	glfwSetScrollCallback(window->GetWindowPtr(), Input::GetScrolling);
	glfwSetWindowSizeCallback(window->GetWindowPtr(), Input::GetSize);

	// COLOR
	glm::vec3* background = new glm::vec3(0.33f, 1.0f, 1.0f);
	auto orange = glm::vec3(0.39f, 1.0f, 1.0f);
	auto blue = glm::vec3(1.0f, 1.0f, 1.0f);	
	glClearColor(background->r,	background->g,	background->b,	1.0f);

	// mesh
	int count;
	std::vector<Mesh> meshes;
	std::cout << "How many mesh do you want ?";
	std::cin >> count;
	meshes.reserve(count);
	for (int i = 0; i < count; ++i)
	{
		meshes.emplace_back("./models/cube.obj");
	}

	window->SetMeshProgram(ShaderProgram(
		Shader{ GL_VERTEX_SHADER, "MeshVertexShader.glsl" }, 
		Shader{ GL_FRAGMENT_SHADER, "MeshFragmentShader.glsl" }));
			
	// pointeur sur la couleur de la fenetre
	glfwSetWindowUserPointer(window->GetWindowPtr(), background);
	/// pointeur sur la position de la souris
	glfwSetCursorPosCallback(window->GetWindowPtr(), Input::CursorPosCallback);

	//// utilise le programe creer precedement
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glfwSetTime(0);	
	//// change la couleur de la fenetre
	glClearColor(1.f, 0.08f, 0.58f, 1.f);

	const GLint matrixID = glGetUniformLocation(window->GetMeshProgram().GetID(), "mvp");

	// pointeur sur la camera de la fenetre
	glfwSetWindowUserPointer(window->GetWindowPtr(), window);
	// pointeur sur la mouse wheel
	glfwSetScrollCallback(window->GetWindowPtr(), Input::GetScrolling);
	// pointeur sur les touche du claver
	glfwSetKeyCallback(window->GetWindowPtr(), Input::GetKeyDown);


	while (!glfwWindowShouldClose(window->GetWindowPtr()))
	{
		glfwPollEvents();
		// remet la couleur par default
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		window->GetMeshProgram().Use();
		for (auto mesh : meshes)
		{
			glUniformMatrix4fv(matrixID, 1, GL_FALSE, glm::value_ptr(mesh.GetMVPMatrix(
				window->camera.GetProjectionMatrix(), window->camera.GetViewMatrix())));
			mesh.Draw(window->GetMeshProgram());
		}
		
		glfwSwapBuffers(window->GetWindowPtr());
	}

	glfwTerminate();

	return 0;
}