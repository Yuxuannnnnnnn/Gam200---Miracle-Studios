#pragma once
#include <map>
#include <string>

#include "Texture2D.h"

class TextureManager
{
public:
	std::map<std::string, Texture2D*> _textureMap;
	const std::map<std::string, Texture2D*>& GetTextureMap();
	TextureManager();
	~TextureManager();

};