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

#include "GameObjectComponents/IComponentSystem.h"
#include "MathLib/SYMath.h"

enum class RIGIDBODY_TYPE {
	RB_STATIC = true,
	RB_DYNAMIC = false
};

class RigidBody2D : public IComponentSystem
{
public:
	Vector3 _velocity;
	Vector3 _direction;
	Vector3 _appliedForce;
	Vector3 _position;

	/*float _angularVelocity;
	float _angularForce;*/

	float _angle;
	float _mass;
	float _fictionVal;
	bool _static;
	bool _enable;

public:
	RigidBody2D();
	~RigidBody2D() = default;

	void UpdateVec(double dt);
	void UpdatePos(double dt);

	void Draw();

	void StopVelocity();
	void AddForce(Vector3 force);
	void RemoveForce(Vector3 force);
	void SetFiction(float value);
	void SetMass(float mass);
	void SetType(bool type);
	void SetEnable(bool enable);

	std::string ComponentName() const override
	{
		return "RigidBody2D Component";
	}
};

#endif
