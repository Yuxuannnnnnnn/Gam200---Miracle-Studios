#pragma once

#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <string>
#include <glew.h>

class Texture2D
{
private:
	unsigned int _id;
	std::string _filePath;
	unsigned char* _localBuffer;
	int _width, _height, _bpp;
public:
	Texture2D(const std::string& path);
	~Texture2D();

	void Select(unsigned int slot = 0) const;
	void UnSelect() const;

	int GetWidth() const;
	int GetHeight() const;
};

#endif

