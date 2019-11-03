#pragma once
#include "GameObjectComponents/LogicComponents/IScript.h"

class Enemy : public IScript
{
private:

public:
	int _health;

	void Update(double dt);
};