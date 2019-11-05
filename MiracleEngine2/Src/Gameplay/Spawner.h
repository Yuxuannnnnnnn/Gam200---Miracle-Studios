#pragma once
#include "GameObjectComponents/LogicComponents/IScript.h"

class Spawner : public IScript
{
private:
	TypeIdGO _typeId;
	const float _radiusSpawn;
	double _timer;
	const double _timeCooldown;
	bool _init;
public:
//Constructor
	Spawner();

	int _health;

// InUpEx
	void Init();
	void Update(double dt);

	void Spawn();
};