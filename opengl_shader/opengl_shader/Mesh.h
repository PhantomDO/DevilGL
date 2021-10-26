#pragma once
#include <string>
#include <vector>
#include <GL/glew.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

class Mesh
{
public:
	Mesh(const std::string& path);
	bool LoadFromFile(const std::string& path);

public:
	size_t GetVerticesCount() const { return m_Vertices.size(); }
	size_t GetIndicesCount() const { return m_Triangles.size(); }
	size_t GetNormalCount() const { return m_Normals.size(); }
	size_t GetUVCount() const { return m_UVs.size(); }
	size_t GetStrides() const { return (sizeof(glm::vec3) * (GetVerticesCount() + GetNormalCount())) + (sizeof(glm::vec2) * GetUVCount()); }
	
	std::vector<glm::vec3> GetVertices() const { return m_Vertices; }
	const GLsizei* GetIndices() const { return m_Triangles.data(); }
	std::vector<glm::vec3> GetNormals() const { return m_Normals; }
	std::vector<glm::vec2> GetUVs() const { return m_UVs; }

	GLuint GetVAO() const { return m_VAO; }
	GLuint GetVBO() const { return m_VBO; }
	GLuint GetEBO() const { return m_EBO; }
	
private:
	std::vector<glm::vec3> m_Vertices;
	std::vector<glm::vec3> m_Normals;
	std::vector<glm::vec2> m_UVs;
	std::vector<GLsizei> m_Triangles;

	GLuint m_VAO;
	GLuint m_VBO;
	GLuint m_EBO;
};
