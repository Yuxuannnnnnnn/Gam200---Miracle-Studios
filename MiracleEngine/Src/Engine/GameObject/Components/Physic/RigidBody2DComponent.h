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

#include "../../IComponent.h"
#include "Tools/MathLib/Math.h"

enum class RIGIDBODY_TYPE {
	RB_STATIC = true,
	RB_DYNAMIC = false
};

class RigidBody2D : public IComponent
{
public:
	Vector3 _velocity;
	Vector3 _appliedForce;
	Vector3 _direction;

	/*float _angularVelocity;
	float _angularForce;*/

	float _mass;
	float _fictionVal;

	bool _static;
	bool _componentEnable;

public:
	RigidBody2D();
	RigidBody2D(const RigidBody2D& rhs) = default;
	virtual ~RigidBody2D() = default;

	RigidBody2D& operator= (const RigidBody2D& rhs) = delete;

	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser& document) override;
	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;
	void Inspect() override;
	void DeserialiseComponentSceneFile(IComponent* protoCom, DeSerialiser& SceneFile) { return; }

///////////////////////////////////////////////////////////////////////////////
	// Function Setting and Getting only

	void SetVelocity(Vector3 velocity);
	void SetFiction(float value);
	void SetMass(float mass);
	void SetType(bool type);


};

#endif
