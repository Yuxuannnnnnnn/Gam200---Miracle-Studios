#pragma once
#include "GameObject/Components/Logic/IScript2.h"

#ifndef ENEMY_H
#define	ENEMY_H

class Node; // forward declare

enum class Enemy_Type {
	BASIC = 1,
	RANGER = 2
};

class Enemy : public IScript2
{
private:
// Logic Data - General
	int _health;
	int _enemyType;
// Logic - Behaviour
	bool _stunned, _stunActivate;
	double _timerStun, _timerStunCooldown;
	double _timerAttack, _timerAttackCooldown;
	int _attackRangeShoot, _attackRangeMelee;
	double _moveSpeed, _chaseSpeed;
	double _chaseTimer, _chaseDuration;
// Logic - Animation
	double _timerDeath;
	bool _deathStart;
	bool _charging, _chargingStart;
	int _animState, _animStatePrev;
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
	//No Need this function
	void DeSerialiseComponent(DeSerialiser& prototypeDoc);
	virtual void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator);
	virtual void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator);
	void Inspect();
	Enemy();
	Enemy* Clone();
	void Init();
	void LoadResource();
	void Update(double dt);
// Logic - Behaviour
	void AttackRangeMelee(double dt);
	void AttackRangeShoot();
	void CheckState();
	void FSM(double dt);
	void ChancePickUps();
// Logic - Pathfinding
	Vector3 GetDestinationPos();	// _target's position
	Vector3 GetPosition();			// _parent's / self position
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
