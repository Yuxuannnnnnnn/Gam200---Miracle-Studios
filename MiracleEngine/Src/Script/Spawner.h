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
	void DeSerialiseComponent(DeSerialiser& prototypeDoc)
	{
		rapidjson::Value value;
		prototypeDoc.AddMember("Script2Data", rapidjson::Value(true));
		value.SetArray();
		{
			rapidjson::Value object;
			object.SetObject();
			object.AddMember("Health", rapidjson::Value(_healthMax), prototypeDoc.Allocator());
			object.AddMember("SpawnType", rapidjson::Value(_spawnType), prototypeDoc.Allocator());
			object.AddMember("SpawnCooldown", rapidjson::Value(_timerSpawnCooldown), prototypeDoc.Allocator());
			object.AddMember("LightDuration", rapidjson::Value(_timerLightDuration), prototypeDoc.Allocator());
			object.AddMember("SpawnAmount", rapidjson::Value(_spawnAmount), prototypeDoc.Allocator());
			value.PushBack(object, prototypeDoc.Allocator());
		}
	}
	void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
	{
		rapidjson::Value value;
		prototypeDoc.AddMember("Script2Data", rapidjson::Value(true), allocator);
		value.SetArray();
		{
			rapidjson::Value object;
			object.SetObject();
			object.AddMember("Health", rapidjson::Value(_healthMax), allocator);
			object.AddMember("SpawnType", rapidjson::Value(_spawnType), allocator);
			object.AddMember("SpawnCooldown", rapidjson::Value(_timerSpawnCooldown), allocator);
			object.AddMember("LightDuration", rapidjson::Value(_timerLightDuration), allocator);
			object.AddMember("SpawnAmount", rapidjson::Value(_spawnAmount), allocator);
			value.PushBack(object, allocator);
		}
	}
	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
	{
		// ???????????????????????????????????????????????
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
