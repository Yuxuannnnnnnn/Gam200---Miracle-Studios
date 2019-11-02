///////////////////////////////////////////////////////////////////////////////////////
//
//	PickingCollider.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _PICKING_COLLIDER_H
#define _PICKING_COLLIDER_H

#include "PhysicsComponents/BoxCollider2D.h"

class PickingCollider : public BoxCollider2D
{
public:
	// Constructor
	PickingCollider() = delete;
	PickingCollider(TransformComponent* transform = nullptr) : BoxCollider2D(transform) {}
	virtual ~PickingCollider() {}

	//No replication of class object
	PickingCollider(const PickingCollider& rhs) = delete;
	PickingCollider& operator= (const PickingCollider& rhs) = delete;
};

#endif
