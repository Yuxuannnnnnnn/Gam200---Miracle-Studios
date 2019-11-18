#pragma once
#include "GameObjectComponents/LogicComponents/IScript.h"

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

	int _enemyType;
	int _health;

	void SerialiseComponent(Serialiser& document) 
	{
		if (document.HasMember("Health") && document["Health"].IsInt())	//Checks if the variable exists in .Json file
		{
			_health = (document["Health"].GetInt());
		}

		if (document.HasMember("EnemyType") && document["EnemyType"].IsInt())	//Checks if the variable exists in .Json file
		{
			_enemyType = (document["EnemyType"].GetInt());
		}
	}


	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override
	{
		rapidjson::Value value;

		value.SetInt(_health);
		prototypeDoc.AddMember("Health", value);
		value.Clear();

		value.SetInt(_enemyType);
		prototypeDoc.AddMember("EnemyType", value);
		value.Clear();
	}

	void Inspect() override
	{
		ImGui::Spacing();
		ImGui::InputInt("Health ", &_health);
		ImGui::Spacing();

		//Inspect EnemyType? Where is the Enum list for drop down Bar?
		ImGui::Spacing();
		ImGui::InputInt("EnemyType ", &_enemyType);
		ImGui::Spacing();
	}

//Constructor
	Boss();
	void SerialiseComponent(Serialiser& document);

	void Init();
	void Update(double dt);

	Vector3& GetDestinationPos();	// gets _target's position
	Vector3& GetPosition();	// gets _parent's position

	void Shoot();
	void Attack();

	void FSM();

	void ChancePickUps();

	void OnCollision2DTrigger(Collider2D* other);
};

#endif
