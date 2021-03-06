#pragma once

#include <string>
#include "../Libs.h"
#include "../Transform.h"
#include "Camera.h"

class Shader {
public:
	Shader() {}
	Shader(const std::string& fileName);
	virtual ~Shader();

public:
	void bind();
	void update(const Transform& transform, const Camera& camera);

private:
	static const unsigned int NUM_SHADERS = 2;

	enum {
		TRANSFORM_U,
		NUM_UNIFORMS
	};

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];
};