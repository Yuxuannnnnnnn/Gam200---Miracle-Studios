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
	int _health;
	int _weaponActive;
	double _timer;
	double _timerCooldown;
public:
	Player();

	void Update(double dt);

	void WeaponSwitch();
	void WeaponShoot();
	void WeaponShoot_Pistol();
	void WeaponShoot_Shotgun();
	void WeaponShoot_RPG();

	void updateInput();
	int GetHealth();
	void SetHealth(int val);
};