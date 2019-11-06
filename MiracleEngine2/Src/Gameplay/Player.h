#pragma once
#include "GameObjectComponents/LogicComponents/IScript.h"

enum class WeaponId {
	NONE = 0,
	PISTOL = 1,
	SHOTGUN = 2,
	RPG = 3,
};

class Player : public IScript
{
private:
	bool _init;
	int _health;
	int _weaponActive;
	double _timer;
	double _timerCooldown;
	GameObject* _camera;
public:
	Player();

	void Init();
	void Update(double dt);

	void WeaponSwitch();
	void WeaponShoot();
	void WeaponShoot_Pistol();
	void WeaponShoot_Shotgun();
	void WeaponShoot_RPG();
	void UpdateCamera();
	void updateInput();
	int GetHealth();
	void SetHealth(int val);
};