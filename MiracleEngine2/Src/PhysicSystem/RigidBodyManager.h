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
#include "GameObjectComponents/PhysicsComponents/RigidBody2D.h"

#include "IContainer.h"

class RigidbodyManager final : public IContainer
{
public:
	std::unordered_map < size_t, RigidBody2D* >	_rigidBody2dList;
private:

public:
	RigidbodyManager() = default;
	~RigidbodyManager() {}

	RigidbodyManager(const RigidbodyManager& rhs) = delete;
	RigidbodyManager& operator= (const RigidbodyManager& rhs) = delete;

	void UpdateVelocity(double dt);
	void ApplyVelocityToObject(double dt);

	void Draw();

	void AddObject(size_t uId);
	void RemoveObject(size_t uId);

	static void AddForce(size_t uId, Vector3 forceDir, float force);
	static void AddForwardForce(size_t uId, float force);
};

#endif
