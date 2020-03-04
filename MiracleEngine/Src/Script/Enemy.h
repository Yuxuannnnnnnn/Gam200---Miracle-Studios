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
			_attackRangeShoot = (int)document["AttackRangeShoot"].GetDouble();
			_attackRangeShoot *= 100;
			_attackRangeShoot *= _attackRangeShoot;
		}
		if (document.HasMember("AttackRangeMelee") && document["AttackRangeMelee"].IsDouble())
		{
			_attackRangeMelee = (int)document["AttackRangeMelee"].GetDouble();
			_attackRangeMelee *= 100;
			_attackRangeMelee *= _attackRangeMelee;
		}
	}
	//No Need this function
	void DeSerialiseComponent(DeSerialiser& prototypeDoc)
	{
	}

	virtual void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
	{
		rapidjson::Value value;

		value.SetString(rapidjson::StringRef(ToScriptName(_type)));
		prototypeDoc.AddMember("Script2Id", value, allocator);

		value.SetInt(_health);
		prototypeDoc.AddMember("Health", value, allocator);

		value.SetInt(_enemyType);
		prototypeDoc.AddMember("EnemyType", value, allocator);

		value.SetDouble(_timerStunCooldown);
		prototypeDoc.AddMember("StunDuration", value, allocator);		
		
		value.SetDouble(_moveSpeed);
		prototypeDoc.AddMember("MoveSpeed", value, allocator);		
		
		value.SetDouble(_chaseSpeed);
		prototypeDoc.AddMember("ChaseSpeed", value, allocator);		
		
		value.SetDouble(_chaseDuration);
		prototypeDoc.AddMember("ChaseDuration", value, allocator);			
		

		double attackRangeShoot = sqrt(_attackRangeShoot) / 100.0;
		value.SetDouble(attackRangeShoot);
		prototypeDoc.AddMember("AttackRangeShoot", value, allocator);		
		
		double attackRangeMelee = sqrt(_attackRangeMelee) / 100.0;
		value.SetDouble(attackRangeMelee);
		prototypeDoc.AddMember("AttackRangeMelee", value, allocator);

	}

	virtual void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
	{
		LogicComponent* protoLogicCom = dynamic_cast<LogicComponent*>(protoCom);

		size_t UId = protoLogicCom->GetScriptContianer()[_type];

		Enemy* script = (Enemy*)(MyLogicSystem.getScriptPtr(UId));

		if (!script)
		{
			DeSerialiseComponent(value, allocator);
			return;
		}

		rapidjson::Value Health;
		rapidjson::Value EnemyType;
		rapidjson::Value StunDuration;
		rapidjson::Value MoveSpeed;
		rapidjson::Value ChaseSpeed;
		rapidjson::Value ChaseDuration;
		rapidjson::Value AttackRangeShoot;
		rapidjson::Value AttackRangeMelee;

		bool addComponentIntoSceneFile = false;


		if (script->_health != _health)
		{
			addComponentIntoSceneFile = true;
			Health.SetInt(_health);
		}

		if (script->_enemyType != _enemyType)
		{
			addComponentIntoSceneFile = true;
			EnemyType.SetInt(_enemyType);
		}

		if (script->_timerStunCooldown != _timerStunCooldown)
		{
			addComponentIntoSceneFile = true;
			StunDuration.SetDouble(_timerStunCooldown);
		}

		if (script->_moveSpeed != _moveSpeed)
		{
			addComponentIntoSceneFile = true;
			MoveSpeed.SetDouble(_moveSpeed);
		}

		if (script->_chaseSpeed != _chaseSpeed)
		{
			addComponentIntoSceneFile = true;
			ChaseSpeed.SetDouble(_chaseSpeed);
		}

		if (script->_chaseDuration != _chaseDuration)
		{
			addComponentIntoSceneFile = true;
			ChaseDuration.SetDouble(_chaseDuration);
		}

		if (script->_attackRangeShoot != _attackRangeShoot)
		{
			addComponentIntoSceneFile = true;

			double attackRangeShoot = sqrt(_attackRangeShoot) / 100.0;
			AttackRangeShoot.SetDouble(attackRangeShoot);
		}

		if (script->_attackRangeMelee != _attackRangeMelee)
		{
			addComponentIntoSceneFile = true;

			double attackRangeMelee = sqrt(_attackRangeMelee) / 100.0;
			AttackRangeMelee.SetDouble(attackRangeMelee);
		}

		if (addComponentIntoSceneFile)	//If anyone of component data of obj is different from Prototype
		{
			rapidjson::Value scriptName;

			scriptName.SetString(rapidjson::StringRef(ToScriptName(_type)));
			value.AddMember("Script2Id", scriptName, allocator);

			if (!Health.IsNull())	//if rapidjson::value container is not empty
			{
				value.AddMember("Health", Health, allocator);
			}

			if (!EnemyType.IsNull())	//if rapidjson::value container is not empty
			{
				value.AddMember("EnemyType", EnemyType, allocator);
			}

			if (!StunDuration.IsNull())	//if rapidjson::value container is not empty
			{
				value.AddMember("StunDuration", StunDuration, allocator);
			}


			if (!MoveSpeed.IsNull())	//if rapidjson::value container is not empty
			{
				value.AddMember("MoveSpeed", MoveSpeed, allocator);
			}


			if (!ChaseSpeed.IsNull())	//if rapidjson::value container is not empty
			{
				value.AddMember("ChaseSpeed", ChaseSpeed, allocator);
			}


			if (!ChaseDuration.IsNull())	//if rapidjson::value container is not empty
			{
				value.AddMember("ChaseDuration", ChaseDuration, allocator);
			}


			if (!AttackRangeShoot.IsNull())	//if rapidjson::value container is not empty
			{
				value.AddMember("AttackRangeShoot", AttackRangeShoot, allocator);
			}			
			
			if (!AttackRangeMelee.IsNull())	//if rapidjson::value container is not empty
			{
				value.AddMember("AttackRangeMelee", AttackRangeMelee, allocator);
			}
		}
	}



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
