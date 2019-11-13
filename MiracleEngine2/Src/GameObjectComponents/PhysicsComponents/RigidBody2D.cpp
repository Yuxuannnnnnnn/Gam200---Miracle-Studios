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


void RigidBody2D::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("Mass") && document["Mass"].IsFloat())	//Checks if the variable exists in .Json file
		_mass = document["Mass"].GetFloat();

	if (document.HasMember("Friction") && document["Friction"].IsFloat())
		_fictionVal = document["Friction"].GetFloat();

	if (document.HasMember("Static") && document["Static"].IsBool())
		_static = document["Static"].GetBool();

}

void RigidBody2D::Inspect()
{
	IComponentSystem::Inspect();

	ImGui::Spacing();
	ImGui::Checkbox("Static", &_static);

	ImGui::Spacing();
	ImGui::InputFloat3("Velocity X, Y, Z", _velocity.m);

	ImGui::Spacing();
	ImGui::InputFloat3("Direction X, Y, Z", _direction.m);

	ImGui::Spacing();
	ImGui::InputFloat3("Applied Force X, Y, Z", _appliedForce.m);

	ImGui::Spacing();
	ImGui::InputFloat("Mass", &_mass);

	ImGui::Spacing();
	ImGui::InputFloat("Friction Value", &_fictionVal);

	ImGui::Spacing();

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

