#pragma once
#include "GameObject/Components/Logic/IScript2.h"

#ifndef TURRET_H
#define	TURRET_H

class Turret : public IScript2
{
private:
// Logic Data - General
	bool _init;
	int _health;
// Logic - Behaviour
	GameObject* _target;
	size_t _targetUid;
	int _state;
	double _timerAttack;
	double _timeAttackCooldown;	
	size_t _attackRangeShoot; // currently set to 1*_mapTileSize
// Logic Data - Animation
	bool _shooting;
	int _animState, _animStatePrev; // 1==StartIdle, 2==StartShoot

public:
	void SerialiseComponent(Serialiser& document) ;
	void DeSerialiseComponent(DeSerialiser& prototypeDoc) ;
	void Inspect() ;

	Turret();
	Turret* Clone();


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
