///////////////////////////////////////////////////////////////////////////////////////
//
//	EdgeCollider2DComponent.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _EDGE_COLLIDER_2D_H
#define _EDGE_COLLIDER_2D_H

#include "ICollider2D.h"
#include "SystemPhysics/BoundingEdge.h"

class EdgeCollider2DComponent : public Collider2D
{
public:
	BEdge _data;

	Vector3 _center;
	Vector3	_start;
	Vector3	_end;

public:
	EdgeCollider2DComponent();
	EdgeCollider2DComponent(const EdgeCollider2DComponent& rhs) = default;
	virtual ~EdgeCollider2DComponent() = default;

	EdgeCollider2DComponent& operator= (const EdgeCollider2DComponent& rhs) = delete;

	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser& document) override
	{
		if (document.HasMember("EdgeCollider2DComponent") && document["EdgeCollider2DComponent"].IsBool())
			SetEnable(document["EdgeCollider2DComponent"].GetBool());

		Collider2D::SerialiseComponent(document);

		if (document.HasMember("Collider2D.E.Center") && document["Collider2D.E.Center"].IsArray())
		{
			if (document["Collider2D.E.Center"][0].IsFloat() && document["Collider2D.E.Center"][1].IsFloat())
				_center = Vector3{ document["Collider2D.E.Center"][0].GetFloat(), document["Collider2D.E.Center"][1].GetFloat(), 1 };

			if (document["Collider2D.E.Center"].Size() == 3)
			{
				_center.SetZ(document["Collider2D.E.Center"][2].GetFloat());
			}
		}

		if (document.HasMember("Collider2D.E.Start") && document["Collider2D.E.Start"].IsArray())
		{
			if (document["Collider2D.E.Start"][0].IsFloat() && document["Collider2D.E.Start"][1].IsFloat())
				_start = Vector3{ document["Collider2D.E.Start"][0].GetFloat(), document["Collider2D.E.Start"][1].GetFloat(), 1 };

			if (document["Collider2D.E.Start"].Size() == 3)
			{
				_start.SetZ(document["Collider2D.E.Start"][2].GetFloat());
			}
		}

		if (document.HasMember("Collider2D.E.End") && document["Collider2D.E.End"].IsArray())
		{
			if (document["Collider2D.E.End"][0].IsFloat() && document["Collider2D.E.End"][1].IsFloat())
				_end = Vector3{ document["Collider2D.E.End"][0].GetFloat(), document["Collider2D.E.End"][1].GetFloat(), 1 };

			if (document["Collider2D.E.End"].Size() == 3)
			{
				_end.SetZ(document["Collider2D.E.End"][2].GetFloat());
			}
		}

	}
	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override
	{
		rapidjson::Value value;

		value.SetBool(GetEnable());
		prototypeDoc.AddMember("EdgeCollider2DComponent", value);

		Collider2D::DeSerialiseComponent(prototypeDoc);

		value.SetArray();
		value.PushBack(rapidjson::Value(_center.GetX()).Move(), prototypeDoc.Allocator());
		value.PushBack(rapidjson::Value(_center.GetY()).Move(), prototypeDoc.Allocator());
		value.PushBack(rapidjson::Value(_center.GetZ()).Move(), prototypeDoc.Allocator());
		prototypeDoc.AddMember("Collider2D.E.Center", value);

		value.SetArray();
		value.PushBack(rapidjson::Value(_start.GetX()).Move(), prototypeDoc.Allocator());
		value.PushBack(rapidjson::Value(_start.GetY()).Move(), prototypeDoc.Allocator());
		value.PushBack(rapidjson::Value(_start.GetZ()).Move(), prototypeDoc.Allocator());
		prototypeDoc.AddMember("Collider2D.E.Start", value);

		value.SetArray();
		value.PushBack(rapidjson::Value(_end.GetX()).Move(), prototypeDoc.Allocator());
		value.PushBack(rapidjson::Value(_end.GetY()).Move(), prototypeDoc.Allocator());
		value.PushBack(rapidjson::Value(_end.GetZ()).Move(), prototypeDoc.Allocator());
		prototypeDoc.AddMember("Collider2D.E.End", value);
	}
	void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
	{
		rapidjson::Value value;

		value.SetBool(GetEnable());
		prototypeDoc.AddMember("EdgeCollider2DComponent", value, allocator);

		Collider2D::DeSerialiseComponent(prototypeDoc, allocator);

		value.SetArray();
		value.PushBack(rapidjson::Value(_center.GetX()).Move(), allocator);
		value.PushBack(rapidjson::Value(_center.GetY()).Move(), allocator);
		value.PushBack(rapidjson::Value(_center.GetZ()).Move(), allocator);
		prototypeDoc.AddMember("Collider2D.E.Center", value, allocator);

		value.SetArray();
		value.PushBack(rapidjson::Value(_start.GetX()).Move(), allocator);
		value.PushBack(rapidjson::Value(_start.GetY()).Move(), allocator);
		value.PushBack(rapidjson::Value(_start.GetZ()).Move(), allocator);
		prototypeDoc.AddMember("Collider2D.E.Start", value, allocator);

		value.SetArray();
		value.PushBack(rapidjson::Value(_end.GetX()).Move(), allocator);
		value.PushBack(rapidjson::Value(_end.GetY()).Move(), allocator);
		value.PushBack(rapidjson::Value(_end.GetZ()).Move(), allocator);
		prototypeDoc.AddMember("Collider2D.E.End", value, allocator);

	}
	void Inspect() override;
	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
	{
		EdgeCollider2DComponent* protoIColliderCom = dynamic_cast<EdgeCollider2DComponent*>(protoCom);

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
		rapidjson::Value start;
		rapidjson::Value end;

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

		if (protoIColliderCom->_start != _start)
		{
			start.SetArray();
			addComponentIntoSceneFile = true;
			start.PushBack(rapidjson::Value(_start._x), allocator);
			start.PushBack(rapidjson::Value(_start._y), allocator);
			start.PushBack(rapidjson::Value(_start._z), allocator);
		}

		if (protoIColliderCom->_end != _end)
		{
			end.SetArray();
			addComponentIntoSceneFile = true;
			end.PushBack(rapidjson::Value(_end._x), allocator);
			end.PushBack(rapidjson::Value(_end._y), allocator);
			end.PushBack(rapidjson::Value(_end._z), allocator);
		}

		if (addComponentIntoSceneFile)	//If anyone of component data of obj is different from Prototype
		{
			if (!enable.IsNull())
				value.AddMember("EdgeCollider2DComponent", enable, allocator);
			else
				value.AddMember("EdgeCollider2DComponent", protoIColliderCom->GetEnable(), allocator);

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
				value.AddMember("Collider2D.E.Center", center, allocator);
			}

			if (!start.IsNull())
			{
				value.AddMember("Collider2D.E.Start", start, allocator);
			}

			if (!end.IsNull())
			{
				value.AddMember("Collider2D.E.End", end, allocator);
			}

		}
	}

///////////////////////////////////////////////////////////////////////////////
	// Function Setting and Getting only
	EdgeCollider2DComponent* CloneComponent() { return new EdgeCollider2DComponent(*this); }
};

//struct Ray
//{
//	Vector3	m_pt0;
//	Vector3	m_dir;
//};


#endif
