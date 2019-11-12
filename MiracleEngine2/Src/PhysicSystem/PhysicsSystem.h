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

#include <unordered_map>
#include "CollisionTable.h"
#include "GameObjectComponents/PhysicsComponents/Collider2D.h"
#include "GameObjectComponents/PhysicsComponents/RigidBody2D.h"
#include "GameObjectComponents/PickingCollider.h"
#include "GameObjectComponents/ButtonComponent.h"

class PhysicsSystem final
{
public:
	std::unordered_map < size_t, RigidBody2D* >	_rigidBody2dList;
	std::unordered_map < size_t, Collider2D* > _collider2dList;
	std::unordered_map< size_t, ButtonComponent*> _buttonList;
	std::unordered_map< size_t, PickingCollider*> _pickList;

	std::unordered_map< size_t, TransformComponent*> _transformList;
private:
	CollisionTable _collisionTable;

public:
	PhysicsSystem() {};
	~PhysicsSystem() {};

	PhysicsSystem(const PhysicsSystem& rhs) = delete;
	PhysicsSystem& operator= (const PhysicsSystem& rhs) = delete;

	void Update(double dt);

	// level editer function
	void UpdateDraw();
	void UpdatePicking();

	void UpdateColliderData(Collider2D* collider);

protected:
	RigidBody2D* GetRigidBody2D(size_t uId);
	TransformComponent* GetTransform(size_t uId);

private:
	// rigidbody
	void UpdatePhyiscs(double dt);
	void UpdateTransform(double dt);

	// collision
	void UpdateCollision(double dt);
	void UpdateButtons();

	// EventHandler
	void UpdateEvents();
	void DrawRigidbody2D();
	void DrawCollider2D();
	void DrawButton();

public:
	static void AddForce(size_t uId, Vector3 forceDir, float force);
	static void AddForwardForce(size_t uId, float force);
};

#endif
