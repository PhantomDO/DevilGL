#pragma once
#include <iostream>
#include <GL/glew.h>

#include "Shader.h"

class ShaderProgram
{
public:

	ShaderProgram() = default;
	ShaderProgram(const Shader& vertex, const Shader& fragment);
	GLint GetID() const { return m_ID; }
	void Use() const { glUseProgram(m_ID); }

public:

	static std::string ReadShaderFile(const std::string& shader);

	static bool ShaderCompilationTest(const GLuint& shader);	
	static bool ProgramShaderLinkedTest(const GLint& program, const GLuint& vertexShader, const GLuint& fragmentShader);
	
private:

	GLint m_ID;
};
