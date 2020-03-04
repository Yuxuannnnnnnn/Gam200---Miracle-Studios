#pragma once
#include "GameObject/Components/Logic/IScript2.h"

#ifndef BOSS_H
#define	BOSS_H

/*
	check what values needed for serialisation
		DONT do serialisation, wait for YX to fin, then follow the standard
	check animations & sounds, need follow animation methods in Enemy.h.cpp
	check if need ParentChild.

private:

// vals that need serialisation
	int health, healthMax, healthHalf, healthQuart; // Half&Quart dont need serial
	double bulletROF, laserCharge, laserShootDuration;
	double attackDuration, attack related timings;
	float rotation speed;
// non-serail vals
	bool _init;
	int rand;
	GameObject* Player;

public:
	

	void Init()
	{
		// find player
		// set the max, half, quart HP vals
		_init = true;
	}
	void UPDATE()
	{
		if (_init)
			Init();

		if(Health is less than 50%)
			HalfAtk();
		else if(Health is less than 25%)
			QuartAtk();
		else
		{
			// default shooting
			// spin and shoot
		}
	}


	LookAtPlayer()
	SpinAround()
	ShootBullet() // should just be shoot in direction Boss is facing
	ShootLaser() // will need multiple phases within ShootLaser
		// look at player whie charging
		// once charged flash the line of laser, then shoot laser
		// double chargeTime, flashTime, 
	RandNormalAtk() {
		// call random function to see which Attack to use
	}
	FirstAttack() {
		for(int i = 0; i < 25; i++)
			ShootBullet();
	}
	SecondAttack() {
		SpinAround()
		for(int i = 0; i < 25; i++)
			ShootBullet();
	}
	void FirstSpecialAttack() {				// whats this?
		check number of attacks made;
		if(number of attacks exceed 4)
			use special attack;
	}
	HalfAtk() { ShootLaser() }
	QuartAtk() { FirstSpecialAttack () }



*/


//enum class BossStates {
//	DEAD = 0,
//
//};
//
//class Boss : public IScript2
//{
//private:
//// Logic Data - General
//	bool _init;
//	int _health, _healthMax, _healthRage;
//	double _timerAttackNormal, _frequencyAttackNormal;
//	double _timerAttackRage, _frequencyAttackRage;
//// Logic - Behaviour
//	GameObject* _target;
//	int _state;
//
//public:
//	void SerialiseComponent(Serialiser& document)
//	{
//
//	}
//	void DeSerialiseComponent(DeSerialiser& prototypeDoc)
//	{
//
//	}
//	void Inspect()
//	{
//
//	}
//	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
//	{
//	}
//
//	Boss();
//	Boss* Clone();
//	void Init();
//	void Update(double dt);
//
//	Vector3& GetDestinationPos();	// gets _target's position
//	Vector3& GetPosition();	// gets _parent's position
//
//	void FSM();	
//
//	void OnCollision2DTrigger(Collider2D* other);
//};

#endif
