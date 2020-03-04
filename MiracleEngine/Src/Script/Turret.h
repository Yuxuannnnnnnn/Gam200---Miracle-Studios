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
	double _timerAttack, _timeAttackCooldown;	
	int _attackRangeShoot; // currently set to 1*_mapTileSize
// Logic Data - Animation
	double _deployTime, _aliveTime;
	bool _shooting;
	int _animState, _animStatePrev; // 1==StartIdle, 2==StartShoot

	GameObject* _turretBase;
	Vec3 _deployScale;

	TransformComponent* _transform;

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

		if (document.HasMember("AliveTime") && document["AliveTime"].IsDouble())
			_aliveTime = (document["AliveTime"].GetDouble());

		if (document.HasMember("DeployScale") && document["DeployScale"].IsArray())
		{
			if (document["DeployScale"][0].IsFloat() && document["DeployScale"][1].IsFloat())	//Check the array values
				_deployScale = Vector3{ document["DeployScale"][0].GetFloat(), document["DeployScale"][1].GetFloat(), 1.f };

			if (document["DeployScale"].Size() == 3)
			{
				_deployScale.SetZ(document["DeployScale"][2].GetFloat());
			}
		}
	}
	//Function Not Needed for scripts
	void Turret::DeSerialiseComponent(DeSerialiser& prototypeDoc)
	{
		//rapidjson::Value value;
		//
		//value.SetBool(true);
		//prototypeDoc.AddMember("Script2Id", value);
		//
		//value.SetArray();
		//{
		//	rapidjson::Value object;
		//	object.SetObject();
		//	object.AddMember("Health", _healthMax, prototypeDoc.Allocator());
		//	object.AddMember("Firerate", _timeAttackCooldown, prototypeDoc.Allocator());
		//	_attackRangeShoot /= 100;
		//	_attackRangeShoot /= _attackRangeShoot;
		//	object.AddMember("AttackRangeShoot", _attackRangeShoot, prototypeDoc.Allocator());
		//	object.AddMember("DeployTime", _deployTime, prototypeDoc.Allocator());
		//	object.AddMember("AliveTime", _aliveTime, prototypeDoc.Allocator());
		//	value.PushBack(object, prototypeDoc.Allocator());
		//}
	}

	void Turret::DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
	{
		rapidjson::Value value;

		value.SetString(rapidjson::StringRef(ToScriptName(_type)));
		prototypeDoc.AddMember("Script2Id", value, allocator);

		value.SetInt(_healthMax);
		prototypeDoc.AddMember("Health", value, allocator);

		value.SetDouble(_timeAttackCooldown);
		prototypeDoc.AddMember("Firerate", value, allocator);

		int attackRangeShoot = sqrt(_attackRangeShoot) / 100.0;
		value.SetInt(attackRangeShoot);
		prototypeDoc.AddMember("AttackRangeShoot", value, allocator);

		value.SetDouble(_deployTime);
		prototypeDoc.AddMember("DeployTime", value, allocator);

		value.SetDouble(_aliveTime);
		prototypeDoc.AddMember("AliveTime", value, allocator);

		value.SetArray();
		{
			for (unsigned i = 0; i < 3; i++)
				value.PushBack(rapidjson::Value(_deployScale[i]).Move(), allocator);
		}
		prototypeDoc.AddMember("DeployScale", value, allocator);


	}


	void Turret::DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
	{
		LogicComponent* protoLogicCom = dynamic_cast<LogicComponent*>(protoCom);

		size_t UId = protoLogicCom->GetScriptContianer()[_type];

		Turret* script = (Turret*)(MyLogicSystem.getScriptPtr(UId));

		if (!script)
		{
			DeSerialiseComponent(value, allocator);
			return;
		}

		rapidjson::Value Health;
		rapidjson::Value Firerate;
		rapidjson::Value AttackRangeShoot;
		rapidjson::Value DeployTime;
		rapidjson::Value AliveTime;
		rapidjson::Value DeployScale;

		bool addComponentIntoSceneFile = false;

		if (script->_healthMax != _healthMax)
		{
			addComponentIntoSceneFile = true;
			Health.SetInt(_healthMax);
		}

		if (script->_timeAttackCooldown != _timeAttackCooldown)
		{
			addComponentIntoSceneFile = true;
			Firerate.SetDouble(_timeAttackCooldown);
		}

		if (script->_attackRangeShoot != _attackRangeShoot)
		{
			addComponentIntoSceneFile = true;
			int attackRangeShoot = sqrt(_attackRangeShoot) / 100.0;
			AttackRangeShoot.SetInt(attackRangeShoot);
		}

		if (script->_deployTime != _deployTime)
		{
			addComponentIntoSceneFile = true;
			DeployTime.SetDouble(_deployTime);
		}

		if (script->_aliveTime != _aliveTime)
		{
			addComponentIntoSceneFile = true;
			AliveTime.SetDouble(_aliveTime);
		}

		for (int i = 0; i < 3; i++)
		{
			if (script->_deployScale[i] != _deployScale[i])
			{
				addComponentIntoSceneFile = true;
				DeployScale.SetArray();
				for (int i = 0; i < 3; i++)
				{
					DeployScale.PushBack(rapidjson::Value(_deployScale[i]).Move(), allocator);
				}
				break;
			}
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

			if (!Firerate.IsNull())	//if rapidjson::value container is not empty
			{
				value.AddMember("Firerate", Firerate, allocator);
			}

			if (!AttackRangeShoot.IsNull())	//if rapidjson::value container is not empty
			{
				value.AddMember("AttackRangeShoot", AttackRangeShoot, allocator);
			}

			if (!DeployTime.IsNull())	//if rapidjson::value container is not empty
			{
				value.AddMember("DeployTime", DeployTime, allocator);
			}

			if (!AliveTime.IsNull())	//if rapidjson::value container is not empty
			{
				value.AddMember("AliveTime", AliveTime, allocator);
			}

			if (!DeployScale.IsNull())	//if rapidjson::value container is not empty
			{
				value.AddMember("DeployScale", DeployScale, allocator);
			}
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
		ImGui::InputDouble("AliveTime ", &_aliveTime);
		ImGui::Spacing();

		ImGui::Spacing();
		ImGui::InputFloat2("DeployScale ", _deployScale.m);
		ImGui::Spacing();
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
