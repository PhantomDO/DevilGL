#include "ShaderProgram.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>


void ShaderProgram::ShaderCompilationTest(const GLuint& vertexShader)
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

void ShaderProgram::ProgramShaderLinkedTest(const GLint& program, const GLuint& vertexShader, const GLuint& fragmentShader)
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

ShaderProgram::ShaderProgram(const Shader& vertex, const Shader& fragment)
{
	std::cout << ReadShaderFile(vertex.path.c_str()) << std::endl;
	const GLuint vertexShader = glCreateShader(vertex.type);
	const auto vertexSource = const_cast<GLchar*>((vertex.path).c_str());
	glShaderSource(vertexShader, 1, &vertexSource, nullptr);
	glCompileShader(vertexShader);
	ShaderCompilationTest(vertexShader);

	std::cout << ReadShaderFile(fragment.path.c_str()) << std::endl;
	const GLuint fragmentShader = glCreateShader(fragment.type);
	const auto fragmentSource = const_cast<GLchar*>((fragment.path).c_str());
	glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
	glCompileShader(fragmentShader);
	ShaderCompilationTest(fragmentShader);

	m_ID = glCreateProgram();
	glAttachShader(m_ID, vertexShader);
	glAttachShader(m_ID, fragmentShader);
	glLinkProgram(m_ID);
	ProgramShaderLinkedTest(m_ID, vertexShader, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

std::string ShaderProgram::ReadShaderFile(const char* shader)
{
	// lis le fichier 
	std::ifstream file(shader);
	if (!file) return std::string();

	size_t size = file.gcount();

	// remet les caractere au depart du fichier
	file.clear();
	file.seekg(0, std::ios_base::beg);

	// copie les caractere dans le string stream
	std::stringstream sstr;
	sstr << file.rdbuf();
	file.close();

	// renvoie une string du string stream pass�
	return sstr.str();
}
