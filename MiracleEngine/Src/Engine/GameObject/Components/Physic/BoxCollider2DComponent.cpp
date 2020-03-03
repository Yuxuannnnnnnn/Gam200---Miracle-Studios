//
//	BoxCollider2DComponent.cpp
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#include "PrecompiledHeaders.h"
#include "BoxCollider2DComponent.h"

BoxCollider2DComponent::BoxCollider2DComponent() :
	_center{ Vec3{0.f,0.f,1.f} },
	_scale{ Vec3{1.f,1.f,1.f} },
	_angle{ 0.f }
{
	_type = (unsigned)ColliderType::BOX_COLLIDER;
}

std::string BoxCollider2DComponent::ComponentName() const
{
	return std::string("BoxCollider Component");
}



void BoxCollider2DComponent::Inspect()
{
	Collider2D::Inspect();

	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();


	ImGui::InputFloat2("Box Center Pos X, Y", _center.m);
	ImGui::Spacing();
	ImGui::SliderFloat2("Box Center X Y", _center.m, -1000, 1000);


	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();

	ImGui::InputFloat2("Box Scale X, Y", _scale.m);
	ImGui::Spacing();
	ImGui::SliderFloat2("Box Scale X Y", _scale.m, 1, 500);

	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();

	float DegAngle = RadToDeg(_angle);
	ImGui::InputFloat("Box Rotation Angle", &DegAngle);
	ImGui::Spacing();
	ImGui::SliderFloat("Box Angle", &DegAngle, -180, 180);
	_angle = DegToRad(DegAngle);

	ImGui::Spacing();
}

void BoxCollider2DComponent::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("BoxCollider2DComponent") && document["BoxCollider2DComponent"].IsBool())
		SetEnable(document["BoxCollider2DComponent"].GetBool());

	Collider2D::SerialiseComponent(document);

	if (document.HasMember("Collider2D.B.Center") && document["Collider2D.B.Center"].IsArray())
	{
		if (document["Collider2D.B.Center"][0].IsFloat() && document["Collider2D.B.Center"][1].IsFloat())
			_center = Vector3{ document["Collider2D.B.Center"][0].GetFloat(), document["Collider2D.B.Center"][1].GetFloat(), 1 };

		if (document["Collider2D.B.Center"].Size() == 3)
		{
			_center.SetZ(document["Collider2D.B.Center"][2].GetFloat());
		}
	}

	if (document.HasMember("Collider2D.B.Scale") && document["Collider2D.B.Scale"].IsArray())
	{
		if (document["Collider2D.B.Scale"][0].IsFloat() && document["Collider2D.B.Scale"][1].IsFloat())
			_scale = Vector3{ document["Collider2D.B.Scale"][0].GetFloat(), document["Collider2D.B.Scale"][1].GetFloat(), 1 };

		if (document["Collider2D.B.Scale"].Size() == 3)
		{
			_scale.SetZ(document["Collider2D.B.Scale"][2].GetFloat());
		}
	}


	if (document.HasMember("Collider2D.B.Angle") && document["Collider2D.B.Angle"].IsFloat())	//Checks if the variable exists in .Json file
	{
		_angle = (document["Collider2D.B.Angle"].GetFloat());
	}
}


void BoxCollider2DComponent::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
	rapidjson::Value value;

	value.SetBool(GetEnable());
	prototypeDoc.AddMember("BoxCollider2DComponent", value);

	Collider2D::DeSerialiseComponent(prototypeDoc);

	value.SetArray();
	value.PushBack(rapidjson::Value(_center.GetX()).Move(), prototypeDoc.Allocator());
	value.PushBack(rapidjson::Value(_center.GetY()).Move(), prototypeDoc.Allocator());
	value.PushBack(rapidjson::Value(_center.GetZ()).Move(), prototypeDoc.Allocator());
	prototypeDoc.AddMember("Collider2D.B.Center", value);

	value.SetArray();
	value.PushBack(rapidjson::Value(_scale.GetX()).Move(), prototypeDoc.Allocator());
	value.PushBack(rapidjson::Value(_scale.GetY()).Move(), prototypeDoc.Allocator());
	value.PushBack(rapidjson::Value(_scale.GetZ()).Move(), prototypeDoc.Allocator());
	prototypeDoc.AddMember("Collider2D.B.Scale", value);

	value.SetFloat(_angle);
	prototypeDoc.AddMember("Collider2D.B.Angle", value);
}

