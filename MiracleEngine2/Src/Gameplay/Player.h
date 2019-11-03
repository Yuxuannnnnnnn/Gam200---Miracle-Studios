#pragma once
#include "GameObjectComponents/LogicComponents/IScript.h"


class Player : public IScript
{
private:
	
public:

	void Update(double dt);

	void updateMovement(double dt);

};