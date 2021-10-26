#include "ShaderProgram.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>


void ShaderProgram::ShaderCompilationTest(GLint vertexShader)
{
	GLint isCompiled;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

		for (auto& i : infoLog)
			std::cout << i;
	}
}

void ShaderProgram::ProgramShaderLinkedTest(GLint program, GLint vertexShader, GLint fragmentShader)
{
	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
	}
}

std::string ShaderProgram::ReadShaderFile(const char* shader)
{
	// lis le fichier 
	std::ifstream file(shader);
	if (!file) return std::string();

	size_t size = file.gcount();

	// remet les caract�re au d�part du fichier
	file.clear();
	file.seekg(0, std::ios_base::beg);

	// copie les caract�re dans le string stream
	std::stringstream sstr;
	sstr << file.rdbuf();
	file.close();

	// renvoie une string du string stream pass�
	return sstr.str();
}
