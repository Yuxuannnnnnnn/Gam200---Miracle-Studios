///////////////////////////////////////////////////////////////////////////////////////
//
//	RigidBody2D.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _RIGIDBODY_2D_H
#define _RIGIDBODY_2D_H
#include "../Engine/GameObject.h"

#include "..//MathLib/Vector3.h"

class RigidBody2D : public GameObject
{
public:
	Vector3 Vec;
	Vector3 AppliedVec;
	Vector3 Dir;
	float angle;
	float mass;
	float fiction;
	bool _static;


	void Update(double dt)
	{
		Vec = AppliedVec;
		_pos += Vec * dt;
		AppliedVec = Vector3{};
	}
	
};

#endif
