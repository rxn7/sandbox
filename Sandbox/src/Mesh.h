#pragma once

#include "Libs.h"

class Vertex {
public:
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord) {
		this->pos = pos;
		this->texCoord = texCoord;
	}

public:
	inline glm::vec3* getPos() { return &pos; }
	inline glm::vec2* getTexCoord() { return &texCoord; }

private:
	glm::vec3 pos;
	glm::vec2 texCoord;
};

class Mesh {
public:
	Mesh() {}
	Mesh(Vertex* vertices, unsigned int numVerts);
	virtual ~Mesh();

public:
	void draw();
	void addVertices(Vertex* vertices, unsigned int numVertes);

private:
	GLuint m_vao;

	enum {
		POSITION_VB,
		TEXCOORD_VB,
		INDEX_VB,
		NUM_BUFFERS,
	};

	GLuint m_vab[NUM_BUFFERS];
	unsigned int m_drawCount;
};

