///////////////////////////////////////////////////////////////////////////////////////
//
//	RigidBody2D.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////

#include "GameObjectComponents/IComponentSystem.h"
#include "MathLib/SYMath.h"

#ifndef _RIGIDBODY_2D_H
#define _RIGIDBODY_2D_H


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
	float _mass;		//serialised
	float _fictionVal;	//serialised
	bool _static;		//serialised
	bool _enable;

protected:
	TransformComponent* _transform;

public:

	RigidBody2D(GameObject* parent, size_t uId, IComponentSystem* component = nullptr);
	
	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser& document) override;
	void Inspect() override;

	virtual ~RigidBody2D() = default;
	RigidBody2D(TransformComponent * transform = nullptr);
	// A copy empty shell object
	RigidBody2D(const RigidBody2D& rhs);
	//No replication of class object
	RigidBody2D& operator= (const RigidBody2D& rhs) = delete;

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


};

#endif
