#pragma once
#include "GameObjectComponents/LogicComponents/IScript.h"

class ButtonUI : public IScript
{
private:

public:
	//Constructor
	ButtonUI();

	int _health;

	// InUpEx
	void Init();
	void Update(double dt);
	void Exit();

};