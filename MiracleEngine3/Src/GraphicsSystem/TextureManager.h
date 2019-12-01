#pragma once

#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <map>
#include <string>

#include "Texture2D.h"

class TextureManager
{
public:
	std::map<std::string, Texture2D*> _textureMap;
	std::map<std::string, Texture2D*> _animationMap;
	const std::map<std::string, Texture2D*>& GetTextureMap();
	TextureManager();
	~TextureManager();

};

#endif

