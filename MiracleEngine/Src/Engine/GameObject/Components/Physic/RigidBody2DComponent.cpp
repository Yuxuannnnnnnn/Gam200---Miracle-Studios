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
	_static{ true }
{}

std::string RigidBody2DComponent::ComponentName() const
{
	return std::string("RigidBody Component");
}

void RigidBody2DComponent::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("RigidBody2DComponent") && document["RigidBody2DComponent"].IsBool())
		SetEnable(document["RigidBody2DComponent"].GetBool());

	if (document.HasMember("Mass") && document["Mass"].IsFloat())	//Checks if the variable exists in .Json file
		_mass = document["Mass"].GetFloat();

	if (document.HasMember("Friction") && document["Friction"].IsFloat())
		_fictionVal = document["Friction"].GetFloat();

	if (document.HasMember("Static") && document["Static"].IsBool())
		_static = document["Static"].GetBool();

}


void RigidBody2DComponent::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
	rapidjson::Value value;

	value.SetBool(GetEnable());
	prototypeDoc.AddMember("RigidBody2DComponent", value);

	value.SetFloat(_mass);
	prototypeDoc.AddMember("Mass", value);

	value.SetFloat(_fictionVal);
	prototypeDoc.AddMember("Friction", value);

	value.SetBool(_static);
	prototypeDoc.AddMember("Static", value);
}

void RigidBody2DComponent::DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
{
	rapidjson::Value value;

	value.SetBool(GetEnable());
	prototypeDoc.AddMember("RigidBody2DComponent", value, allocator);

	value.SetFloat(_mass);
	prototypeDoc.AddMember("Mass", value, allocator);

	value.SetFloat(_fictionVal);
	prototypeDoc.AddMember("Friction", value, allocator);

	value.SetBool(_static);
	prototypeDoc.AddMember("Static", value, allocator);
}

void RigidBody2DComponent::DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
{
	RigidBody2DComponent* protoIColliderCom = dynamic_cast<RigidBody2DComponent*>(protoCom);


	if (!protoIColliderCom)
	{
		DeSerialiseComponent(value, allocator);
		return;
	}

	bool addComponentIntoSceneFile = false;
	rapidjson::Value  enable;
	rapidjson::Value  mass;
	rapidjson::Value  fictionVal;
	rapidjson::Value  stat;

	if (protoIColliderCom->GetEnable() != this->GetEnable())
	{
		addComponentIntoSceneFile = true;
		enable.SetBool(GetEnable());
	}


	if (protoIColliderCom->_mass != _mass)	//If audiofile of Object is diff from prototype
	{
		addComponentIntoSceneFile = true;
		mass.SetFloat(_mass);
	}

	if (protoIColliderCom->_fictionVal != _fictionVal)	//If audiofile of Object is diff from prototype
	{
		addComponentIntoSceneFile = true;
		fictionVal.SetFloat(_fictionVal);
	}

	if (protoIColliderCom->_static != _static)	//If audiofile of Object is diff from prototype
	{
		addComponentIntoSceneFile = true;
		stat.SetBool(_static);
	}


	if (addComponentIntoSceneFile)	//If anyone of component data of obj is different from Prototype
	{
		if (!enable.IsNull())
			value.AddMember("RigidBody2DComponent", enable, allocator);
		else
			value.AddMember("RigidBody2DComponent", protoIColliderCom->GetEnable(), allocator);

		if (!mass.IsNull())
		{
			value.AddMember("Mass", mass, allocator);
		}

		if (!fictionVal.IsNull())
		{
			value.AddMember("Friction", fictionVal, allocator);
		}

		if (!stat.IsNull())
		{
			value.AddMember("Static", stat, allocator);
		}
	}
}


void RigidBody2DComponent::Inspect()
{
	IComponent::Inspect();

	ImGui::Spacing();
	ImGui::Checkbox("Static", &_static);

	ImGui::Spacing();
	ImGui::InputFloat2("Velocity X, Y, Z", _velocity.m);

	ImGui::Spacing();
	ImGui::InputFloat2("Direction X, Y, Z", _direction.m);

	ImGui::Spacing();
	ImGui::InputFloat2("Applied Force X, Y, Z", _appliedForce.m);

	ImGui::Spacing();
	ImGui::InputFloat("Mass", &_mass);

	ImGui::Spacing();
	ImGui::InputFloat("Friction Value", &_fictionVal);

	ImGui::Spacing();

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

