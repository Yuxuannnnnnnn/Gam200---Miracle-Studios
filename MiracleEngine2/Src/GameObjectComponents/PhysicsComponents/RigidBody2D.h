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
#include "../GraphicComponents/TransformComponent.h"
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

	/*float _angularVelocity;
	float _angularForce;*/

	float _mass;
	float _fictionVal;
	bool _static;
	bool _componentEnable;

	TransformComponent* _transform;

protected:
	

public:

	RigidBody2D(GameObject* parent, size_t uId, IComponentSystem* component = nullptr);

	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser& document) override;
	void Inspect() override;

	// Constructor
	RigidBody2D(TransformComponent* transform = nullptr);
	virtual ~RigidBody2D() {};
	

	// A copy empty shell object
	RigidBody2D(const RigidBody2D& rhs);
	//No replication of class object
	RigidBody2D& operator= (const RigidBody2D& rhs) = delete;

	void UpdateVec(double dt);
	void UpdatePos(double dt);

	void Draw();

	void StopVelocity();
	void AddForce(Vector3 forceDir, float force);
	void AddForwardForce(float force);
	void SetFiction(float value);
	void SetMass(float mass);
	void SetType(bool type);

};

#endif