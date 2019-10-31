#include "TextureManager.h"
#include "PrecompiledHeaders.h"

const std::map<std::string, Texture2D*>& TextureManager::GetTextureMap()
{
	return _textureMap;
}


TextureManager::TextureManager()
{
	_textureMap["zombie"] = new Texture2D("Resources/Image/zombie.png");
	_textureMap["background"] = new Texture2D("Resources/Image/background.png");
	_textureMap["idle"] = new Texture2D("Resources/Image/catidle.png");
	_textureMap["run"] = new Texture2D("Resources/Image/catrun.png");
	_textureMap["jump"] = new Texture2D("Resources/Image/catjump.png");
}

TextureManager::~TextureManager()
{
	for (auto e : _textureMap)
	{
		delete e.second;
	}
}