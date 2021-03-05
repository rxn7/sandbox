#pragma once

#include "../Libs.h"
#include "Uv.h"
#include "Shader.h"
#include "Transform.h"

class Vertex {
public:
	Vertex(){}

	Vertex(const glm::vec3& pos, const UV& uv) {
		this->pos = pos;
		this->texCoord = uv;
	}

public:
	inline glm::vec3* getPos() { return &pos; }
	inline UV* getTexCoord() { return &texCoord; }

private:
	glm::vec3 pos{};
	UV texCoord{};
};

class Mesh {
public:
	Mesh() {}

	Mesh(const Shader& shader, Vertex* vertices, unsigned int numVerts);
	virtual ~Mesh();

public:
	void update(Vertex* vertices, unsigned int numVerts);
	void clear();
	void draw(const Camera& camera);

	inline Shader* getShader() { return &m_shader; }
	inline Transform* getTransform() { return &m_transform; }

private:
	Shader m_shader;
	Transform m_transform;

	enum {
		POSITION_VB,
		TEXCOORD_VB,
		INDEX_VB,
		NUM_BUFFERS,
	};

	GLuint m_vao=0;
	GLuint m_vab[NUM_BUFFERS]{};
	unsigned int m_drawCount=0;
};

