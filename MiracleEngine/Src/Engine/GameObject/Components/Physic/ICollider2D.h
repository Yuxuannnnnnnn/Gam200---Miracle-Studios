///////////////////////////////////////////////////////////////////////////////////////
//
//	ICollider2D.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _COLLIDER_2D_H
#define _COLLIDER_2D_H

#include "Tools/MathLib/Math.h"
#include "SystemPhysics/CollisionTable.h"
#include "../../IComponent.h"

enum class ColliderType{
    
    NONE_COLLIDER = 0,
    BOX_COLLIDER = 1,
    CIRCLE_COLLIDER = 2,
	EDGE_COLLIDER = 3,

  };

class Collider2D : public IComponent
{
public:
	int _type;
	int _tag;
	int _layer;
	bool _trigger;


	bool _attachedRigidboy;
public:


	Collider2D();
	Collider2D(const Collider2D& rhs) = default;
	virtual ~Collider2D() {}

	Collider2D& operator=(const Collider2D& rhs) = delete;

	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser& document) override
	{
		if (document.HasMember("ColliderTypeId") && document["ColliderTypeId"].IsInt())	//Checks if the variable exists in .Json file
			_type = document["ColliderTypeId"].GetUint();

		if (document.HasMember("ColliderTag") && document["ColliderTag"].IsInt())	//Checks if the variable exists in .Json file
			_tag = document["ColliderTag"].GetUint();

		if (document.HasMember("ColliderTrigger") && document["ColliderTrigger"].IsBool())	//Checks if the variable exists in .Json file
			_trigger = document["ColliderTrigger"].GetBool();
	}


	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override
	{
		rapidjson::Value value;

		value.SetInt(_type);
		prototypeDoc.AddMember("ColliderTypeId", value);

		value.SetInt(_tag);
		prototypeDoc.AddMember("ColliderTag", value);

		value.SetBool(_trigger);
		prototypeDoc.AddMember("ColliderTrigger", value);
	}

	void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator);


	void Inspect() override;

///////////////////////////////////////////////////////////////////////////////
	// Function Setting and Getting only
};

#endif
