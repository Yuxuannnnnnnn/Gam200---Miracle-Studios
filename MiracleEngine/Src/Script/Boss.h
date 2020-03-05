#pragma once
#include "GameObject/Components/Logic/IScript2.h"

#ifndef BOSS_H
#define	BOSS_H

enum class Boss_State {
	IDLE = 0,
	IDLE_END,
	DEATH,
	SPIN_SHOOTBULLET,
	CHARGING_LASER,
	FIRING_LASER,
	RAPID_CHARGING_LASER,
	RAPID_FIRING_LASER,
};

class Boss : public IScript2
{
private:
	int health, healthMax, healthHalf, healthQuart; // Half&Quart dont need serial
	double idleTimer, idleDuration; // after every attack, rest for this long

	int ammo, ammoMax;
	double bulletTimer, bulletROF; // shoot bullet related stuff
	float rotationspeed;

	double laserChargeTimer, laserChargeDuration; // laser charge
	double laserFlashTimer, laserFlashDuration; // laser short flash
	double laserAliveTimer, laserAliveDuration; // laser lifetime, the actual laser that does dmg

	int laserRapidFireAmount; // how many shots
	double laserRelatedDurationSpeedUp; // multiplier to the durations above, 2 will make laser shoot 2x faster, 3 gives 3x, etc

// non-serail vals
	bool _init, _deathStart;
	Boss_State _state, _statePrev;
	int playerId;
	GameObject* playerPtr;
	double _dt;

public:
	Boss();
	Boss* Clone();
	void Init();
	void Update(double dt);
// Logic - Behaviour
	void UpdateState();
	void RunState();

	void Idle();
	void Death();
	void SpinAround();
	void ShootBullet();
	void LookAtPlayer();
	void LaserCharge();
	void LaserShoot();
		// will need multiple phases within LaserShoot
		// look at player whie charging
		// once charged flash the line of laser, then shoot laser
		// double chargeTime, flashTime, 
	void SpinShoot() {
		// rotate clockwise
		//shoot enemy
		for (int i = 0; i < 25; i++)
			ShootBullet();
	}
	void SecondAttack() {
		SpinAround();
			for (int i = 0; i < 25; i++)
				ShootBullet();
	}
	void FirstSpecialAttack() {
		// rapid fire laser
	}
	void HalfAtk() { LaserShoot(); }
	void QuartAtk() { FirstSpecialAttack(); }


	void OnCollision2DTrigger(Collider2D* other)
	{}


	void SerialiseComponent(Serialiser& document)
	{
	}
	void DeSerialiseComponent(DeSerialiser& prototypeDoc)
	{
	}
	virtual void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
	{
	}

	virtual void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
	{
	}
	void Inspect()
	{
	}
};
#endif
