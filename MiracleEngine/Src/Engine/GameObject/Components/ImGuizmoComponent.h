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

#include "Physic/BoxCollider2DComponent.h"

class PickingCollider : public BoxCollider2DComponent
{
public:
	bool _picked;

public:
	PickingCollider() : _picked{ false } {}
	virtual ~PickingCollider() = default;

	//No replication of class object
	PickingCollider(const PickingCollider& rhs) = delete;
	PickingCollider& operator= (const PickingCollider& rhs) = delete;

	IComponent* CloneComponent() { return nullptr; }
};

#endif

