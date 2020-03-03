///////////////////////////////////////////////////////////////////////////////////////
//
//	RigidBody2DComponent.h
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

class RigidBody2DComponent : public IComponent
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

public:
	RigidBody2DComponent();
	RigidBody2DComponent(const RigidBody2DComponent& rhs) = default;
	virtual ~RigidBody2DComponent() = default;

	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser& document) override;

	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;
	void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator);
	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator);

	void Inspect() override;

///////////////////////////////////////////////////////////////////////////////
	// Function Setting and Getting only

	void SetVelocity(Vector3 velocity);
	void SetFiction(float value);
	void SetMass(float mass);
	void SetType(bool type);

	RigidBody2DComponent* CloneComponent() { return new RigidBody2DComponent(*this); }
};

#endif
