#pragma once
#include "Interfaces/IScript.h"

#ifndef TURRET_H
#define	TURRET_H

class Turret : public IScript
{
private:
// Logic Data - General
	bool _init;
	int _health;
// Logic - Behaviour
	GameObject* _target;
	int _state;
	double _timerAttack;
	double _timeAttackCooldown;	
	size_t _attackRange; // currently set to 1*_mapTileSize

public:
	void SerialiseComponent(Serialiser& document) override;
	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;
	void Inspect() override;

	Turret();

	void Init();
	void Update(double dt);

	Vector3& GetDestinationPos();	// gets _target's position
	Vector3& GetPosition();	// gets _parent's position

// Attack Logic
	void SearchTarget();
	void ShootTarget();
	void RotateToTarget();

	void FSM();
};

#endif
