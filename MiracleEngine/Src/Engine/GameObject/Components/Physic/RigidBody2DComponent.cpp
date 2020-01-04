///////////////////////////////////////////////////////////////////////////////////////
//
//	RigidBody2D.cpp
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#include "PrecompiledHeaders.h"
#include "RigidBody2DComponent.h"

RigidBody2D::RigidBody2D() :
	_velocity{},
	_appliedForce{},
	_direction{ 0.f,1.f,0.f },
	_mass{ 1.f },
	_fictionVal{ 0.f },
	_static{ true },
	_componentEnable{ true }
{}

std::string RigidBody2D::ComponentName() const
{
	return std::string("RigidBody Component");
}


///////////////////////////////////////////////////////////////////////////////
	// Function Setting and Getting only

void RigidBody2D::SetVelocity(Vector3 velocity)
{
	_velocity = velocity;
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

