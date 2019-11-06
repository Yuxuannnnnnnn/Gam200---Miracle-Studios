#pragma once
#include "GameObjectComponents/LogicComponents/IScript.h"


class Player : public IScript
{
private:
	int _health;
public:
	Player();

	void Update(double dt);

	void updateMovement(double dt);
	int GetHealth();
	void SetHealth(int val);
};