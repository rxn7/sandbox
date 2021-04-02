#pragma once

#include <string>
#include "../Libs.h"
#include "Camera.h"
#include "../ChunkCoord.h"

class Shader {
public:
	Shader();
	Shader(const std::string& fileName);
	virtual ~Shader();

public:
	/// <summary> Binds this shader. </summary>
	void bind();

	/// <summary> Updates the transform uniform in shader. </summary>
	void update(const ChunkCoord& coord, const Camera& camera);

private:
	static const unsigned int NUM_SHADERS = 2;

	enum {
		VIEW_U,
		PROJ_U,
		COORD_X,
		COORD_Z,
		NUM_UNIFORMS
	};

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];
};