#pragma once

#include "../Libs.h"
#include "Shader.h"
#include <vector>

struct ChunkCoord;

struct Vertex {
public:
	Vertex(){
		m_pos = glm::vec3();
		m_texCoord = glm::vec2();
	}

	Vertex(const glm::vec3& pos, const glm::vec2& uv) {
		this->m_pos = pos;
		this->m_texCoord = uv;
	}
	
	glm::vec3 m_pos;
	glm::vec2 m_texCoord;
};

class Mesh {
public:
	Mesh();
	Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices);
	virtual ~Mesh();

public:
	/// <summary> Binds the specified shader and draws the elements. </summary>
	void Draw(const Camera& camera, Shader& shader, const ChunkCoord& coord);

private:
	/// <summary> Generates buffers and sets vertex attrib pointers. </summary>
	void SetupMesh();
	
public:
	std::vector<Vertex> m_vertices;
	std::vector<GLuint> m_indices;
	
private:
	GLuint m_vao, m_vbo, m_ebo;
};