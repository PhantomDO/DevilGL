#pragma once
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Mesh.h"
#include "Tools.h"

struct LightParameters
{
	GLuint position;
	GLuint ambiant;
	GLuint diffuse;
	GLuint specular;

	LightParameters() = default;

	LightParameters(const int& programId)
	{
		Setup(programId);
	}

	LightParameters(const int& programId, const int& index)
	{
		Setup(programId, index);
	}

	void Setup(const int& programId, const int& index = -1)
	{
		position = glGetUniformLocation(programId, index < 0 ? "light.position" : Tools::StringFormat("light[%d].position", index).c_str());
		ambiant = glGetUniformLocation(programId, index < 0 ? "light.ambiant" : Tools::StringFormat("light[%d].ambiant", index).c_str());
		diffuse = glGetUniformLocation(programId, index < 0 ? "light.diffuse" : Tools::StringFormat("light[%d].diffuse", index).c_str());
		specular = glGetUniformLocation(programId, index < 0 ? "light.specular" : Tools::StringFormat("light[%d].specular", index).c_str());
	}
};

struct Light
{
	glm::vec3 position;
	glm::vec3 ambiant;
	glm::vec3 diffuse;
	glm::vec3 specular;

	LightParameters parameters = LightParameters{};
	std::shared_ptr<Mesh> mesh = nullptr;
	
	Light() = default;

	Light(const glm::vec3& position, const glm::vec3& ambiant, const glm::vec3& diffuse, const glm::vec3& specular)
		: position(position), ambiant(ambiant), diffuse(diffuse), specular(specular)
	{
	}
};
