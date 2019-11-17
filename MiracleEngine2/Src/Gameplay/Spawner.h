#pragma once
#include "GameObjectComponents/LogicComponents/IScript.h"

#ifndef SPAWNER_H
#define	SPAWNER_H

class Spawner : public IScript
{
private:
// Logic Data - General
	bool _init;
	int _health;
// Logic - Behaviour
	double _timer;
	const double _timeCooldown;
	TypeIdGO _typeId;
	const float _radiusSpawn;
	
public:
	Spawner();

	void Init();
	void Update(double dt);

	void Spawn();
};

#endif
