#pragma once
#include "../Isystem.h"
#include "../inputsystem/inputsystem.h"
#include "../graphicsystem/graphicsystem.h"
#include "../GameObject.h"
#include <vector>
#include "deltatime.h"

class Engine
{
public:
	void Init();
	void Update();
	void Exit();
	std::vector<GameObject> _objectlist;
	DeltaTime _dt;
private:
	std::vector<ISystem*> _systems;
	
};

extern Engine* engine;