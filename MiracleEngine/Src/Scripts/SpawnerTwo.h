#pragma once
#include "GameObject/Components/Logic/IScript.h"

#ifndef SPAWNERTWO_H
#define	SPAWNERTWO_H

class SpawnerTwo : public IScript
{
private:
	// Logic Data - General
	bool _init;
	int _health;
	// Logic - Behaviour
	double _timer;
	const double _timeCooldown;
	//TypeIdGO _typeId;
	const float _radiusSpawn;

public:
	SpawnerTwo();

	void Init();
	void Update(double dt);

	void Spawn();
};

#endif
