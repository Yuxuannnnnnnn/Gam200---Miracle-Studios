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

#include "GameObjectComponents/IComponentSystem.h"
#include "GraphicsSystem/DebugRenderer.h"

#include "MathLib/SYMath.h"

enum ColliderType{
    
    NONE_COLLIDER = 0,
    BOX_COLLIDER = 1,
    CIRCLE_COLLIDER = 2,
	LINE_COLLIDER = 3,

  };

class Collider2D : public IComponentSystem
{
public:
	unsigned _type;
	unsigned _layer;

	bool _enable;
	bool _trigger;
public:
  
	Collider2D() :
		_type{ NONE_COLLIDER },
		_layer{ 0 },
		_enable{ true },
		_trigger{ true }
	{
	}

	virtual ~Collider2D() {}

	virtual void Draw() {};

	virtual void update() {}

	std::string ComponentName() const override
	{
		return "ColliderComponent";
	}
};

#endif
