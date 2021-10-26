#include <iostream>
#include <string>

#include "Helper.h"
#include "Input.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Window.h"

#ifdef WIN32
//This magic line is to force notebook computer that share NVidia and Intel graphics to use high performance GPU (NVidia).
//Intel graphics doesn't support OpenGL > 1.2
extern "C" _declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
#endif

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
	Mesh mesh = Mesh("./models/duck.obj");

	const auto triangleVertexShader = ShaderProgram(Shader{ GL_VERTEX_SHADER, "TriangleVertexShader.glsl" });
	const auto triangleFragmentShader = ShaderProgram(Shader{ GL_FRAGMENT_SHADER, "TriangleFragmentShader.glsl" });
		
	// Creation du program
	window->SetMeshProgramID(glCreateProgram());
	glAttachShader(window->GetMeshProgramID(), triangleVertexShader.GetProgramID());
	glAttachShader(window->GetMeshProgramID(), triangleFragmentShader.GetProgramID());
	glLinkProgram(window->GetMeshProgramID());

	// test de link du program avec les shader
	ShaderProgram::ProgramShaderLinkedTest(window->GetMeshProgramID(), 
		triangleVertexShader.GetProgramID(), 
		triangleFragmentShader.GetProgramID());
		
	// pointeur sur la couleur de la fenetre
	glfwSetWindowUserPointer(window->GetWindowPtr(), background);
	/// pointeur sur la position de la souris
	glfwSetCursorPosCallback(window->GetWindowPtr(), Input::CursorPosCallback);

	//// utilise le programe creer precedement
	glEnable(GL_DEPTH_TEST);

	glfwSetTime(0);	
	//// change la couleur de la fenetre
	glClearColor(1.f, 0.08f, 0.58f, 1.f);

	while (!glfwWindowShouldClose(window->GetWindowPtr()))
	{
		glfwPollEvents();
		// remet la couleur par default
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glUseProgram(window->GetMeshProgramID());

		glBindVertexArray(mesh.GetVAO());
		glMultiDrawElements(GL_POINTS, mesh.GetIndices(), GL_UNSIGNED_INT, (const GLvoid**)0, 1);

		glfwSwapBuffers(window->GetWindowPtr());
	}
	
	glfwTerminate();

	return 0;
}