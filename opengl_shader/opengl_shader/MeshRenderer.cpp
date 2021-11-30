#include "MeshRenderer.h"

#include <functional>

#include "Debug.h"
#include "Helper.h"

void MeshRenderer::Setup()
{
	if (m_Mesh == nullptr) return;

	//Allocation des buffers
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);

	//Spécification des vertices pour le m_Mesh
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

	glBufferData(GL_ARRAY_BUFFER, m_Mesh->vertices.size() * sizeof(Vertex), &m_Mesh->vertices.front(), GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Mesh->indices.size() * sizeof(GLuint), &m_Mesh->indices.front(), GL_STATIC_DRAW);

	//spécifie l'organisation de l'entrée du vertex shader
	//Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(0));
	//normales
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(offsetof(Vertex, normal)));
	//Coordonnées de textures
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(offsetof(Vertex, uv)));

	glBindVertexArray(0);
}

void MeshRenderer::SetMesh(const Mesh& mesh)
{
	m_Mesh = std::make_shared<Mesh>(mesh);
	Setup();
}

void MeshRenderer::SetMesh(Mesh&& mesh)
{
	m_Mesh = std::make_shared<Mesh>(std::move(mesh));
	Setup();
}

void MeshRenderer::AddTexture(const Texture2D& tex)
{
	m_Textures.emplace_back(std::make_shared<Texture2D>(tex));
}

void MeshRenderer::AddTexture(Texture2D&& tex)
{
	m_Textures.emplace_back(std::make_shared<Texture2D>(std::move(tex)));
}

void MeshRenderer::RemoveTexture(const uint32_t& index)
{
	if (index > m_Textures.size() - 1)
	{
		Debug::LogError("Index out of range.");
		return;
	}

	m_Textures.erase(m_Textures.begin() + index);
}

void MeshRenderer::Draw(const ShaderProgram& shader) const
{
	if (m_Mesh == nullptr) return;

	for (auto& tex : m_Textures)
	{
		tex->Bind();
	}

	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, m_Mesh->indices.size(), GL_UNSIGNED_INT, static_cast<GLvoid*>(0));
	glBindVertexArray(0);
}

glm::mat4 MeshRenderer::GetMVPMatrix(const glm::mat4& projection, const glm::mat4& view, const glm::mat4& model)
{
	return projection * view * model;
}

glm::mat4 MeshRenderer::GetMVMatrix(const glm::mat4& view, const glm::mat4& model)
{
	return view * model;
}
