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

#include "ISingleton.h"
#include "Collider2D.h"

#include <vector>
#include <map>

class EventHandler : public ISingleton<EventHandler> {

private:

	std::multimap<Collider2D*, Collider2D*> _collisionQueuePre;
	std::multimap<Collider2D*, Collider2D*> _collisionQueueCurr;
	std::multimap<Collider2D*, int> _staticCollsionQueue;

public:
	EventHandler() {}
	~EventHandler() {}

	void UpdateEvent();

	void UpdateCollisionEvent();
	void AddCollisionEvent(Collider2D& first, Collider2D& second);

	void RemoveCollisionEventPre(Collider2D* first, Collider2D* second);
	void RemoveCollisionEventCurr(Collider2D* first, Collider2D* second);

	void UpdateStaticCollisionEvent();
	void AddStaticCollisionEvent(Collider2D& first, int second);

	void ClearAllQueue();
};

#endif
