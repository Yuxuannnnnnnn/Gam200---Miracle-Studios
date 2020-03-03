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
	void SerialiseComponent(Serialiser& document) override;
	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;
	void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator);
	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator);

	void Inspect() override;
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
