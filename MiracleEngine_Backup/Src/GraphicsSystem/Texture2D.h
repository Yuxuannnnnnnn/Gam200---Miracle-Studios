#pragma once

#include <string>
#include <glew.h>

class Texture2D
{
private:
	unsigned int _id;
	std::string _FilePath;
	unsigned char* _LocalBuffer;
	int _Width, _Height, _BPP;
public:
	Texture2D(const std::string& path);
	~Texture2D();

	void Select(unsigned int slot = 0) const;
	void UnSelect() const;

	inline int GetWidth() const { return _Width; }
	inline int GetHeight() const { return _Height; }
};