///////////////////////////////////////////////////////////////////////////////////////
//
//	CircleCollider2D.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _CIRCLE_COLLIDER_2D_H
#define _CIRCLE_COLLIDER_2D_H

#include "ICollider2D.h"

class CircleCollider2D : public Collider2D
{
public:
	Vector3	mCenPos;
	float	mRadius;

public:
	CircleCollider2D();
	CircleCollider2D(const CircleCollider2D& rhs) = default;
	virtual ~CircleCollider2D() = default;

	CircleCollider2D& operator=(const CircleCollider2D & rhs) = delete;

	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser& document) override;
	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;
	void Inspect() override;
	void DeserialiseComponentSceneFile(IComponent* protoCom, DeSerialiser& SceneFile) 
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
			SceneFile.AddMember("BoxCollider2D", rapidjson::Value(true));

			if (!type.IsNull())
			{
				SceneFile.AddMember("ColliderTypeId", type);
			}

			if (!tag.IsNull())
			{
				SceneFile.AddMember("ColliderTag", tag);
			}

			if (!trigger.IsNull())
			{
				SceneFile.AddMember("ColliderTrigger", trigger);
			}
		}
	}


///////////////////////////////////////////////////////////////////////////////
	// Function Setting and Getting only

};

#endif
