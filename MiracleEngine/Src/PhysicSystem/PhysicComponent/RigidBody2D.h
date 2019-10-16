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

#include "MathLib/SYMath.h"

class RigidBody2D
{
public:
	Vector3 _velocity;
	Vector3 _direction;
	Vector3 _appliedForce;
	float _angle;
	float _mass;
	float _fictionVal;
	bool _static;

	RigidBody2D();
	~RigidBody2D() = default;

	void UpdateVec(double dt);
	void UpdatePos(double dt);

	void Draw();
};

#endif
