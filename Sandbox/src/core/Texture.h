#pragma once
#include <string>
#include "Libs.h"

class Texture {
public:
	Texture(const std::string& fileName);
	virtual ~Texture();
	
public:
	void bind(unsigned int unit);

private:
	GLuint m_texture = 0;
};

