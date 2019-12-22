#include "PrecompiledHeaders.h"
#include "TextureManager.h"

const std::map<std::string, Texture2D*>& TextureManager::GetTextureMap()
{
	return _textureMap;
}


TextureManager::TextureManager()
{
	//ResourceManager::GetInstance().

	if (MyResourceManager.AddNewTexture2DResource({ "player","Resources/Image/Player.png" }))
		_textureMap["player"] = MyResourceManager.GetTexture2DResource("player");

	if (MyResourceManager.AddNewTexture2DResource({ "enemy1","Resources/Image/EnemyMove.png" }))
		_textureMap["enemy1"] = MyResourceManager.GetTexture2DResource("enemy1");

	if (MyResourceManager.AddNewTexture2DResource({ "enemy2","Resources/Image/EnemyAttack.png" }))
		_textureMap["enemy2"] = MyResourceManager.GetTexture2DResource("enemy2");

	if (MyResourceManager.AddNewTexture2DResource({ "button","Resources/Image/button.png" }))
		_textureMap["button"] = MyResourceManager.GetTexture2DResource("button");

	if (MyResourceManager.AddNewTexture2DResource({ "bullet","Resources/Image/PlayerBullet.png" }))
		_textureMap["bullet"] = MyResourceManager.GetTexture2DResource("bullet");

	if (MyResourceManager.AddNewTexture2DResource({ "bulletE","Resources/Image/Bullet_E.png" }))
		_textureMap["bulletE"] = MyResourceManager.GetTexture2DResource("bulletE");

	if (MyResourceManager.AddNewTexture2DResource({ "bulletT","Resources/Image/Bullet_T.png" }))
		_textureMap["bulletT"] = MyResourceManager.GetTexture2DResource("bulletT");

	if (MyResourceManager.AddNewTexture2DResource({ "floor","Resources/Image/Floor.png" }))
		_textureMap["floor"] = MyResourceManager.GetTexture2DResource("floor");

	if (MyResourceManager.AddNewTexture2DResource({ "wall","Resources/Image/Wall.png" }))
		_textureMap["wall"] = MyResourceManager.GetTexture2DResource("wall");

	if (MyResourceManager.AddNewTexture2DResource({ "turret","Resources/Image/Turret.png" }))
		_textureMap["turret"] = MyResourceManager.GetTexture2DResource("turret");
	
	if (MyResourceManager.AddNewTexture2DResource({ "spawner","Resources/Image/Spawner.png" }))
		_textureMap["spawner"] = MyResourceManager.GetTexture2DResource("spawner");

	if (MyResourceManager.AddNewTexture2DResource({ "health","Resources/Image/Health_power_up_glow.png" }))
		_textureMap["health"] = MyResourceManager.GetTexture2DResource("health");

	if (MyResourceManager.AddNewTexture2DResource({ "rocket","Resources/Image/Rocket_icon_glow.png" }))
		_textureMap["rocket"] = MyResourceManager.GetTexture2DResource("rocket");

	if (MyResourceManager.AddNewTexture2DResource({ "zombie","Resources/Image/zombie.png" }))
		_textureMap["zombie"] = MyResourceManager.GetTexture2DResource("zombie");

	if (MyResourceManager.AddNewTexture2DResource({ "idle","Resources/Image/catidle.png" }))
		_textureMap["idle"] = MyResourceManager.GetTexture2DResource("idle");

	if (MyResourceManager.AddNewTexture2DResource({ "run","Resources/Image/catrun.png" }))
		_textureMap["run"] = MyResourceManager.GetTexture2DResource("run");

	if (MyResourceManager.AddNewTexture2DResource({ "jump","Resources/Image/catjump.png" }))
		_textureMap["jump"] = MyResourceManager.GetTexture2DResource("jump");

	if (MyResourceManager.AddNewTexture2DResource({ "coin","Resources/Image/coin.png" }))
		_textureMap["coin"] = MyResourceManager.GetTexture2DResource("coin");
}

TextureManager::~TextureManager()
{
	for (auto e : _textureMap)
	{
		delete e.second;
	}
}