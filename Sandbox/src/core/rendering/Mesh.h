#pragma once

#include "../Libs.h"
#include "Shader.h"
#include "../Transform.h"
#include <vector>

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
	Mesh() {
		m_vao = 0;
		m_vbo = 0;
		m_ebo = 0;
	}

	Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices);
	virtual ~Mesh();

public:
	void draw(const Camera& camera, Shader& shader);

	inline Transform* getTransform() { return &m_transform; }

private:
	void setupMesh();
	
public:
	std::vector<Vertex> m_vertices;
	std::vector<GLuint> m_indices;
	
private:
	Transform m_transform;

	GLuint m_vao, m_vbo, m_ebo;
};