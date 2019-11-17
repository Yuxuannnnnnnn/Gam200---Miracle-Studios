///////////////////////////////////////////////////////////////////////////////////////
//
//	Physics.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _PHYSICS_SYSTEM_H
#define _PHYSICS_SYSTEM_H

#include "GameObjectComponents/PhysicsComponents/Collider2D.h"
#include "GameObjectComponents/PhysicsComponents/RigidBody2D.h"

#include "GameObjectComponents/PickingCollider.h"

#include<iostream>
#include<vector>
#include<iterator>

class Physics final
{
public:
	//Dynamic array of Components
	std::vector<Collider2D*> _ListCollider2D;
	std::vector<RigidBody2D*> _ListRigidBody2D;
	std::vector<PickingCollider*> _ListPickableObject;

	bool _enable;

public:
	Physics();
	//Deletes all gameObjects in the list
	~Physics();

	void Update(double dt);

	Collider2D* CreateCircleCollider(TransformComponent* transform);
	Collider2D* CreateBoxCollider(TransformComponent* transform);
	Collider2D* CreateEdgeCollider(TransformComponent* transform);
	RigidBody2D* CreateRigidBody2D(TransformComponent* transform);
	PickingCollider* CreatePickableObject(TransformComponent* transform);

	//No replication of class object
	Physics(const Physics& rhs) = delete;
	Physics& operator= (const Physics& rhs) = delete;

private:
	void UpdatePhyiscs(double dt);
	void UpdateCollision(double dt);
	void UpdateTransform(double dt);
	void UpdateEvents();

	void UpdatePicking(double dt);

	void Clear();

};

#endif
