#pragma once
#include "GameObject/Components/Logic/IScript.h"

#ifndef BOSS_H
#define	BOSS_H

class Node; // forward declare

enum class Boss_State {
	NONE = 0,
	IDLE,
	IDLE_END,
	DEATH,

	SPIN_SHOOTBULLET,
	LASER_CHARGE,
	LASER_CHARGE_RAPID,
	LASER_SHOOT,
};

class Boss : public IScript												// NOTE NOTE NOTE NOTE -- THIS ISNT DONE AT ALL, WILL SETTLE THIS AFTER I DO THE LOGIC CHANGES :BRANDON
{
private:
// Logic Data - General
	int health, healthMax, healthHalf, healthQuart;
	double idleTimer, idleDuration;

	int ammo, ammoMax;
	double bulletTimer, shootROF, bulletSpeed;
	float rotationspeed;

	double laserChargeTimer, laserChargeDuration,
		laserFlashTimer, laserFlashDuration,
		laserAliveTimer, laserAliveDuration;
	int laserRapidFireNumOfShots, rapidFireShotCount;
	double laserRapidChargeSpeedUp;

	bool 	_laserChargeStart, _laserFlashStart, _laserShootStart;
	bool _init, _deathStart;
	Boss_State _state, _statePrev;

	GameObject* playerPtr, *subObj;
	int playerId;
	double _dt;

public:
	Boss();
	~Boss();
	Boss* Clone();

	void Init();
	void Update(double dt);

	void UpdateState();
	void RunState();

	void Idle();
	void Death();
	void SpinAround();
	void ShootBullet();
	void LookAtPlayer();
	void LaserCharge(double speedUp = 1.0);
	void LaserShoot();

	void OnCollision2DTrigger(Collider2D* other);

	void SerialiseComponent(Serialiser& document);
	void DeSerialiseComponent(DeSerialiser& prototypeDoc);
	void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator);
	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator);
	void Inspect();
};

#endif
