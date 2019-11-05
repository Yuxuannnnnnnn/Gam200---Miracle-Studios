#pragma once
#include "GameObjectComponents/LogicComponents/IScript.h"

class SpawnerTwo : public IScript
{
private:
	TypeIdGO _typeId;
	const float _radiusSpawn;
	double _timer;
	const double _timeCooldown;
	bool _init;
public:
//Constructor
	SpawnerTwo();

	int _health;

// InUpEx
	void Init();
	void Update(double dt);

	void Spawn();
};