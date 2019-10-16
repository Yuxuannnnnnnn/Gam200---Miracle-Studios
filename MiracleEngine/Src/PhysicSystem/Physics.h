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

#include "CollisionComponent/Collider2D.h"
#include "PhysicComponent/RigidBody2D.h"

#include<iostream>
#include<vector>
#include<iterator>

class Physics final
{
public:
	//Dynamic array of Components
	std::vector<Collider2D*> _ListCollider2D;
	std::vector<RigidBody2D*> _ListRigidBody2D;

	bool _enable;

public:
	Physics();
	//Deletes all gameObjects in the list
	~Physics();

	void Update(double dt);
	
	Collider2D* CreateCircleCollider(const Vector3& _v, const float& r);

	Collider2D* CreateBoxCollider(const Vector3& _cenPos, const Vector3& _scale, float angle);

	Collider2D* CreateEdgeCollider(const Vector3& pos, float scale, float dir);

	RigidBody2D* CreateRigidBody2D();

	void Clear();

private:
	//No replication of class object
	Physics(const Physics& rhs) = delete;
	Physics& operator= (const Physics& rhs) = delete;
};

#endif
