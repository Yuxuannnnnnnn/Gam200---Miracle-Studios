///////////////////////////////////////////////////////////////////////////////////////
//
//	PhysicsSystem.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _RIGIDBODY_MANAGER_H
#define _RIGIDBODY_MANAGER_H

#include <unordered_map>
#include "GameObject/Components/Physic/RigidBody2DComponent.h"

#include "IContainer.h"

class RigidbodyManager final 
{

public:
	RigidbodyManager() = default;
	~RigidbodyManager() {}

	RigidbodyManager(const RigidbodyManager& rhs) = delete;
	RigidbodyManager& operator= (const RigidbodyManager& rhs) = delete;

	void UpdateVelocity(double dt);
	void ApplyVelocityToObject(double dt);

	void Draw();

	static void AddForce(size_t uId, Vector3 forceDir, float force);
	static void AddForwardForce(size_t uId, float force);
};

#endif
