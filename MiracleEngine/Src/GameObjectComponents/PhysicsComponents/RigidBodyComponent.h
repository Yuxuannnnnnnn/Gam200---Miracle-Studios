#pragma once
#include "GameObjectComponents/IComponentSystem.h"



class RigidBodyComponent : public IComponentSystem
{
private:
	bool _collidable;

public:
	RigidBodyComponent(bool collidable = true)
		:_collidable(collidable)
	{
	}

	std::string ComponentName() const override
	{
		return "RigidBodyComponent";
	}
};

