///////////////////////////////////////////////////////////////////////////////////////
//
//	BoxCollider2DComponent.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _BOX_COLLIDER_2D_H
#define _BOX_COLLIDER_2D_H

#include "ICollider2D.h"

typedef unsigned int outcode;
#define TOP 0x0008 //1000
#define BOTTOM 0x0004 //0100
#define RIGHT 0x0002 //0010
#define LEFT 0x0001 //0001

enum class OutCode_Type {
	TOP_LEFT = 1001,
	TOP_CENTER = 1000,
	TOP_RIGHT = 1010,
	CENTER_LEFT = 0001,
	CENTER = 0000,
	CENTER_RIGHT = 0010,
	BOTTOM_LEFT = 0101,
	BOTTOM_CENTER = 0100,
	BOTTOM_RIGHT = 0110
};

class BoxCollider2DComponent : public Collider2D // renderer
{
public:
	// AABB
	Vector3		mMaxPos;	// Bottom-right point with maximum x and y values
	Vector3		mMinPos;	// Top-left point with minimum x and y values

	//OBB
	Vector3 mOrigin; // corner[0].dot(axis[a])
	Vector3 mCorner[4]; // Corners of the box, where 0 is the lower left.
	Vector3 mAxis[2];  // Two edges of the box extended away from corner[0].

	Vector3 mScale;
	float mAngle;

public:
	BoxCollider2DComponent();
	BoxCollider2DComponent(const BoxCollider2DComponent& rhs) = default;
	virtual ~BoxCollider2DComponent() = default;
	
	BoxCollider2DComponent& operator=(const BoxCollider2DComponent& rhs) = delete;
	
	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser& document) override
	{
		Collider2D::SerialiseComponent(document);
	}


	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override
	{
		rapidjson::Value value;

		value.SetBool(true);
		prototypeDoc.AddMember("BoxCollider2DComponent", rapidjson::Value(true));

		Collider2D::DeSerialiseComponent(prototypeDoc);
	}

	void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
	{
		rapidjson::Value value;

		value.SetBool(true);
		prototypeDoc.AddMember("BoxCollider2DComponent", rapidjson::Value(true), allocator);

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
			value.AddMember("BoxCollider2DComponent", rapidjson::Value(true), allocator);

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
	BoxCollider2DComponent* CloneComponent() { return new BoxCollider2DComponent(*this); }
};

#endif

