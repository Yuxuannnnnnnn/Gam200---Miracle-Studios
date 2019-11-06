///////////////////////////////////////////////////////////////////////////////////////
//
//	ButtonCollider.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _BUTTON_COLLIDER_H
#define _BUTTON_COLLIDER_H

#include "PhysicsComponents/BoxCollider2D.h"

class ButtonComponent : public BoxCollider2D
{
public:
	bool _pressed;

	// Constructor
	ButtonComponent() :_pressed{false}, BoxCollider2D(nullptr) {}
	virtual ~ButtonComponent() {}

	//No replication of class object
	ButtonComponent(const ButtonComponent& rhs) = delete;
	ButtonComponent& operator= (const ButtonComponent& rhs) = delete;
};

#endif
