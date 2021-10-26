#pragma once
#include <GL/glew.h>

struct Window
{
public:
	float FovY = 45.0f;
	GLuint ProgramID;
	GLuint LightProgramID;
};
