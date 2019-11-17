#include "TextureManager.h"
#include "PrecompiledHeaders.h"

const std::map<std::string, Texture2D*>& TextureManager::GetTextureMap()
{
	return _textureMap;
}


TextureManager::TextureManager()
{

	_textureMap["player"] = new Texture2D("Resources/Image/Tex_Player.png");
	_textureMap["bullet"] = new Texture2D("Resources/Image/bullet.png");
	_textureMap["floor"] = new Texture2D("Resources/Image/Tex_Floor.png");
	_textureMap["wall"] = new Texture2D("Resources/Image/Tex_Wall.png");
	_textureMap["enemy"] = new Texture2D("Resources/Image/Tex_Enemy.png");
	_textureMap["background"] = new Texture2D("Resources/Image/background.png");

	_textureMap["zombie"] = new Texture2D("Resources/Image/zombie.png");	
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