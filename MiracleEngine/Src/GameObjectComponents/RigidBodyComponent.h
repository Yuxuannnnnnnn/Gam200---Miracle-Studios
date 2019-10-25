#pragma once
#include "IComponentSystem.h"



class RigidBodyComponent : public IComponentSystem
{
private:
	bool _collidable;

public:
	RigidBodyComponent(bool collidable = true)
		:_collidable(collidable)
	{
	}
// GetPID
	size_t GetParentId() const override
	{
		return _ParentId;
	}
	std::string ComponentName() const override
	{
		return "RigidBodyComponent";
	}
};

