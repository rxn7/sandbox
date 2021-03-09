#pragma once
#include <string>
#include "../Libs.h"

class Texture {
public:
	Texture(const std::string& fileName);
	virtual ~Texture();
	
public:
	/// <summary> Binds this texture. </summary>
	void bind();

	/// <summary> Returns m_name. </summary>
	std::string getName() const { return m_name; }

private:
	std::string m_name;
	GLuint m_texture = 0;
};

