#pragma once
#include <string>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Bounds.h"
#include "ShaderProgram.h"
#include "Transform.h"

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 UV;
};

struct Texture
{
	GLuint id;
	std::string type;
};

/// <summary>
/// https://www.math.ucsd.edu/~sbuss/MathCG2/OpenGLsoft/BasicDrawModes/explainBDM.html
/// </summary>
class Mesh
{
public:
	Mesh(const std::string& path);
	Mesh(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices);
	~Mesh();
	bool LoadFromFile(const std::string& path);
	void Setup();
	void Draw(const ShaderProgram& shader) const;
public:
	
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;
	Transform transform;

	glm::mat4 GetMVPMatrix(const glm::mat4& projection, const glm::mat4& view, const glm::mat4& model = glm::mat4(1.0f))
	{
		return projection * view * model;
	}

	Bounds bounds;

	GLuint GetVAO() const { return m_VAO; }
	GLuint GetVBO() const { return m_VBO; }
	GLuint GetEBO() const { return m_EBO; }
	
private:

	GLuint m_VAO;
	GLuint m_VBO;
	GLuint m_EBO;
};
