#include "TextureManager.h"
#include "PrecompiledHeaders.h"

const std::map<std::string, Texture2D*>& TextureManager::GetTextureMap()
{
	return _textureMap;
}


TextureManager::TextureManager()
{

	_textureMap["player"] = new Texture2D("Resources/Image/Player.png");
	_textureMap["enemy1"] = new Texture2D("Resources/Image/EnemyMove.png");
	_textureMap["enemy2"] = new Texture2D("Resources/Image/EnemyAttack.png");
	
	_textureMap["bullet"] = new Texture2D("Resources/Image/PlayerBullet.png");
	_textureMap["floor"] = new Texture2D("Resources/Image/Floor.png");
	_textureMap["wall"] = new Texture2D("Resources/Image/Wall.png");
	_textureMap["turret"] = new Texture2D("Resources/Image/Enemy.png");

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