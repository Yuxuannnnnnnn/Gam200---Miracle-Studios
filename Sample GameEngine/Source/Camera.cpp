///////////////////////////////////////////////////////////////////////////////////////
//
//	Camera.cpp
//	Authors: Chris Peters
//	Copyright 2010, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#include "Precompiled.h"
#include "Camera.h"
#include "Graphics.h"

namespace Framework
{
	Camera::Camera()
	{
		transform = NULL;
		GRAPHICS->CurrentCamera = this;
	}

	Camera::~Camera()
	{
		if( GRAPHICS->CurrentCamera == this )
			GRAPHICS->CurrentCamera = NULL;
	}

	void Camera::Initialize()
	{
		transform = GetOwner()->has(Transform);
	}


}