///////////////////////////////////////////////////////////////////////////////////////
//
//	IMouseHandler.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _IMOUSE_HANDLER_H
#define _IMOUSE_HANDLER_H

#include "SystemInput/InputSystem.h"

class IMouseHandler
{
public:
	InputSystem* _input;

	IMouseHandler();

	const Vec3& GetMousePos() const;

	virtual void OnMouseDown() {}
	virtual void OnMouseDrag() {}
	virtual void OnMouseUp() {}

	virtual void OnMouseEnter() {}
	virtual void OnMouseOver() {}
	virtual void OnMouseExit() {}

	virtual ~IMouseHandler() {}
};

#endif