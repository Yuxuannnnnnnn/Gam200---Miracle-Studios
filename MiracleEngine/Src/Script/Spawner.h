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
	int _health, _healthMax;
	int _spawnType;
	int _spawnAmount;
// Logic - Behaviour
	double _timerSpawn, _timerSpawnCooldown;
	double _timerLight, _timerLightDuration;
	bool _light, _lightPrevState;
	
public:
	void SerialiseComponent(Serialiser& document);
	//Function Not needed for Scripts
	void DeSerialiseComponent(DeSerialiser& prototypeDoc);
	void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator);
	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator);
	void Inspect();

	Spawner();
	Spawner* Clone();

	void Init();
	void LoadResource();
	void Update(double dt);

	void Spawn();
};

#endif
