#pragma once
#include "GameObject/Components/Logic/IScript.h"

#ifndef BOSS_H
#define	BOSS_H

class Node; // forward declare

class Boss : public IScript												// NOTE NOTE NOTE NOTE -- THIS ISNT DONE AT ALL, WILL SETTLE THIS AFTER I DO THE LOGIC CHANGES :BRANDON
{
private:
// Logic Data - General
	bool _init;
	int _health;
	int _healthRage;
// Logic - Behaviour
	double _timerAttack;
	double _timerAttackCooldown;
	double _timerAttackRageCooldown;
// Logic - Pathfinding
	GameObject* _target;
	int _state;

public:

	void SerialiseComponent(Serialiser& document) ;
	void DeSerialiseComponent(DeSerialiser& prototypeDoc) ;
	void Inspect() ;

	Boss();

	void Init();
	void Update(double dt);

	Vector3& GetDestinationPos();	// gets _target's position
	Vector3& GetPosition();	// gets _parent's position

	void Shoot();
	void Attack();
	void ChancePickUps();

	void FSM();	

	void OnCollision2DTrigger(Collider2D* other);
};

#endif
