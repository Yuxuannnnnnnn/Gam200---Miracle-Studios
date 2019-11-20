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
#include "CollisionMap.h"
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

	CollisionMap _collisionMap;

private:
	CollisionTable _collisionTable;

	size_t _pickUId;
public:
	PhysicsSystem() :_pickUId{0} {}
	~PhysicsSystem() {}

	PhysicsSystem(const PhysicsSystem& rhs) = delete;
	PhysicsSystem& operator= (const PhysicsSystem& rhs) = delete;

	void Update(double dt);

	// level editer function
	void UpdateDraw();
	void UpdatePicking();

	void UpdateColliderData(Collider2D* collider);

	// 
	void RemoveRigidBody2d(size_t uid);
	void RemoveCollider2d(size_t uid);
	void RemoveButton(size_t uid);
	void RemovePick(size_t uid);
	void RemoveTransform(size_t uid);

protected:
	RigidBody2D* GetRigidBody2D(size_t uId);
	TransformComponent* GetTransform(size_t uId);

private:
	// rigidbody
	void UpdatePhyiscs(double dt);
	void UpdateTransform(double dt);

	// collision
	void UpdateCollision(double dt);
	void UpdateStaticCollision(double dt);
	int CollisionCheckTile(Collider2D* object, unsigned centerTileId, double dt, unsigned dir = 0, unsigned checked = 0);
	void CollisionCheckResponse(Collider2D* collider1, Collider2D* collider2, double dt);
	void UpdateButtons();


	void DrawRigidbody2D();
	void DrawCollider2D();
	void DrawButton();

public:
	static void AddForce(size_t uId, Vector3 forceDir, float force);
	static void AddForwardForce(size_t uId, float force);
};

#endif
