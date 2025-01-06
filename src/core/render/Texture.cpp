#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

#include <iostream>
#include <filesystem>

Texture::Texture(const std::string& fileName) {
	int width, height, numComponents;
	stbi_set_flip_vertically_on_load(true);
	stbi_uc* imgData =  stbi_load(fileName.c_str(), &width, &height, &numComponents, 0);
	
	m_name = fileName.substr(fileName.find_last_of("/\\") + 1);

	if (imgData == NULL) {
		std::cerr << "Texture loading failed: " << fileName << std::endl;
	}

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);
	
	stbi_image_free(imgData);
}

Texture::~Texture() {
	glDeleteTextures(1, &m_texture);
}

void Texture::Bind() {
	glBindTexture(GL_TEXTURE_2D, m_texture);
}

std::string Texture::GetName() const {
	return m_name;
}
