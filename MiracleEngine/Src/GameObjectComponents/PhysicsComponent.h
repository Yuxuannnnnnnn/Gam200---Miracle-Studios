#pragma once




class PhysicsComponent: public IComponentSystem
{

public:
	std::string ComponentName() const
	{
		return "Physics Component";
	}


};

