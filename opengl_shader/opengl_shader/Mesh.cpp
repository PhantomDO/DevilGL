#include "Mesh.h"

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "Helper.h"

Mesh::Mesh(const std::string& path)
{
	if (!LoadFromFile(path))
	{
		Helper::Terminate("Can't load obj");
	}

	//Allocation des buffers
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	
	//Spécification des vertices pour le mesh
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(glm::vec3), &m_Vertices.front(), GL_STATIC_DRAW);

	//spécifie l'organisation de l'entrée du vertex shader
	//Positions
	glVertexAttribPointer(0, m_Vertices.size(), GL_FLOAT, GL_FALSE, GetStrides(), reinterpret_cast<GLvoid*>(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);
	//normales
	glVertexAttribPointer(1, m_Normals.size(), GL_FLOAT, GL_FALSE, GetStrides(), reinterpret_cast<GLvoid*>(m_Vertices.size() * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	//Coordonnées de textures
	glVertexAttribPointer(2, m_UVs.size(), GL_FLOAT, GL_FALSE, GetStrides(), reinterpret_cast<GLvoid*>(m_Vertices.size() + m_Normals.size() * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glGenBuffers(1, &m_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(glm::vec<3, int, glm::defaultp>) * m_Triangles.size() * sizeof(GLuint), &m_EBO, GL_STATIC_DRAW);
}

struct FaceVert
{
    FaceVert() : vertex(-1), normal(-1), uv(-1) {}

    int vertex;
    int normal;
    int uv;
};

struct VertexLess {
    bool operator() (const FaceVert& lhs, const FaceVert& rhs) const
    {
        if (lhs.vertex != rhs.vertex) return (lhs.vertex < rhs.vertex);
        if (lhs.normal != rhs.normal) return (lhs.normal < rhs.normal);
        if (lhs.uv != rhs.uv) return (lhs.uv < rhs.uv);
        return false;
    }
};

bool Mesh::LoadFromFile(const std::string& path)
{
	std::ifstream in;
	in.open(path, std::ifstream::in);

	if (in.fail())
	{
		std::cerr << "Failed to open " << path << std::endl;
		return false;
	}

	m_Vertices.clear();
	m_Normals.clear();
	m_UVs.clear();
	m_Triangles.clear();

	std::vector<glm::vec3> tmpVertices;
	std::vector<glm::vec3> tmpNormals;
	std::vector<glm::vec2> tmpUvs;

	std::cerr << "Loading mesh..." << std::endl;

	std::map<FaceVert, int, VertexLess> uniqueVertices;
	uint32_t vertexCount = 0;
	std::string line;

	while(!in.eof())
	{
		std::getline(in, line);
		std::istringstream iss(line);

		char trash;
		if (!line.compare(0, 2, "v "))
		{
			iss >> trash;
			glm::vec3 vertex;
			float w = 1.f;
			for (int i = 0; i < 4; i++)
			{
				if (i == 4 && iss >> w)
				{
					iss >> w;
				}
				else 
				{
					iss >> vertex[i];
				}
			}
			tmpVertices.push_back(vertex / w);
		}
		else if (!line.compare(0, 2, "vt "))
		{
			iss >> trash;
			glm::vec2 uv;			
			for (int i = 0; i < 2; i++)
			{
				iss >> uv[i];
			}
			tmpUvs.push_back(uv);
		}
		else if (!line.compare(0, 2, "vn "))
		{
			iss >> trash;
			glm::vec3 normal;			
			for (int i = 0; i < 3; i++)
			{
				iss >> normal[i];
			}
			tmpNormals.push_back(normal);
		}
		else if (!line.compare(0, 2, "f "))
		{
			std::vector<int32_t> vertexIndices;
			std::vector<int32_t> normalIndices;
			std::vector<int32_t> uvIndices;

			glm::vec<3, int, glm::defaultp> face;
			
			int vCount = 0, nCount = 0, uvCount = 0;
			auto subLine= line.substr(2);
			const char* linePtr = subLine.c_str();
			while (linePtr[0] != 0)
			{
				while(linePtr[0] == ' ') ++linePtr;

				int vi = 0, ni = 0, uvi = 0;

				if (sscanf_s(linePtr, "%d/%d/%d", &vi, &ni, &uvi) == 3)
				{
					vertexIndices.push_back(vi - 1); 
					normalIndices.push_back(ni - 1); 
					uvIndices.push_back(uvi - 1); 
				}
				else if (sscanf_s(linePtr, "%d//%d", &vi, &ni) == 2)
				{
					vertexIndices.push_back(vi - 1); 
					normalIndices.push_back(ni - 1);
				}
				else if (sscanf_s(linePtr, "%d/%d", &vi, &uvi) == 2)
				{
					vertexIndices.push_back(vi - 1); 
					uvIndices.push_back(uvi - 1); 
				}
				else if (sscanf_s(linePtr, "%d", &vi) == 1)
				{
					vertexIndices.push_back(vi - 1); 
				}

				while(linePtr[0] != ' ' && linePtr[0] != 0) ++linePtr;
			}

			for (uint32_t i = 0; i < vertexIndices.size() - 1; ++i)
			{
				FaceVert tri;
				tri.vertex = vertexIndices[0];
				if (!normalIndices.empty()) tri.normal = normalIndices[0];
				if (!uvIndices.empty()) tri.normal = uvIndices[0];

				if (uniqueVertices.count(tri) == 0) uniqueVertices[tri] = vertexCount++;
				face[0] = uniqueVertices[tri];
								
				tri.vertex = vertexIndices[i];
				if (!normalIndices.empty()) tri.normal = normalIndices[i];
				if (!uvIndices.empty()) tri.normal = uvIndices[i];
				
				if (uniqueVertices.count(tri) == 0) uniqueVertices[tri] = vertexCount++;
				face[1] = uniqueVertices[tri];

				tri.vertex = vertexIndices[i + 1];
				if (!normalIndices.empty()) tri.normal = normalIndices[i + 1];
				if (!uvIndices.empty()) tri.normal = uvIndices[i + 1];
				
				if (uniqueVertices.count(tri) == 0) uniqueVertices[tri] = vertexCount++;
				face[2] = uniqueVertices[tri];

				for (int i = 0; i < 3; i++)
				{
					m_Triangles.push_back(face[i]);
				}
			}
		}
	}

	in.close();

	m_Vertices.resize(vertexCount);
	if (!m_Normals.empty()) m_Normals.resize(vertexCount);
	if (!m_UVs.empty()) m_UVs.resize(vertexCount);

	std::map<FaceVert, int, VertexLess>::iterator iter;
	for (iter = uniqueVertices.begin(); iter != uniqueVertices.end(); ++iter)
	{
		m_Vertices[iter->second] = tmpVertices[iter->first.vertex];		
		if (!m_Normals.empty()) m_Normals[iter->second] = tmpNormals[iter->first.normal];
		if (!m_UVs.empty()) m_UVs[iter->second] = tmpUvs[iter->first.uv];
	}

	return true;
}
