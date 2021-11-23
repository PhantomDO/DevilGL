#pragma once
#include <memory>

#include "Component.h"
#include "Mesh.h"
#include "ShaderProgram.h"

class MeshRenderer : public Component
{
private:

	std::shared_ptr<Mesh> m_Mesh;
	void Setup();

public:

	std::shared_ptr<Mesh>& GetMesh() { return m_Mesh; }
	void SetMesh(const Mesh& mesh);
	void SetMesh(Mesh&& mesh);

	//std::vector<Material> materials;
	//Material GetPrincipalMaterial()

	void Draw(const ShaderProgram& shader) const;

	glm::mat4 GetMVPMatrix(const glm::mat4& projection, const glm::mat4& view, const glm::mat4& model = glm::mat4(1.0f));
	glm::mat4 GetMVMatrix(const glm::mat4& view, const glm::mat4& model = glm::mat4(1.0f));

	GLuint GetVAO() const { return m_VAO; }
	GLuint GetVBO() const { return m_VBO; }
	GLuint GetEBO() const { return m_EBO; }

public:
	MeshRenderer()
		: m_Mesh(nullptr), m_VAO(0), m_VBO(0), m_EBO(0)
	{

	}

	MeshRenderer(const MeshRenderer& mr)
		: m_Mesh(mr.m_Mesh), m_VAO(mr.m_VAO), m_VBO(mr.m_VBO), m_EBO(mr.m_EBO)
	{

	}

	MeshRenderer(std::shared_ptr<MeshRenderer> mr)
		: m_Mesh(mr->m_Mesh), m_VAO(mr->m_VAO), m_VBO(mr->m_VBO), m_EBO(mr->m_EBO)
	{

	}

	~MeshRenderer() override
	{
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		m_Mesh = nullptr;
	}

private:

	GLuint m_VAO;
	GLuint m_VBO;
	GLuint m_EBO;
};

