#include "ShaderProgram.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>


bool ShaderProgram::ShaderCompilationTest(const GLuint& shader)
{
	GLint isCompiled = GL_FALSE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

		for (const auto& i : infoLog)
			std::cout << i;

		return false;
	}

	return true;
}

bool ShaderProgram::ProgramShaderLinkedTest(const GLint& program, const GLuint& vertexShader,
                                            const GLuint& fragmentShader)
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
		return false;
	}
	return true;
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

ShaderProgram::ShaderProgram(const Shader& vertex, const Shader& fragment)
{
	const auto vertexSource = const_cast<GLchar*>((vertex.path).c_str());
	std::cout << ReadShaderFile(vertexSource) << std::endl;
	const GLuint vertexShader = glCreateShader(vertex.type);
	glShaderSource(vertexShader, 1, &vertexSource, nullptr);
	glCompileShader(vertexShader);
	if (!ShaderCompilationTest(vertexShader))
	{
		glDeleteShader(vertexShader);
		std::cerr << "Error when compiling vertex shader" << std::endl;
	}
	
	const auto fragmentSource = const_cast<GLchar*>((fragment.path).c_str());
	std::cout << ReadShaderFile(fragmentSource) << std::endl;
	const GLuint fragmentShader = glCreateShader(fragment.type);
	glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
	glCompileShader(fragmentShader);
	if (!ShaderCompilationTest(fragmentShader))
	{
		glDeleteShader(fragmentShader);
		std::cerr << "Error when compiling fragment shader" << std::endl;
	}

	m_ID = glCreateProgram();
	glAttachShader(m_ID, vertexShader);
	glAttachShader(m_ID, fragmentShader);
	glLinkProgram(m_ID);
	if (!ProgramShaderLinkedTest(m_ID, vertexShader, fragmentShader))
	{
		glDeleteProgram(m_ID);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		std::cerr << "Error when compiling program" << std::endl;
	}
	
	glDetachShader(m_ID, vertexShader);
	glDetachShader(m_ID, fragmentShader);
}
