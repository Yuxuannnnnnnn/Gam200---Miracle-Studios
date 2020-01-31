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

	bool _componentEnable;

public:
	RigidBody2DComponent();
	RigidBody2DComponent(const RigidBody2DComponent& rhs) = default;
	virtual ~RigidBody2DComponent() = default;

	RigidBody2DComponent& operator= (const RigidBody2DComponent& rhs) = delete;

	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser& document) override
	{
		if (document.HasMember("Mass") && document["Mass"].IsFloat())	//Checks if the variable exists in .Json file
			_mass = document["Mass"].GetFloat();

		if (document.HasMember("Friction") && document["Friction"].IsFloat())
			_fictionVal = document["Friction"].GetFloat();

		if (document.HasMember("Static") && document["Static"].IsBool())
			_static = document["Static"].GetBool();

	}


	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override
	{
		rapidjson::Value value;

		value.SetBool(true);
		prototypeDoc.AddMember("RigidBody2DComponent", rapidjson::Value(true));

		value.SetFloat(_mass);
		prototypeDoc.AddMember("Mass", value);

		value.SetFloat(_fictionVal);
		prototypeDoc.AddMember("Friction", value);

		value.SetBool(_static);
		prototypeDoc.AddMember("Static", value);
	}

	void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
	{
		rapidjson::Value value;

		value.SetBool(true);
		prototypeDoc.AddMember("RigidBody2DComponent", rapidjson::Value(true), allocator);

		value.SetFloat(_mass);
		prototypeDoc.AddMember("Mass", value, allocator);

		value.SetFloat(_fictionVal);
		prototypeDoc.AddMember("Friction", value, allocator);

		value.SetBool(_static);
		prototypeDoc.AddMember("Static", value, allocator);
	}

	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
	{
		RigidBody2DComponent* protoIColliderCom = dynamic_cast<RigidBody2DComponent*>(protoCom);

		bool addComponentIntoSceneFile = false;
		rapidjson::Value  mass;
		rapidjson::Value  fictionVal;
		rapidjson::Value  stat;

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
			value.AddMember("RigidBodyComponent", rapidjson::Value(true), allocator);

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


	void Inspect() override
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

	void SetVelocity(Vector3 velocity);
	void SetFiction(float value);
	void SetMass(float mass);
	void SetType(bool type);

	RigidBody2DComponent* CloneComponent() { return new RigidBody2DComponent(*this); }
};

#endif
