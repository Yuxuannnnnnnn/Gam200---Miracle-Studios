///////////////////////////////////////////////////////////////////////////////////////
//
//	IColliderHandler.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _ICOLLIDER_HANDLER_H
#define _ICOLLIDER_HANDLER_H
#include "../PhysicSystem/CollisionComponent/Collider2D.h"

class IColliderHandler
{
public:
	virtual void OnCollision2DTrigger(Collider2D* other) { (void)other; }
	virtual void OnCollision2DStay(Collider2D* other) { (void)other; }
	virtual void OnCollision2DExit(Collider2D* other) { (void)other; }

	virtual ~IColliderHandler() {}
};

#endif
