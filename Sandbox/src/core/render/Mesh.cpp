#include "Mesh.h"
#include <vector>
#include "../Libs.h"

Mesh::Mesh() {
	m_vao = 0;
	m_vbo = 0;
	m_ebo = 0;
}

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices) {
	m_vertices = vertices;
	m_indices = indices;

	setupMesh();
}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &m_vao);
	glDeleteVertexArrays(1, &m_vbo);
	glDeleteVertexArrays(1, &m_ebo);
}

void Mesh::draw(const Camera& camera, Shader& shader) {
	if (glm::distance(camera.getPosition(), m_transform.getPos()) > 100) {
		return;
	}

	shader.update(m_transform, camera);
	shader.bind();

	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::setupMesh() {
	glGenBuffers(1, &m_vao);
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