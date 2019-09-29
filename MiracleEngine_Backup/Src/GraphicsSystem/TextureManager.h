#pragma once
#include <map>
#include <string>
#include "Texture2D.h"

class TextureManager
{
public:
	TextureManager()
	{
		_textureMap["zombie"] = new Texture2D("zombie.png");
		_textureMap["background"] = new Texture2D("background.png");
	}
	std::map<std::string, Texture2D*> _textureMap;
};