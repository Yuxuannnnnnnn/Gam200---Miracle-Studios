#pragma once
#include "IComponentSystem.h"



class PhysicsComponent: public IComponentSystem
{
	size_t _ParentId;
public:
// GetPID
	size_t GetParentId() const override
	{
		return _ParentId;
	}
	std::string ComponentName() const
	{
		return "Physics Component";
	}

};

