///////////////////////////////////////////////////////////////////////////////////////
//
//	EventHandler.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _EVENT_HANDLER_H
#define _EVENT_HANDLER_H

#include "../../ISingleton.h"

#include "GameObjectComponents/PhysicsComponents/Collider2D.h"

#include <unordered_set>
#include <unordered_map>

class EventHandler : public ISingleton<EventHandler> {

private:
	typedef std::unordered_multimap<Collider2D*, Collider2D*> Collide2DQueue;
	typedef std::unordered_set<size_t> MouseQueue;

	Collide2DQueue _Collide2DQuePre;
	Collide2DQueue _Collide2DQueCurr;

	Collide2DQueue _Trigger2DQuePre;
	Collide2DQueue _Trigger2DQueCurr;

	MouseQueue _MouseClickQuePre;
	MouseQueue _MouseClickQueCurr;

	MouseQueue _MouseHoverQuePre;
	MouseQueue _MouseHoverQueCurr;

public:
	EventHandler() {}
	virtual ~EventHandler();

	void UpdateEvent();

	void UpdateCollided2DEvent();
	void AddCollided2DEvent(Collider2D& first, Collider2D& second);

	void UpdateTriggered2DEvent();
	void AddTriggered2DEvent(Collider2D& first, Collider2D& second);

	void UpdateMouseClickEvent();
	void AddMouseClickEvent(size_t id);

	void UpdateMouseHoverEvent();
	void AddMouseHoverEvent(size_t id);

private:
	void RemoveCollided2DEvent(Collide2DQueue& queue, Collider2D* first, Collider2D* second);
	void RemoveTriggered2DEvent(Collide2DQueue& queue, Collider2D* first, Collider2D* second);

	void RemoveMouseClickEvent(MouseQueue& queue, size_t id);
	void RemoveMouseHoverEvent(MouseQueue& queue, size_t id);

	void ClearAllQueue();
};

#endif
