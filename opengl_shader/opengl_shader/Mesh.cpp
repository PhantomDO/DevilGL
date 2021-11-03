#include "Mesh.h"

#include <algorithm>
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

	transform = Transform();
	Setup();
	
	std::cerr << "Mesh loaded." << std::endl;
}

Mesh::Mesh(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices)
{
	for (int i = 0; i < vertices.size(); i += 3)
	{
		this->vertices.push_back(Vertex{
			glm::vec3(vertices[i + 0], vertices[i + 1], vertices[i + 2]), 
			glm::vec3(0),
			glm::vec3(0) });
	}

	this->indices = indices;
	transform = Transform();

	Setup();

	std::cerr << "Mesh loaded." << std::endl;
}

Mesh::~Mesh()
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void Mesh::Setup()
{
	//Allocation des buffers
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);

	//Spécification des vertices pour le mesh
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices.front(), GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices.front(), GL_STATIC_DRAW);

	//spécifie l'organisation de l'entrée du vertex shader
	//Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(0));
	//normales
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(offsetof(Vertex, Normal)));
	//Coordonnées de textures
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(offsetof(Vertex, UV)));

	glBindVertexArray(0);
}

void Mesh::Draw(const ShaderProgram& shader) const
{
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, static_cast<GLvoid*>(0));
	glBindVertexArray(0);
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

	vertices.clear();
	indices.clear();
	textures.clear();

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
			for (int i = 0; i <= 3; i++)
			{
				if (i == 3 /*&& iss >> w*/)
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
			
			for (uint32_t i = 1; i < vertexIndices.size() - 1; ++i)
			{
				FaceVert tri;
				tri.vertex = vertexIndices[0];
				if (!normalIndices.empty()) tri.normal = normalIndices[0];
				if (!uvIndices.empty()) tri.normal = uvIndices[0];

				if (uniqueVertices.count(tri) == 0) uniqueVertices[tri] = vertexCount++;
				indices.push_back(uniqueVertices[tri] + 1);
								
				tri.vertex = vertexIndices[i];
				if (!normalIndices.empty()) tri.normal = normalIndices[i];
				if (!uvIndices.empty()) tri.normal = uvIndices[i];
				
				if (uniqueVertices.count(tri) == 0) uniqueVertices[tri] = vertexCount++;
				indices.push_back(uniqueVertices[tri] + 1);

				tri.vertex = vertexIndices[i + 1];
				if (!normalIndices.empty()) tri.normal = normalIndices[i + 1];
				if (!uvIndices.empty()) tri.normal = uvIndices[i + 1];
				
				if (uniqueVertices.count(tri) == 0) uniqueVertices[tri] = vertexCount++;
				indices.push_back(uniqueVertices[tri] + 1);
			}
		}
	}

	in.close();
	
	vertices.resize(vertexCount);
	std::map<FaceVert, int, VertexLess>::iterator iter;
	for (iter = uniqueVertices.begin(); iter != uniqueVertices.end(); ++iter)
	{
		vertices[iter->second] = {
			tmpVertices[iter->first.vertex], 
			iter->first.normal != -1 ? tmpNormals[iter->first.normal] : glm::vec3(0), 
			iter->first.uv != -1 ? tmpUvs[iter->first.uv] : glm::vec2(0)
		};
	}

	std::cerr << "# v# " << vertices.size() << " f# " << indices.size() / 3 << std::endl;

	glm::vec3 min, max;
	if (!vertices.empty())
	{
		min = max = vertices[0].Position;
		for (uint32_t i = 1; i < vertices.size(); ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				min[j] = std::min(min[j], vertices[i].Position[j]);			
				max[j] = std::max(max[j], vertices[i].Position[j]);			
			}
		}
	}
	else
	{
		std::cerr << "Vertices Array size is less or equal to 0" << std::endl;
	}

	glm::vec3 size = max - min;
	glm::vec3 center = min + glm::normalize(size) * (glm::length(size) / 2);
	bounds = Bounds(center, size);

	return true;
}

