///////////////////////////////////////////////////////////////////////////////////////
//
//	RigidBody2DComponent.cpp
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#include "PrecompiledHeaders.h"
#include "RigidBody2DComponent.h"

RigidBody2DComponent::RigidBody2DComponent() :
	_velocity{},
	_appliedForce{},
	_direction{ 0.f,1.f,0.f },
	_mass{ 1.f },
	_fictionVal{ 0.f },
	_static{ true },
	_componentEnable{ true }
{}

std::string RigidBody2DComponent::ComponentName() const
{
	return std::string("RigidBody Component");
}


///////////////////////////////////////////////////////////////////////////////
	// Function Setting and Getting only

void RigidBody2DComponent::SetVelocity(Vector3 velocity)
{
	_velocity = velocity;
}

void RigidBody2DComponent::SetFiction(float value)
{
	_fictionVal = value;
}

void RigidBody2DComponent::SetMass(float mass)
{
	_mass = mass;
}

void RigidBody2DComponent::SetType(bool type)
{
	_static = type;
}

