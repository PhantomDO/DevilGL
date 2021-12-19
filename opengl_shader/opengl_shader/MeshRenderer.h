#pragma once
#include <memory>

#include "Component.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Texture2D.h"

namespace Engine
{
	class MeshRenderer : public Component
	{
		CLASS_DECLARATION(MeshRenderer)

	private:

		GLuint m_VAO;
		GLuint m_VBO;
		GLuint m_EBO;

		std::vector<std::shared_ptr<Texture2D>> m_Textures;
		std::unique_ptr<Mesh> m_Mesh;
		void Setup();
		
	public:

		Mesh& GetMesh();
		void SetMesh(Mesh&& mesh);

		std::vector<std::shared_ptr<Texture2D>> GetTextures() { return m_Textures; }
		void AddTexture(Texture2D&& tex);
		void RemoveTexture(const uint32_t& index);

		//std::vector<Material> materials;
		//Material GetPrincipalMaterial()

		void Draw(const ShaderProgram& shader) const;

		static glm::mat4 GetMVPMatrix(const glm::mat4& projection, const glm::mat4& view, const glm::mat4& model);
		static glm::mat4 GetMVMatrix(const glm::mat4& view, const glm::mat4& model);

		GLuint GetVAO() const { return m_VAO; }
		GLuint GetVBO() const { return m_VBO; }
		GLuint GetEBO() const { return m_EBO; }

	public:
		MeshRenderer()
			: Component(), m_VAO(0), m_VBO(0), m_EBO(0), m_Mesh(nullptr)
		{
		}

		~MeshRenderer() override
		{
			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(2);
			m_Mesh = nullptr;
		}

	public:

		//MeshRenderer& operator =(const MeshRenderer& mr) = default;
		//MeshRenderer& operator =(MeshRenderer&& mr) = default;
	};
}

