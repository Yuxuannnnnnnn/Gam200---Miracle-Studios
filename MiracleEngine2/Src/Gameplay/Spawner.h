#pragma once
#include "GameObjectComponents/LogicComponents/IScript.h"

class Spawner : public IScript
{
private:
	TypeIdGO _typeId;
	const float _radiusSpawn;
	double _timer;
	const double _timeCooldown;

public:
//Constructor
	Spawner();

	int _health;

// InUpEx
	void Update(double dt);

	void Spawn();
};