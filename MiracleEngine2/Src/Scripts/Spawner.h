#pragma once
#include "GameObject/Components/Logic/IScript.h"

#ifndef SPAWNER_H
#define	SPAWNER_H

/*_bulletType
	0 unknown
	1 walker
	2 shooter
	3 charger
*/

class Spawner : public IScript
{
private:
// Logic Data - General
	bool _init;
	int _health;
	int _spawntype;
// Logic - Behaviour
	double _timerSpawn;
	double _timerCooldownSpawn;
public:
	void SerialiseComponent(Serialiser& document) override;
	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;
	void Inspect() override;

	Spawner();

	void Init();
	void Update(double dt);

	void Spawn();
};

#endif
