#pragma once

#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <string>
#include <glew.h>

class Texture2D
{
private:
	unsigned int _id;
	int _width;   // width and height of texture
	int _height;
	int _bpp;  // bit per pixel
public:
	unsigned int GetTextureID() const;

	Texture2D();
	~Texture2D();

	void Select(unsigned int slot = 0) const;
	void UnSelect() const;

	int GetWidth() const;
	int GetHeight() const;

	bool load(std::string path);
	void unload();
};

#endif

