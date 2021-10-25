#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main( int argc, char * argv[])
{
	glfwInit(); //Fonction de la bibliothèque GLFW
	glewInit(); //Fonction de la bibliothèque GLEW
	glGetString(GL_VERSION); //Fonction de la bibliothèque OpenGL du système
	return 0;
}