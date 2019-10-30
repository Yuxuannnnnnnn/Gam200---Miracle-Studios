#pragma once
#include "GameObjectComponents/IComponentSystem.h"



class PhysicsComponent: public IComponentSystem
{
public:

	std::string ComponentName() const
	{
		return "Physics Component";
	}

};

