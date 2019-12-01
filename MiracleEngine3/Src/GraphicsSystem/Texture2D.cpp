#include "Texture2D.h"
#include "PrecompiledHeaders.h"
#include "Tools/MemoryManager/ResourceManager.h"
#include "../stb_image/stb_image.h"

int Texture2D::GetWidth() const { return _width; }
int Texture2D::GetHeight() const { return _height; }

Texture2D::Texture2D(const std::string& path)
	: _id(0), _filePath(path), _localBuffer(nullptr),
	_width(0), _height(0), _bpp(0)
{
	_localBuffer = ResourceManager::GetInstance().GetTexture2DResource(path, _width, _height, _bpp);

	glEnable(GL_BLEND);
	
	glGenTextures(1, &_id);
	glBindTexture(GL_TEXTURE_2D, _id);


	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _localBuffer);
	glBindTexture(GL_TEXTURE_2D, 0);

}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &_id);
}

void Texture2D::Select(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, _id);
}

void Texture2D::UnSelect() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}


unsigned int Texture2D::GetTextureID() const
{
	return _id;
}