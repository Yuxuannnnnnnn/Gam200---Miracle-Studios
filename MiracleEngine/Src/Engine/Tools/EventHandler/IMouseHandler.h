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

class IMouseHandler
{
public:
	virtual void OnMouseDown() {}
	virtual void OnMouseDrag() {}
	virtual void OnMouseUp() {}

	virtual void OnMouseEnter() {}
	virtual void OnMouseOver() {}
	virtual void OnMouseExit() {}

	virtual ~IMouseHandler() {}
};

#endif