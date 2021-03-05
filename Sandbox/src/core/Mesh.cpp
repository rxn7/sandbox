#include "Mesh.h"
#include <vector>

Mesh::Mesh(const Shader& shader, Vertex* vertices, unsigned int numVerts) {
	m_shader = shader;
	m_drawCount = numVerts;

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	std::vector<glm::vec3> positions;
	std::vector<UV> texCoords;

	positions.reserve(numVerts);
	texCoords.reserve(numVerts);

	for (size_t i = 0; i<numVerts; i++) {
		positions.push_back(*vertices[i].getPos());
		texCoords.push_back(*vertices[i].getTexCoord());
	}

	glGenBuffers(NUM_BUFFERS, m_vab);
	  
	// Positions
	glBindBuffer(GL_ARRAY_BUFFER, m_vab[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVerts*sizeof(positions[0]), &positions[0], GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Tex coords
	glBindBuffer(GL_ARRAY_BUFFER, m_vab[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVerts*sizeof(texCoords[0]), &texCoords[0], GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &m_vao);
}

void Mesh::draw(const Camera& camera) {
	m_shader.update(m_transform, camera);

	m_shader.bind();
	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, m_drawCount);
	glBindVertexArray(0);
}