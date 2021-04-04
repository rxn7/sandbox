#pragma once

#include <string>
#include "../Libs.h"

class Texture {
public:
	Texture(const std::string& fileName);
	virtual ~Texture();
	
public:
	/// <summary> Binds this texture. </summary>
	void Bind();

	/// <summary> Returns the name of the texture. </summary>
	std::string GetName() const;

private:
	std::string m_name;
	GLuint m_texture = 0;
};

