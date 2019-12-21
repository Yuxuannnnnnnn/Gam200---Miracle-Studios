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
#include "../GameObjectComponents/PhysicsComponents/ICollider2D.h"

class IColliderHandler
{
public:
	virtual void OnCollision2DTrigger(ICollider2D* other) { (void)other; }
	virtual void OnCollision2DStay(ICollider2D* other) { (void)other; }
	virtual void OnCollision2DExit(ICollider2D* other) { (void)other; }

	virtual void OnTrigger2DEnter(ICollider2D* other) { (void)other; }
	virtual void OnTrigger2DStay(ICollider2D* other) { (void)other; }
	virtual void OnTrigger2DExit(ICollider2D* other) { (void)other; }

	virtual ~IColliderHandler() {}
};

#endif
