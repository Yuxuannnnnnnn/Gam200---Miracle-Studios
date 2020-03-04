#pragma once
#include "GameObject/Components/Logic/IScript2.h"

#ifndef SPAWNER_H
#define	SPAWNER_H

/*_bulletType
	0 unknown
	1 charger
	2 shooter
*/

class Spawner : public IScript2
{
private:
// Logic Data - General
	bool _init;
	int _health, _healthMax;
	int _spawnType;
	int _spawnAmount;
// Logic - Behaviour
	double _timerSpawn, _timerSpawnCooldown;
	double _timerLight, _timerLightDuration;
	bool _light, _lightPrevState;
	
public:
	void SerialiseComponent(Serialiser& document)
	{
		if (document.HasMember("Health") && document["Health"].IsInt())
			_health = _healthMax = document["Health"].GetInt();

		if (document.HasMember("SpawnType") && document["SpawnType"].IsInt())
			_spawnType = document["SpawnType"].GetInt();

		if (document.HasMember("SpawnCooldown") && document["SpawnCooldown"].GetDouble())
			_timerSpawn = _timerSpawnCooldown = document["SpawnCooldown"].GetDouble();

		if (document.HasMember("LightDuration") && document["LightDuration"].GetDouble())
			_timerLightDuration = document["LightDuration"].GetDouble();

		if (document.HasMember("SpawnAmount") && document["SpawnAmount"].IsInt())
			_spawnAmount = document["SpawnAmount"].GetInt();
	}

	//Function Not needed for Scripts
	void DeSerialiseComponent(DeSerialiser& prototypeDoc)
	{
		//rapidjson::Value value;
		//prototypeDoc.AddMember("Script2Data", rapidjson::Value(true));
		//value.SetArray();
		//{
		//	rapidjson::Value object;
		//	object.SetObject();
		//	object.AddMember("Health", rapidjson::Value(_healthMax), prototypeDoc.Allocator());
		//	object.AddMember("SpawnType", rapidjson::Value(_spawnType), prototypeDoc.Allocator());
		//	object.AddMember("SpawnCooldown", rapidjson::Value(_timerSpawnCooldown), prototypeDoc.Allocator());
		//	object.AddMember("LightDuration", rapidjson::Value(_timerLightDuration), prototypeDoc.Allocator());
		//	object.AddMember("SpawnAmount", rapidjson::Value(_spawnAmount), prototypeDoc.Allocator());
		//	value.PushBack(object, prototypeDoc.Allocator());
		//}
	}

	void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
	{
		rapidjson::Value value;

		value.SetString(rapidjson::StringRef(ToScriptName(_type)));
		prototypeDoc.AddMember("Script2Id", value, allocator);

		value.SetInt(_healthMax);
		prototypeDoc.AddMember("Health", value, allocator);		
		
		value.SetInt(_spawnType);
		prototypeDoc.AddMember("SpawnType", value, allocator);

		value.SetDouble(_timerSpawnCooldown);
		prototypeDoc.AddMember("SpawnCooldown", value, allocator);

		value.SetDouble(_timerLightDuration);
		prototypeDoc.AddMember("LightDuration", value, allocator);

		value.SetInt(_spawnAmount);
		prototypeDoc.AddMember("SpawnAmount", value, allocator);

	}


	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
	{
		LogicComponent* protoLogicCom = dynamic_cast<LogicComponent*>(protoCom);

		size_t UId = protoLogicCom->GetScriptContianer()[_type];

		Spawner* script = (Spawner*)(MyLogicSystem.getScriptPtr(UId));

		if (!script)
		{
			DeSerialiseComponent(value, allocator);
			return;
		}

		rapidjson::Value Health;
		rapidjson::Value SpawnType;
		rapidjson::Value SpawnCooldown;
		rapidjson::Value LightDuration;
		rapidjson::Value SpawnAmount;

		bool addComponentIntoSceneFile = false;

		if (script->_healthMax != _healthMax)
		{
			addComponentIntoSceneFile = true;
			Health.SetInt(_healthMax);
		}

		if (script->_spawnType != _spawnType)
		{
			addComponentIntoSceneFile = true;
			SpawnType.SetInt(_spawnType);
		}

		if (script->_timerSpawnCooldown != _timerSpawnCooldown)
		{
			addComponentIntoSceneFile = true;
			SpawnCooldown.SetDouble(_timerSpawnCooldown);
		}

		if (script->_timerLightDuration != _timerLightDuration)
		{
			addComponentIntoSceneFile = true;
			LightDuration.SetDouble(_timerLightDuration);
		}

		if (script->_spawnAmount != _spawnAmount)
		{
			addComponentIntoSceneFile = true;
			SpawnAmount.SetInt(_spawnAmount);
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

			if (!SpawnType.IsNull())	//if rapidjson::value container is not empty
			{
				value.AddMember("SpawnType", SpawnType, allocator);
			}

			if (!SpawnCooldown.IsNull())	//if rapidjson::value container is not empty
			{
				value.AddMember("SpawnCooldown", SpawnCooldown, allocator);
			}

			if (!LightDuration.IsNull())	//if rapidjson::value container is not empty
			{
				value.AddMember("LightDuration", LightDuration, allocator);
			}

			if (!SpawnAmount.IsNull())	//if rapidjson::value container is not empty
			{
				value.AddMember("SpawnAmount", SpawnAmount, allocator);
			}
		}

	}
	void Inspect()
	{
		ImGui::Spacing();
		ImGui::InputInt("Health ", &_health);
		ImGui::Spacing();
		ImGui::InputInt("SpawnType ", &_spawnType);
		ImGui::Spacing();
		ImGui::InputDouble("SpawnCooldown ", &_timerSpawnCooldown);
		ImGui::Spacing();
		ImGui::InputDouble("LightDuration ", &_timerLightDuration);
		ImGui::Spacing();
		ImGui::InputInt("SpawnAmount ", &_spawnAmount);
		ImGui::Spacing();
	}

	Spawner();
	Spawner* Clone();

	void Init();
	void Update(double dt);

	void Spawn();
};

#endif
