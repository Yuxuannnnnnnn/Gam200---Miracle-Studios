#pragma once
#include <map>
#include <string>

#include "Texture2D.h"

class TextureManager
{
public:
	std::map<std::string, Texture2D*> _textureMap;

	TextureManager()
	{
		_textureMap["zombie"] = new Texture2D("zombie.png");
		_textureMap["background"] = new Texture2D("background.png");
	}
};