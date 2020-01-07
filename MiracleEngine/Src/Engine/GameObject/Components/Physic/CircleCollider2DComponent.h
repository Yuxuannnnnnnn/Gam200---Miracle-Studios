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

class CircleCollider2DComponent : public Collider2D
{
public:
	Vector3	mCenPos;
	float	mRadius;

public:
	CircleCollider2DComponent();
	CircleCollider2DComponent(const CircleCollider2DComponent& rhs) = default;
	virtual ~CircleCollider2DComponent() = default;

	CircleCollider2DComponent& operator=(const CircleCollider2DComponent & rhs) = delete;

	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser& document) override;
	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;
	void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
	{
		rapidjson::Value value;

		value.SetBool(true);
		prototypeDoc.AddMember("CircleCollider2DComponent", rapidjson::Value(true), allocator);

		Collider2D::DeSerialiseComponent(prototypeDoc, allocator);
	}
	void Inspect() override;
	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
	{
		Collider2D* protoIColliderCom = dynamic_cast<Collider2D*>(protoCom);

		bool addComponentIntoSceneFile = false;
		rapidjson::Value type;
		rapidjson::Value tag;
		rapidjson::Value trigger;

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


		if (addComponentIntoSceneFile)	//If anyone of component data of obj is different from Prototype
		{
			value.AddMember("BoxCollider2D", rapidjson::Value(true), allocator);

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
		}
	}


///////////////////////////////////////////////////////////////////////////////
	// Function Setting and Getting only
	IComponent* CloneComponent() { return nullptr; }
};

#endif
