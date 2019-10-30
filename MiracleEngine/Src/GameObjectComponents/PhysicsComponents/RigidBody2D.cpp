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

RigidBody2D::RigidBody2D() :
	_velocity{},
	_appliedForce{},
	_direction{ 1.f,0.f,0.f },
	_position{},
	_angle{ 0.f },
	_mass{ 1.f },
	_fictionVal{ 0.f },
	_static{ true },
	_enable{ true }

{
}

void RigidBody2D::UpdateVec(double dt)
{
	if (_static || !_enable)
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
	if (_static || !_enable)
		return;

	// newPos = newVel * dt + currPos;
	_position += _velocity * (float)dt;
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

void RigidBody2D::SetEnable(bool enable)
{
	_enable = enable;
}