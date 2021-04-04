#include "Mesh.h"
#include <vector>
#include "../Libs.h"
#include "../../Definitions.h"

Mesh::Mesh() {
	m_vao = 0;
	m_vbo = 0;
	m_ebo = 0;
}

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices) {
	m_vertices = vertices;
	m_indices = indices;
	SetupMesh();
}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &m_vao);
	
	/* Delete the buffers, otherwise memory leak will occur. */
	glDeleteBuffers(1, &m_ebo);
	glDeleteBuffers(1, &m_vbo);
}

void Mesh::Draw(const Camera& camera, Shader& shader, const ChunkCoord& coord) {
	shader.Bind();
	shader.Update(coord, camera);

	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::SetupMesh() {
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ebo);

	glBindVertexArray(m_vao);
	
	// Vertices
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);

	// Indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLuint), &m_indices[0], GL_STATIC_DRAW);

	// Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	
	// Texture coords
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_texCoord));

	glBindVertexArray(0);
}