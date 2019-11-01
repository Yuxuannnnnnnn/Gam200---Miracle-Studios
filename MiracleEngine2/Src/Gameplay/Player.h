#pragma once
#include "GameObjectComponents/LogicComponents/IScript.h"


class Player : public IScript
{
private:
	
public:

	void Update(double dt) override;

	void updateMovement(double dt);

};