#pragma once
#include "GameObject/Components/Logic/IScript2.h"

#ifndef ENEMY_H
#define	ENEMY_H

class Node; // forward declare

enum class Enemy_Type {
	BASIC = 0,
	RANGER = 1
};

class Enemy : public IScript2
{
private:
// Logic Data - General
	bool _init;
	int _health;
	int _enemyType;
// Logic - Behaviour
	bool _stunned;
	double _timerStun;
	double _timerStunCooldown;
	double _timerAttack;
	double _timerAttackCooldown;
	size_t _attackRange; // manually set in ctor
	size_t _attackMelee; // manually set in ctor
// Logic - Pathfinding
	GameObject* _target;
	int _state;	
	double _timerPathing;
	double _timerPathingCooldown;
	std::vector<Node*> _path;
	Node* _nextNode;
	Node* _destNode;
	size_t _mapTileSize;

public:
	void SerialiseComponent(Serialiser& document);
	void DeSerialiseComponent(DeSerialiser& prototypeDoc) ;
	void Inspect() ;

	Enemy();

	void Init();
	void Update(double dt);
// Logic - Behaviour
	void AttackMelee();
	void AttackRange();
	void CheckState();
	void FSM();
	void ChancePickUps();
// Logic - Pathfinding
	Vector3& GetDestinationPos();	// _target's position
	Vector3& GetPosition();			// _parent's / self position
	std::vector<Node*>& GetPath();
	void Move();
	void MoveNode(bool start = false); // Move using path (toward _destination)

	int GetHealth();
	void SetHealth(int val);
	void DecrementHealth();
	void SetStunned();

	void OnCollision2DTrigger(Collider2D* other);
};
#endif
