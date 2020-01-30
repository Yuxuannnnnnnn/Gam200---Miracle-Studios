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
	int _health;
	int _spawntype;
// Logic - Behaviour
	double _timerSpawn;
	double _timerCooldownSpawn;
public:
	void SerialiseComponent(Serialiser& document) ;
	void DeSerialiseComponent(DeSerialiser& prototypeDoc) ;
	void Inspect() ;

	Spawner();
	Spawner* Clone();

	void Init();
	void Update(double dt);

	void Spawn();
};

#endif
