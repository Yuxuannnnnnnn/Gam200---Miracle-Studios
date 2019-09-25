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

#include "CircleCollider2D.h"
#include "BoxCollider2D.h"
#include "RigidBody2D.h"

#include<iostream>
#include<vector>
#include<iterator>



class Physics final
{
	//Dynamic array of GameObjects
	std::vector<Collider2D*> _ListCollider2D;
	std::vector<RigidBody2D*> _ListRigidBody2D;

  size_t _count;
  
public:
	//No replication of class object
	Physics(const Physics& rhs) = delete;
	Physics& operator= (const Physics& rhs) = delete;

	Physics();

	//Deletes all gameObjects in the list
	~Physics();
  
	void Update(double dt);
  
	void CreateCircleCollider(const Vector3& _v, const float& r);
  
	void CreateBoxCollider(const Vector3& _mMinPos, const Vector3& _mMaxPos);
  
  
};

#endif
