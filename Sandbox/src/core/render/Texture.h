#pragma once
#include <string>
#include "../Libs.h"

class Texture {
public:
	Texture(const std::string& fileName);
	virtual ~Texture();
	
public:
	void bind();
	std::string getName() const { return m_name; }

private:
	std::string m_name;
	GLuint m_texture = 0;
};

