#pragma once
#include "GameObjectComponents/LogicComponents/IScript.h"

#ifndef ENEMYTHREE_H
#define	ENEMYTHREE_H

class Node; // forward declare

class EnemyThree : public IScript
{
private:
// Logic Data - General
	bool _init;
	int _health;
	bool _stunned;
	bool _charging;
// Logic - Behaviour
	double _timerAttack;
	double _timerStun;
	double _timerAttackCooldown;
	double _timerStunCooldown;
	size_t _attackRange; // manually set in ctor
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
	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;
	void Inspect() override;

	EnemyThree();

	void Init();
	void Update(double dt);
// Logic - Behaviour
	void AttackMelee();
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

	void OnCollision2DTrigger(ICollider2D* other);
};
#endif
