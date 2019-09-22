#pragma once
#include "PrecompiledHeaders.h"
#include "IComponentSystem.h"



class PhysicsComponent: public IComponentSystem
{

public:
	std::string ComponentName() const
	{
		return "Physics Component";
	}

};

