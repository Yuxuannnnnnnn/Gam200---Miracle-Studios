///////////////////////////////////////////////////////////////////////////////////////
//
//	CircleCollider2DComponent.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _CIRCLE_COLLIDER_2D_H
#define _CIRCLE_COLLIDER_2D_H

#include "ICollider2D.h"
#include "SystemPhysics/BoundingCircle.h"

class CircleCollider2DComponent : public Collider2D
{
public:
	BCircle _data;

	Vector3	_center;
	float	_radius;

public:
	CircleCollider2DComponent();
	CircleCollider2DComponent(const CircleCollider2DComponent& rhs) = default;
	virtual ~CircleCollider2DComponent() = default;

	CircleCollider2DComponent& operator=(const CircleCollider2DComponent & rhs) = delete;

	std::string ComponentName() const override;

	void SerialiseComponent(Serialiser& document) override
	{
		if (document.HasMember("CircleCollider2DComponent") && document["CircleCollider2DComponent"].IsBool())
			SetEnable(document["CircleCollider2DComponent"].GetBool());

		Collider2D::SerialiseComponent(document);

		if (document.HasMember("Collider2D.C.Center") && document["Collider2D.C.Center"].IsArray())
		{
			if (document["Collider2D.C.Center"][0].IsFloat() && document["Collider2D.C.Center"][1].IsFloat())
				_center = Vector3{ document["Collider2D.C.Center"][0].GetFloat(), document["Collider2D.C.Center"][1].GetFloat(), 1 };

			if (document["Collider2D.C.Center"].Size() == 3)
			{
				_center.SetZ(document["Collider2D.C.Center"][2].GetFloat());
			}
		}


		if (document.HasMember("Collider2D.C.Radius") && document["Collider2D.C.Radius"].IsFloat())	//Checks if the variable exists in .Json file
		{
			_radius = (document["Collider2D.C.Radius"].GetFloat());
		}
	}

	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override
	{
		rapidjson::Value value;

		value.SetBool(GetEnable());
		prototypeDoc.AddMember("CircleCollider2DComponent", value);

		Collider2D::DeSerialiseComponent(prototypeDoc);

		value.SetArray();
		value.PushBack(rapidjson::Value(_center.GetX()).Move(), prototypeDoc.Allocator());
		value.PushBack(rapidjson::Value(_center.GetY()).Move(), prototypeDoc.Allocator());
		value.PushBack(rapidjson::Value(_center.GetZ()).Move(), prototypeDoc.Allocator());
		prototypeDoc.AddMember("Collider2D.C.Center", value);


		value.SetFloat(_radius);
		prototypeDoc.AddMember("Collider2D.C.Radius", value);
	}

	void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
	{
		rapidjson::Value value;

		value.SetBool(GetEnable());
		prototypeDoc.AddMember("CircleCollider2DComponent", value, allocator);

		Collider2D::DeSerialiseComponent(prototypeDoc, allocator);

		value.SetArray();
		value.PushBack(rapidjson::Value(_center.GetX()).Move(), allocator);
		value.PushBack(rapidjson::Value(_center.GetY()).Move(), allocator);
		value.PushBack(rapidjson::Value(_center.GetZ()).Move(), allocator);
		prototypeDoc.AddMember("Collider2D.C.Center", value, allocator);


		value.SetFloat(_radius);
		prototypeDoc.AddMember("Collider2D.C.Radius", value, allocator);
	}
	void Inspect() override;
	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
	{
		CircleCollider2DComponent* protoIColliderCom = dynamic_cast<CircleCollider2DComponent*>(protoCom);

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
		rapidjson::Value radius;

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

		if (protoIColliderCom->_radius != _radius)
		{
			addComponentIntoSceneFile = true;
			radius.SetFloat(_radius);
		}


		if (addComponentIntoSceneFile)	//If anyone of component data of obj is different from Prototype
		{
			if (!enable.IsNull())
				value.AddMember("CircleCollider2DComponent", enable, allocator);
			else
				value.AddMember("CircleCollider2DComponent", protoIColliderCom->GetEnable(), allocator);

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
				value.AddMember("Collider2D.C.Center", center, allocator);
			}

			if (!radius.IsNull())
			{
				value.AddMember("Collider2D.C.Radius", radius, allocator);
			}
		}
	}


///////////////////////////////////////////////////////////////////////////////
	// Function Setting and Getting only
	CircleCollider2DComponent* CloneComponent() { return new CircleCollider2DComponent(*this); }
};

#endif
