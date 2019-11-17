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
		_textureMap["zombie"] = new Texture2D("Image/zombie.png");
		_textureMap["background"] = new Texture2D("Image/background.png");
		_textureMap["idle"] = new Texture2D("Image/catidle.png");
		_textureMap["run"] = new Texture2D("Image/catrun.png");
		_textureMap["jump"] = new Texture2D("Image/catjump.png");
	}
};