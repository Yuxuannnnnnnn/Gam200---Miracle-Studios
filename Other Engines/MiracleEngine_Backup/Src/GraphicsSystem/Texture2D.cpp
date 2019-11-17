#include "Texture2D.h"

#include "../stb_image/stb_image.h"

Texture2D::Texture2D(const std::string& path)
	: _id(0), _FilePath(path), _LocalBuffer(nullptr),
	_Width(0), _Height(0), _BPP(0)
{
	stbi_set_flip_vertically_on_load(1);
	_LocalBuffer = stbi_load(path.c_str(), &_Width, &_Height, &_BPP, 4);

	glGenTextures(1, &_id);
	glBindTexture(GL_TEXTURE_2D, _id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _Width, _Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _LocalBuffer);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (_LocalBuffer)
		stbi_image_free(_LocalBuffer);
}

Texture2D::~Texture2D()
{
	(glDeleteTextures(1, &_id));
}

void Texture2D::Select(unsigned int slot) const
{
	(glActiveTexture(GL_TEXTURE0 + slot));
	(glBindTexture(GL_TEXTURE_2D, _id));
}

void Texture2D::UnSelect() const
{
	(glBindTexture(GL_TEXTURE_2D, 0));
}
