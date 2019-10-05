///////////////////////////////////////////////////////////////////////////////////////
//
//	Collider2D.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _COLLIDER_2D_H
#define _COLLIDER_2D_H

#include "MathLib/SYMath.h"
#include "GameObject.h"
#include "RigidBody2D.h"


enum ColliderType{
    
    NONE_COLLIDER,
    BOX_COLLIDER,
    CIRCLE_COLLIDER,
	LINE_COLLIDER
    
  };

namespace {

	const int	COLLISION_LEFT = 0x00000001;	//0001
	const int	COLLISION_RIGHT = 0x00000002;	//0010
	const int	COLLISION_TOP = 0x00000004;		//0100
	const int	COLLISION_BOTTOM = 0x00000008;	//1000

	const int	COLLISION_LEFT_BOTTOM = 0x00000010;	 //1 0000
	const int	COLLISION_RIGHT_BOTTOM = 0x0000020; //10 0000
}

class Collider2D //: public DebugRenderer 
{
public:
	GameObject* _gameObject;
	RigidBody2D* _body;

	ColliderType _type;
	unsigned _layer;

	bool _enable;

public:
  
	Collider2D() :
		_type{ NONE_COLLIDER },
		_layer{ 0 },
		_gameObject{ nullptr },
		_body{ nullptr },
		_enable{ true }
	{
	}

	virtual ~Collider2D() {}

	virtual void Draw() = 0;

	virtual void update() {}


	void SnapToCell(int flag, Vector2 cellSize) 
	{
		(void)flag;
		(void)cellSize;
	}
};

#endif
