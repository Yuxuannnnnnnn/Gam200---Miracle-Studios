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

#include "MathLib/SYMath.h"
#include "PhysicSystem/CollisionTable.h"
#include "GameObjectComponents/IComponent.h"

enum class ColliderType{
    
    NONE_COLLIDER = 0,
    BOX_COLLIDER = 1,
    CIRCLE_COLLIDER = 2,
	EDGE_COLLIDER = 3,

  };

class ICollider2D : public IComponent
{
public:
	unsigned _type;
	unsigned _tag;
	unsigned _layer;

	bool _trigger;
	bool _attachedRigidboy;
	bool _componentEnable;

public:
	ICollider2D();
	ICollider2D(const ICollider2D& rhs) = default;
	virtual ~ICollider2D() {}

	ICollider2D& operator=(const ICollider2D& rhs) = delete;

	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser& document) override;
	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;
	void Inspect() override;

///////////////////////////////////////////////////////////////////////////////
	// Function Setting and Getting only
};

#endif
