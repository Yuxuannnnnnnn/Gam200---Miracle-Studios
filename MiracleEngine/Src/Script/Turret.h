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
	void Turret::SerialiseComponent(Serialiser& document)
	{
		if (document.HasMember("Health") && document["Health"].IsInt())
			_health = (document["Health"].GetInt());
		if (document.HasMember("Firerate") && document["Firerate"].IsDouble())
			_timeAttackCooldown = (document["Firerate"].GetDouble());
		if (document.HasMember("AttackRangeShoot") && document["AttackRangeShoot"].IsInt())
		{
			_attackRangeShoot = document["AttackRangeShoot"].GetDouble();
			_attackRangeShoot *= 100;
			_attackRangeShoot *= _attackRangeShoot;
		}
	}

	void Turret::DeSerialiseComponent(DeSerialiser& prototypeDoc)
	{
		rapidjson::Value value;

		value.SetBool(true);
		prototypeDoc.AddMember("Script2Id", value);

		value.SetArray();
		{
			rapidjson::Value object;
			object.AddMember("Health", _health, prototypeDoc.Allocator());
			object.AddMember("Firerate", _timeAttackCooldown, prototypeDoc.Allocator());
			_attackRangeShoot /= 100;
			_attackRangeShoot /= _attackRangeShoot;
			object.AddMember("AttackRangeShoot", _attackRangeShoot, prototypeDoc.Allocator());
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
			object.AddMember("Health", _health, allocator);
			object.AddMember("Firerate", _timeAttackCooldown, allocator);
			_attackRangeShoot /= 100;
			_attackRangeShoot /= _attackRangeShoot;
			object.AddMember("AttackRangeShoot", _attackRangeShoot, allocator);
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
	}

	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
	{
		return;
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
