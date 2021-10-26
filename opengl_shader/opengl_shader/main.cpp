#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Helper.h"
#include "Input.h"
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

	///#############################################################################
	///                    Initialisation de la fenêtre
	///#############################################################################

	const int window_width = 800;
	const int window_height = 600;

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

	GLFWwindow* pWindow = glfwCreateWindow(window_width, window_height, "Hello World", NULL, NULL);
	if (!pWindow) 
	{
		Helper::Terminate("Impossible de créer la fenêtre !");
	}
	
	glfwMakeContextCurrent(pWindow);
	glEnable(GL_MULTISAMPLE);
	glewExperimental = GL_TRUE;

	GLenum err;
	if((err = glewInit()) != GLEW_OK) /* Problem: glewInit failed, something is seriously wrong. */
	{
		Helper::Terminate(std::string("Error: ") + reinterpret_cast<const char*>(glewGetErrorString(err)));
	}
	
	Helper::RendererInfo();

	Window windowData;
	glfwSetWindowUserPointer(pWindow, &windowData);
	
	// pointeur sur les touche du claver
	glfwSetKeyCallback(pWindow, Input::GetKeyDown);
	glfwSetScrollCallback(pWindow, Input::GetScrolling);
	glfwSetWindowSizeCallback(pWindow, Input::GetSize);

	// COLOR
	glm::vec3* backgroundColor = new glm::vec3(0.33f, 1.0f, 1.0f);
	std::cout	<< backgroundColor->r << ", "
				<< backgroundColor->g << ", "
				<< backgroundColor->b << std::endl;

	auto orangeColor = glm::vec3(0.39f, 1.0f, 1.0f);
	auto blueColor = glm::vec3(1.0f, 1.0f, 1.0f);
	
	glClearColor(
		backgroundColor->r,
		backgroundColor->g,
		backgroundColor->b,
		1.0f
	);

	// VERTICES
	GLfloat vertices[]{
		-0.5f	,	0.25f,
		 0.5f	,	0.25f,
		 0.5f	,	-0.25f,
		 -0.5f	,	-0.25f,

		 -0.5f	,	-0.25f,
		 0.5f	,	-0.25f,
		 0.5f	,	-0.75f,
		 -0.5f	,	-0.75f,
	};

	// VERTICES
	GLuint indices[]{
		0, 2, 3,
		0, 1, 2,

		4, 6, 7,
		4, 5, 6,
	};

	// VAO
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// VBO
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	// Attribution du tableau au GPU qui le transform en vec2
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(0));
	glEnableVertexAttribArray(0);

	// EBO
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		
	// vertex reading stream	
	std::string vertexStr = Helper::ReadShaderFile("TriangleVertexShader.glsl");
	std::cout << vertexStr << std::endl;

	// Creation du vertexShader
	GLint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLchar* vertexShaderSource = (GLchar*)(vertexStr).c_str();
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	// test de compilation du vertex shader
	Helper::ShaderCompilationTest(vertexShader);

	// fragment reading stream
	std::string fragmentStr = Helper::ReadShaderFile("TriangleFragmentShader.glsl");
	std::cout << fragmentStr << std::endl;

	// Creation du fragmentShader
	GLint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	GLchar* fragmentShaderSource = (GLchar*)(fragmentStr).c_str();
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);

	// test de compilation du fragment shader
	Helper::ShaderCompilationTest(fragmentShader);
	
	// Creation du program
	windowData.ProgramID = glCreateProgram();
	glAttachShader(windowData.ProgramID, vertexShader);
	glAttachShader(windowData.ProgramID, fragmentShader);
	glLinkProgram(windowData.ProgramID);

	// test de link du program avec les shader
	Helper::ProgramShaderLinkedTest(windowData.ProgramID, vertexShader, fragmentShader);
		
	// pointeur sur la couleur de la fenetre
	glfwSetWindowUserPointer(pWindow, backgroundColor);
	/// pointeur sur la position de la souris
	glfwSetCursorPosCallback(pWindow, Input::CursorPosCallback);

	//// utilise le programe creer precedement
	glEnable(GL_DEPTH_TEST);

	glfwSetTime(0);
	glClearColor(0,0,0,1);
	
	while (!glfwWindowShouldClose(pWindow))
	{
		glfwPollEvents();

		// change la couleur de la fenetre
		glClearColor(backgroundColor->r,	backgroundColor->g,	backgroundColor->b,	1.0f);
		// remet la couleur par default
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glUseProgram(windowData.ProgramID);

		// affiche le triangle depuis le vbo
		glDrawArrays(GL_TRIANGLES, 0, 2);

		// affiche le rect depuis le ebo
		glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, (GLvoid*)(0));
		// affiche ls triangles rempli
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		// affiche le rect depuis le ebo
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid*)(0));
		// affiche ls triangles en fil de fer
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		glfwSwapBuffers(pWindow);
	}
	
	glfwTerminate();

	return 0;
}