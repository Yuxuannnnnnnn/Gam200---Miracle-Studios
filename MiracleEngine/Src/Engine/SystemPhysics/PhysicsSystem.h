///////////////////////////////////////////////////////////////////////////////////////
//
//	PhysicsSystem.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _PHYSICS_SYSTEM_H
#define _PHYSICS_SYSTEM_H

#include "GameObject/Components/Graphic/TransformComponent.h"

class PhysicsSystem final
{
public:
	PhysicsSystem() = default;
	~PhysicsSystem() {}

	PhysicsSystem(const PhysicsSystem& rhs) = delete;
	PhysicsSystem& operator= (const PhysicsSystem& rhs) = delete;

	void Update(double dt);
	void Draw();




	static void UpdateTransformMartix(TransformComponent* transform);
};

#endif
