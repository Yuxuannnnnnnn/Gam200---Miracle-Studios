#pragma once
#include "GameObject/Components/Logic/IScript2.h"

#ifndef SPAWNER_H
#define	SPAWNER_H

/*_bulletType
	0 unknown
	1 walker
	2 shooter
	3 charger
*/

class Spawner : public IScript2
{
private:
// Logic Data - General
	bool _init;
	int _health, _healthMax;
	int _spawnType;
// Logic - Behaviour
	double _timerSpawn, _timerSpawnCooldown;
public:
	void SerialiseComponent(Serialiser& document)
	{
		if (document.HasMember("Health") && document["Health"].IsInt())
			_health = _healthMax = document["Health"].GetInt();
		if (document.HasMember("SpawnType") && document["SpawnType"].IsInt())
			_spawnType = document["SpawnType"].GetInt();
		if (document.HasMember("SpawnCooldown") && document["SpawnCooldown"].GetDouble())
			_timerSpawnCooldown = document["SpawnCooldown"].GetDouble();
	}
	void DeSerialiseComponent(DeSerialiser& prototypeDoc)
	{
		rapidjson::Value value;
		prototypeDoc.AddMember("Script2Data", rapidjson::Value(true));
		value.SetInt(_healthMax);
		prototypeDoc.AddMember("Health", value);
		value.SetInt(_spawnType);
		prototypeDoc.AddMember("SpawnType", value);
		value.SetDouble(_timerSpawnCooldown);
		prototypeDoc.AddMember("SpawnCooldown", value);
	}
	void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
	{
	}
	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
	{
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
	}

	Spawner();
	Spawner* Clone();

	void Init();
	void Update(double dt);

	void Spawn();
};

#endif
