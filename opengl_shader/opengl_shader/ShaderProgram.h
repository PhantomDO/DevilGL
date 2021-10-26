#pragma once
#include <iostream>
#include <GL/glew.h>

#include "Shader.h"

class ShaderProgram
{
public:
	ShaderProgram(const Shader& shader)
	{
		std::cout << ReadShaderFile(shader.path.c_str()) << std::endl;

		m_ProgramID = glCreateShader(shader.type);
		m_ShaderSource = const_cast<GLchar*>((shader.path).c_str());
		glShaderSource(m_ProgramID, 1, &m_ShaderSource, nullptr);
		glCompileShader(m_ProgramID);

		ShaderCompilationTest(m_ProgramID);
	}

	static void ProgramShaderLinkedTest(GLint program, GLint vertexShader, GLint fragmentShader);

public:
	GLint GetProgramID() const { return m_ProgramID; }

	void ShaderCompilationTest(GLint vertexShader);	
	std::string ReadShaderFile(const char* shader);
private:

	GLint m_ProgramID;
	GLchar* m_ShaderSource;
};
