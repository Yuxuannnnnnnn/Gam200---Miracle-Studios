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
	
	
	_textureMap["button"] = new Texture2D("Resources/Image/button.png");
	_textureMap["bullet"] = new Texture2D("Resources/Image/PlayerBullet.png");
	_textureMap["bulletE"] = new Texture2D("Resources/Image/Bullet_E.png");
	_textureMap["bulletT"] = new Texture2D("Resources/Image/Bullet_T.png");
	_textureMap["floor"] = new Texture2D("Resources/Image/Floor.png");
	_textureMap["wall"] = new Texture2D("Resources/Image/Wall.png");
	_textureMap["turret"] = new Texture2D("Resources/Image/Turret.png");
	_textureMap["spawner"] = new Texture2D("Resources/Image/Spawner.png");
	_textureMap["health"] = new Texture2D("Resources/Image/Health_power_up_glow.png");
	_textureMap["rocket"] = new Texture2D("Resources/Image/Rocket_icon_glow.png");
	

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