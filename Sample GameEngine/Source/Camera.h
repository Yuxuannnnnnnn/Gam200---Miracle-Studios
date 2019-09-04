///////////////////////////////////////////////////////////////////////////////////////
///
///	\file Camera.h
///	Defines Camera Game Component
///	
///	Authors: Chris Peters
///	Copyright 2010, Digipen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////////////
#pragma once //Makes sure this header is only included once

#include "Engine.h"
#include "Sprite.h"

namespace Framework
{	
	///Simple orthographic camera for viewing the game world.
	///Depends on Transform.
	class Camera : public GameComponent
	{
	public:
		Camera();
		~Camera();
		virtual void Initialize();
		Transform * transform;
	};

}
