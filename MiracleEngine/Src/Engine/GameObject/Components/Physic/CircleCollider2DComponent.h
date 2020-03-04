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

	void SerialiseComponent(Serialiser& document) override;

	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;

	void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator);
	
	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator);

	void Inspect() override;
///////////////////////////////////////////////////////////////////////////////
	// Function Setting and Getting only
	CircleCollider2DComponent* CloneComponent() { return new CircleCollider2DComponent(*this); }
};

#endif
