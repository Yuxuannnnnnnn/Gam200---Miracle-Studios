#pragma once
#include "GameObject/Components/Logic/IScript2.h"

#ifndef TURRET_H
#define	TURRET_H

class Turret : public IScript2
{
private:
// Logic Data - General
	bool _init;
	int _health, _healthMax;
// Logic - Behaviour
	GameObject* _target;
	size_t _targetUid;
	int _state;
	double _timerAttack;
	double _timeAttackCooldown;	
	int _attackRangeShoot; // currently set to 1*_mapTileSize
// Logic Data - Animation
	double _deployTime;
	bool _shooting;
	int _animState, _animStatePrev; // 1==StartIdle, 2==StartShoot

public:
	void Turret::SerialiseComponent(Serialiser& document)
	{
		if (document.HasMember("Health") && document["Health"].IsInt())
			_health = _healthMax = (document["Health"].GetInt());
		if (document.HasMember("Firerate") && document["Firerate"].IsDouble())
			_timeAttackCooldown = (document["Firerate"].GetDouble());
		if (document.HasMember("AttackRangeShoot") && document["AttackRangeShoot"].IsInt())
		{
			_attackRangeShoot = document["AttackRangeShoot"].GetInt();
			_attackRangeShoot *= 100;
			_attackRangeShoot *= _attackRangeShoot;
		}
		if (document.HasMember("DeployTime") && document["DeployTime"].IsDouble())
			_deployTime = (document["DeployTime"].GetDouble());
	}

	void Turret::DeSerialiseComponent(DeSerialiser& prototypeDoc)
	{
		rapidjson::Value value;

		value.SetBool(true);
		prototypeDoc.AddMember("Script2Id", value);

		value.SetArray();
		{
			rapidjson::Value object;
			object.SetObject();
			object.AddMember("Health", _healthMax, prototypeDoc.Allocator());
			object.AddMember("Firerate", _timeAttackCooldown, prototypeDoc.Allocator());
			_attackRangeShoot /= 100;
			_attackRangeShoot /= _attackRangeShoot;
			object.AddMember("AttackRangeShoot", _attackRangeShoot, prototypeDoc.Allocator());
			object.AddMember("DeployTime", _deployTime, prototypeDoc.Allocator());
			value.PushBack(object, prototypeDoc.Allocator());
		}
	}

	void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
	{
		rapidjson::Value value;

		value.SetBool(true);
		prototypeDoc.AddMember("Script2Id", value, allocator);

		value.SetArray();
		{
			rapidjson::Value object;
			object.SetObject();
			object.AddMember("Health", _healthMax, allocator);
			object.AddMember("Firerate", _timeAttackCooldown, allocator);
			_attackRangeShoot /= 100;
			_attackRangeShoot /= _attackRangeShoot;
			object.AddMember("AttackRangeShoot", _attackRangeShoot, allocator);
			object.AddMember("DeployTime", _deployTime, allocator);
			value.PushBack(object, allocator);
		}
	}

	void Turret::Inspect()
	{
		ImGui::Spacing();
		ImGui::InputInt("Health ", &_health);
		ImGui::Spacing();
		ImGui::InputDouble("Firerate ", &_timeAttackCooldown);
		ImGui::Spacing();
		ImGui::InputInt("AttackRange Shoot ", &_attackRangeShoot);
		ImGui::Spacing();
		ImGui::InputDouble("DeployTime ", &_deployTime);
		ImGui::Spacing();
	}

	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
	{
		rapidjson::Value doc;

		doc.SetBool(true);
		value.AddMember("Script2Id", doc, allocator);

		doc.SetArray();
		{
			rapidjson::Value object;
			object.SetObject();
			object.AddMember("Health", _health, allocator);
			object.AddMember("Firerate", _timeAttackCooldown, allocator);
			_attackRangeShoot /= 100;
			_attackRangeShoot /= _attackRangeShoot;
			object.AddMember("AttackRangeShoot", _attackRangeShoot, allocator);
			object.AddMember("DeployTime", _deployTime, allocator);
			doc.PushBack(object, allocator);
		}
	}

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