void BoxCollider2DComponent::DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
{
	rapidjson::Value value;

	value.SetBool(GetEnable());
	prototypeDoc.AddMember("BoxCollider2DComponent", value, allocator);

	Collider2D::DeSerialiseComponent(prototypeDoc, allocator);

	value.SetArray();
	value.PushBack(rapidjson::Value(_center.GetX()).Move(), allocator);
	value.PushBack(rapidjson::Value(_center.GetY()).Move(), allocator);
	value.PushBack(rapidjson::Value(_center.GetZ()).Move(), allocator);
	prototypeDoc.AddMember("Collider2D.B.Center", value, allocator);

	value.SetArray();
	value.PushBack(rapidjson::Value(_scale.GetX()).Move(), allocator);
	value.PushBack(rapidjson::Value(_scale.GetY()).Move(), allocator);
	value.PushBack(rapidjson::Value(_scale.GetZ()).Move(), allocator);
	prototypeDoc.AddMember("Collider2D.B.Scale", value, allocator);

	value.SetFloat(_angle);
	prototypeDoc.AddMember("Collider2D.B.Angle", value, allocator);
}

void BoxCollider2DComponent::DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
{
	BoxCollider2DComponent* protoIColliderCom = dynamic_cast<BoxCollider2DComponent*>(protoCom);

	if (!protoIColliderCom)
	{
		DeSerialiseComponent(value, allocator);
		return;
	}

	bool addComponentIntoSceneFile = false;
	rapidjson::Value enable;
	rapidjson::Value type;
	rapidjson::Value tag;
	rapidjson::Value trigger;

	rapidjson::Value center;
	rapidjson::Value scale;
	rapidjson::Value angle;


	if (protoIColliderCom->GetEnable() != this->GetEnable())
	{
		addComponentIntoSceneFile = true;
		enable.SetBool(GetEnable());
	}

	if (protoIColliderCom->_type != _type)	//If audiofile of Object is diff from prototype
	{
		addComponentIntoSceneFile = true;
		type.SetInt(_type);
	}

	if (protoIColliderCom->_tag != _tag)	//If audiofile of Object is diff from prototype
	{
		addComponentIntoSceneFile = true;
		tag.SetInt(_tag);
	}

	if (protoIColliderCom->_trigger != _trigger)	//If audiofile of Object is diff from prototype
	{
		addComponentIntoSceneFile = true;
		trigger.SetBool(_trigger);
	}

	if (protoIColliderCom->_center != _center)
	{
		center.SetArray();
		addComponentIntoSceneFile = true;
		center.PushBack(rapidjson::Value(_center._x), allocator);
		center.PushBack(rapidjson::Value(_center._y), allocator);
		center.PushBack(rapidjson::Value(_center._z), allocator);
	}

	if (protoIColliderCom->_scale != _scale)
	{
		scale.SetArray();
		addComponentIntoSceneFile = true;
		scale.PushBack(rapidjson::Value(_scale._x), allocator);
		scale.PushBack(rapidjson::Value(_scale._y), allocator);
		scale.PushBack(rapidjson::Value(_scale._z), allocator);
	}

	if (protoIColliderCom->_angle != _angle)
	{
		addComponentIntoSceneFile = true;
		angle.SetFloat(_angle);
	}


	if (addComponentIntoSceneFile)	//If anyone of component data of obj is different from Prototype
	{
		if (!enable.IsNull())
			value.AddMember("BoxCollider2DComponent", enable, allocator);
		else
			value.AddMember("BoxCollider2DComponent", protoIColliderCom->GetEnable(), allocator);

		if (!type.IsNull())
		{
			value.AddMember("ColliderTypeId", type, allocator);
		}

		if (!tag.IsNull())
		{
			value.AddMember("ColliderTag", tag, allocator);
		}

		if (!trigger.IsNull())
		{
			value.AddMember("ColliderTrigger", trigger, allocator);
		}

		if (!center.IsNull())
		{
			value.AddMember("Collider2D.B.Center", center, allocator);
		}

		if (!scale.IsNull())
		{
			value.AddMember("Collider2D.B.Scale", scale, allocator);
		}

		if (!angle.IsNull())
		{
			value.AddMember("Collider2D.B.Angle", angle, allocator);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
	// Function Setting and Getting only