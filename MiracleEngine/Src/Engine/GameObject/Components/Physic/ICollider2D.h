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
	unsigned _type;
	unsigned _tag;
	unsigned _layer;

	bool _trigger;
	bool _attachedRigidboy;
	bool _componentEnable;

public:
	Collider2D();
	Collider2D(const Collider2D& rhs) = default;
	virtual ~Collider2D() {}

	Collider2D& operator=(const Collider2D& rhs) = delete;

	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser& document) override;
	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;
	void Inspect() override;

///////////////////////////////////////////////////////////////////////////////
	// Function Setting and Getting only
};

#endif
