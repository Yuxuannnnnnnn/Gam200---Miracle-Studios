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

#include "../../IComponent.h"
#include "Tools/MathLib/Math.h"

enum class RIGIDBODY_TYPE {
	RB_STATIC = true,
	RB_DYNAMIC = false
};

class RigidBody2D : public IComponent
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
	RigidBody2D();
	RigidBody2D(const RigidBody2D& rhs) = default;
	virtual ~RigidBody2D() = default;

	RigidBody2D& operator= (const RigidBody2D& rhs) = delete;

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
		prototypeDoc.AddMember("RigidBodyComponent", rapidjson::Value(true));

		value.SetFloat(_mass);
		prototypeDoc.AddMember("Mass", value);

		value.SetFloat(_fictionVal);
		prototypeDoc.AddMember("Friction", value);

		value.SetBool(_static);
		prototypeDoc.AddMember("Static", value);
	}

	void DeserialiseComponentSceneFile(IComponent* protoCom, DeSerialiser& SceneFile) 
	{
		RigidBody2D* protoIColliderCom = dynamic_cast<RigidBody2D*>(protoCom);

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
			SceneFile.AddMember("RigidBodyComponent", rapidjson::Value(true));

			if (!mass.IsNull())
			{
				SceneFile.AddMember("Mass", mass);
			}

			if (!fictionVal.IsNull())
			{
				SceneFile.AddMember("Friction", fictionVal);
			}

			if (!stat.IsNull())
			{
				SceneFile.AddMember("Static", stat);
			}
		}
	}


	void Inspect() override
	{
		IComponent::Inspect();

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

	void SetVelocity(Vector3 velocity);
	void SetFiction(float value);
	void SetMass(float mass);
	void SetType(bool type);


};

#endif
