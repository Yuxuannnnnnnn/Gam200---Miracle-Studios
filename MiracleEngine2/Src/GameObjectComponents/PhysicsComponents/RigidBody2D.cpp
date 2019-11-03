///////////////////////////////////////////////////////////////////////////////////////
//
//	RigidBody2D.cpp
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#include "PrecompiledHeaders.h"
#include "RigidBody2D.h"
#include "GraphicsSystem/DebugRenderer.h"

RigidBody2D::RigidBody2D(TransformComponent* transform) :
	_velocity{},
	_appliedForce{},
	_direction{ 1.f,0.f,0.f },
	_position{},
	_angle{ 0.f },
	_mass{ 1.f },
	_fictionVal{ 0.f },
	_static{ true },
	_componentEnable{ true },
	_transform{ transform }
{
}

RigidBody2D::RigidBody2D(const RigidBody2D& rhs) :
	_velocity{ rhs ._velocity },
	_appliedForce{ rhs._appliedForce },
	_direction{ rhs._direction },
	_position{ rhs._position},
	_angle{ rhs._angle },
	_mass{ rhs._mass },
	_fictionVal{ rhs._fictionVal },
	_static{ rhs._static },
	_componentEnable{ rhs._componentEnable },
	_transform{ nullptr }
{
}

void RigidBody2D::UpdateVec(double dt)
{
	if (_static)
		return;

	Vector3 newVel{ 0.f, 0.f , 0.f};

	// newVel = a * dt + currVel;;
	newVel = _appliedForce * _mass;
	newVel = _velocity + newVel * (float)dt;

	// newVel = newVel * firction;
	newVel = newVel * (1.f - _fictionVal);

	_velocity = newVel;

	_appliedForce = Vector3{ 0.f,0.f,0.f };

	Draw();
}

void RigidBody2D::UpdatePos(double dt)
{
	if (_static)
		return;

	// newPos = newVel * dt + currPos;
	_transform->GetPos() += _velocity * (float)dt;
}

void RigidBody2D::Draw()
{
	Vector3 newVel = _velocity.Normalized();
	float length = _velocity.SquaredLength();

	if (length > 100.f)
		length = 100.f;

	DebugRenderer::GetInstance().DrawLine(_position._x, _position._y, _position._x + newVel._x * length, _position._y + newVel._y * length);
}

void RigidBody2D::StopVelocity()
{
	Vec3Zero(_velocity);
}

void RigidBody2D::AddForce(Vector3 force)
{
	Vec3Add(_appliedForce, _appliedForce, force);
}

void RigidBody2D::RemoveForce(Vector3 force)
{
	_appliedForce -= force;
}

void RigidBody2D::SetFiction(float value)
{
	_fictionVal = value;
}

void RigidBody2D::SetMass(float mass)
{
	_mass = mass;
}

void RigidBody2D::SetType(bool type)
{
	_static = type;
}