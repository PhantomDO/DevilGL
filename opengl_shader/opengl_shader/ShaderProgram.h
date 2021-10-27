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
	void Use() { glUseProgram(m_ID); }

public:

	static std::string ReadShaderFile(const char* shader);
	static void ShaderCompilationTest(const GLuint& vertexShader);	
	static void ProgramShaderLinkedTest(const GLint& program, const GLuint& vertexShader, const GLuint& fragmentShader);
	
private:

	GLint m_ID;
};
