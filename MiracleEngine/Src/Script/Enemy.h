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
	bool _init;
	int _health;
	int _enemyType;
// Logic - Behaviour
	bool _stunned;
	double _timerStun, _timerStunCooldown;
	double _timerAttack, _timerAttackCooldown;
	int _attackRangeShoot, _attackRangeMelee;
	double _moveSpeed, _chaseSpeed;
	double _chaseTimer, _chaseDuration;
// Logic - Animation
	Vector3 defaultScale{ 500, 500, 1 };
	Vector3 idleScale{ 350, 350, 1 };
	double _timerDeath;
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
	void SerialiseComponent(Serialiser& document)
	{
		if (document.HasMember("Health") && document["Health"].IsInt())
		{
			_health = (document["Health"].GetInt());
		}
		if (document.HasMember("EnemyType") && document["EnemyType"].IsInt())
		{
			_enemyType = (document["EnemyType"].GetInt());
		}
		if (document.HasMember("StunDuration") && document["StunDuration"].IsDouble())
		{
			_timerStunCooldown = (document["StunDuration"].GetDouble());
		}
		if (document.HasMember("MoveSpeed") && document["MoveSpeed"].IsDouble())
		{
			_moveSpeed = (document["MoveSpeed"].GetDouble());
		}
		if (document.HasMember("ChaseSpeed") && document["ChaseSpeed"].IsDouble())
		{
			_chaseSpeed = (document["ChaseSpeed"].GetDouble());
		}
		if (document.HasMember("ChaseDuration") && document["ChaseDuration"].IsDouble())
		{
			_chaseDuration = (document["ChaseDuration"].GetDouble());
		}
		if (document.HasMember("AttackRangeShoot") && document["AttackRangeShoot"].IsDouble())
		{
			_attackRangeShoot = document["AttackRangeShoot"].GetDouble();
			_attackRangeShoot *= 100;
			_attackRangeShoot *= _attackRangeShoot;
		}
		if (document.HasMember("AttackRangeMelee") && document["AttackRangeMelee"].IsDouble())
		{
			_attackRangeMelee = document["AttackRangeMelee"].GetDouble();
			_attackRangeMelee *= 100;
			_attackRangeMelee *= _attackRangeMelee;
		}
	}
	void DeSerialiseComponent(DeSerialiser& prototypeDoc){}
	void Inspect()
	{
		// health, type, stunDur, moveSpd, chaseSpd, atkRange, AtkMelee
		ImGui::Spacing();
		ImGui::InputInt("Health ", &_health);
		ImGui::Spacing();
		ImGui::InputInt("Enemy Type ", &_enemyType);
		ImGui::Spacing();
		ImGui::InputDouble("Stun Duration ", &_timerStunCooldown);
		ImGui::Spacing();
		ImGui::InputDouble("Move Speed ", &_moveSpeed);
		ImGui::Spacing();
		ImGui::InputDouble("Chase Speed ", &_chaseSpeed);
		ImGui::Spacing();
		ImGui::InputInt("Shoot Attack Range ", &_attackRangeShoot);
		ImGui::Spacing();
		ImGui::InputInt("Melee Attack Range ", &_attackRangeMelee);
		ImGui::Spacing();

	}

	Enemy();
	Enemy* Clone();
	void Init();
	void Update(double dt);
// Logic - Behaviour
	void AttackRangeMelee();
	void AttackRangeShoot();
	void CheckState();
	void FSM();
	void ChancePickUps();
// Logic Data - Animation
	bool _enemy1charging;
	int _animState, _animStatePrev;

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
