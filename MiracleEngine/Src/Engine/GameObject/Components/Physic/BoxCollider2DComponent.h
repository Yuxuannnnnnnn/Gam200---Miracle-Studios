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
#include "SystemPhysics/BoundingPolygon.h"

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
	BPolygon _data;

	Vector3 _center;
	Vector3 _scale;
	float _angle;

public:
	BoxCollider2DComponent();
	BoxCollider2DComponent(const BoxCollider2DComponent& rhs) = default;
	virtual ~BoxCollider2DComponent() = default;
	
	BoxCollider2DComponent& operator=(const BoxCollider2DComponent& rhs) = delete;
	
	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser& document) override;
	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;
	void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator);
	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator);

	virtual void Inspect() override;

///////////////////////////////////////////////////////////////////////////////
	// Function Setting and Getting only
	BoxCollider2DComponent* CloneComponent() { return new BoxCollider2DComponent(*this); }
};

#endif

