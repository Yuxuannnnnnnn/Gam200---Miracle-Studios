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

enum ColliderType{
    
    NONE_COLLIDER = 0,
    BOX_COLLIDER = 1,
    CIRCLE_COLLIDER = 2,
	LINE_COLLIDER = 3,

  };

namespace {

	const int	COLLISION_LEFT = 0x00000001;	//0001
	const int	COLLISION_RIGHT = 0x00000002;	//0010
	const int	COLLISION_TOP = 0x00000004;		//0100
	const int	COLLISION_BOTTOM = 0x00000008;	//1000

	const int	COLLISION_LEFT_BOTTOM = 0x00000010;	 //1 0000
	const int	COLLISION_RIGHT_BOTTOM = 0x0000020; //10 0000
}

class Collider2D : public IComponentSystem //: public DebugRenderer 
{
public:
	unsigned _type;
	unsigned _layer;

	bool _enable;

public:
  
	Collider2D() :
		_type{ NONE_COLLIDER },
		_layer{ 0 },
		_enable{ true }
	{
	}

	virtual ~Collider2D() {}

	virtual void Draw() {};

	virtual void update() {}


	void SnapToCell(int flag, Vector2 cellSize) 
	{
		(void)flag;
		(void)cellSize;
	}

	std::string ComponentName() const override
	{
		return "ColliderComponent";
	}
};

#endif
