#include "PrecompiledHeaders.h"
#include "TextureManager.h"
#include "../Tools/MemoryManager/ResourceManager.h"

const std::map<std::string, Texture2D*>& TextureManager::GetTextureMap()
{
	return _textureMap;
}


TextureManager::TextureManager()
{
	//ResourceManager::GetInstance().

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
	

	_textureMap["startscreen"] = new Texture2D("Resources/Image/StartScreen.png");	
	_textureMap["idle"] = new Texture2D("Resources/Image/catidle.png");
	_textureMap["run"] = new Texture2D("Resources/Image/catrun.png");
	_textureMap["jump"] = new Texture2D("Resources/Image/catjump.png");
	_textureMap["coin"] = new Texture2D("Resources/Image/coin.png");

	_textureMap["HP_Bar"] = new Texture2D("Resources/Image/HP_Bar.png");
	_textureMap["Progress_Bar"] = new Texture2D("Resources/Image/Progress_Bar.png");
	_textureMap["UI_Background"] = new Texture2D("Resources/Image/UI_Background.png");

	// props
	_textureMap["CircularBatteryPlatform"] = new Texture2D("Resources/Image/CircularBatteryPlatform.png");

	_textureMap["Building1"] = new Texture2D("Resources/Image/Building1.png");
	_textureMap["Building2"] = new Texture2D("Resources/Image/Building2.png");
	_textureMap["Building3"] = new Texture2D("Resources/Image/Building3.png");
	_textureMap["Building4"] = new Texture2D("Resources/Image/Building4.png");
	_textureMap["Crate"] = new Texture2D("Resources/Image/Crate.png");
}

TextureManager::~TextureManager()
{
	for (auto e : _textureMap)
	{
		delete e.second;
	}
}