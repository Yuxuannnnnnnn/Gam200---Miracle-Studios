#pragma once
#include "GameObject/Components/Logic/IScript.h"

#ifndef PLAYER_H
#define	PLAYER_H

enum class WeaponId {
	NONE = 0,
	PISTOL = 1,
	SHOTGUN = 2,
	RPG = 3,
};

class Player : public IScript
{
private:
// Logic Data - General
	bool _god;
	bool _init;
	GameObject* _camera;
	int _health, _healthMax;
	int _progress, _progressMax;
// Logic Data - Weapons
	int _weaponActive;
	int _ammoRpg;
	int _ammoTurret;
	int _ammoWall;
	double _timerShoot;
	double _timerDeploy;
	double _fireratePistol;		// 1.0d == 1sec
	double _firerateShotgun;	// 1sec = d * roundPerSec
	double _firerateRPG;		// d = 1/rps
	double _firerateTurret;
	double _firerateWall;
// Logic Data - Progression
	double _timerProg, _timerProgCooldown;
public:
	void SerialiseComponent(Serialiser& document) ;
	void DeSerialiseComponent(DeSerialiser& prototypeDoc) ;
	void Inspect() ;

	Player();

	void Init();
	void Update(double dt);

	void WeaponSwitch();
	void WeaponShoot();
	void WeaponShoot_Pistol();
	void WeaponShoot_Shotgun();
	void WeaponShoot_RPG();
	void UpdateCamera();
	void UpdateInput();
	void UpdateUI();

	int GetHealth();
	void SetHealth(int val);
	int GetHealthMax();
	int GetProgress();
	void SetProgress(int val);
	int GetProgressMax();
	void ProgressIncement(int in = 1);

	void OnTrigger2DEnter(Collider2D* other);
};

#endif
