#include "Texture.h"
#include "../stb_image.h"
#include <iostream>

Texture::Texture(const std::string& fileName) {
	int width, height, numComponents;
	stbi_set_flip_vertically_on_load(true);
	stbi_uc* imgData =  stbi_load(fileName.c_str(), &width, &height, &numComponents, 0);
	
	if (imgData == NULL) {
		std::cerr << "Texture loading failed: " << fileName << std::endl;
	}

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);

	stbi_image_free(imgData);
}

void Texture::bind() {
	glBindTexture(GL_TEXTURE_2D, m_texture);
}

Texture::~Texture() {
	glDeleteTextures(1, &m_texture);
}