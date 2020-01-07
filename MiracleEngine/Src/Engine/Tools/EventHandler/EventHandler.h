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

#include "../ISingleton.h"

#include "GameObject/IComponent.h"
#include "GameObject/Components/Physic/ICollider2D.h"
#include "GameObject/Components/Logic/IScript.h"

#include <unordered_set>
#include <unordered_map>

enum class EventMessageType {
	ON_COLLISION_TRIGGER,
	ON_COLLISION_STAY,
	ON_COLLISION_EXIT,

	ON_TRIGGER_ENTER,
	ON_TRIGGER_STAY,
	ON_TRIGGER_EXIT,

	ON_MOUSE_CLICK_DOWN,
	ON_MOUSE_CLICK_DRAG,
	ON_MOUSE_CLICK_UP,

	ON_MOUSE_HOVER_ENTER,
	ON_MOUSE_HOVER_OVER,
	ON_MOUSE_HOVER_EXIT,

	COMPONENT_CREATION,
	COMPONENT_DELETION,

	OBJECT_DELETION
};

class EventHandler : public ISingleton<EventHandler> 
{
	typedef std::pair<Collider2D*, Collider2D*> ColliderPair;
	typedef std::unordered_map<size_t, ColliderPair> Collider2DList;
	typedef std::unordered_map<size_t, Collider2DList> Collider2DQueue;

	typedef std::pair<ComponentId, IComponent*> ComponentPair;
	typedef std::unordered_multimap<size_t, ComponentPair> NewComponentQueue;
	typedef std::unordered_multimap<size_t, ComponentId> DeleteComponentQueue;

	typedef std::unordered_set<size_t> IdQueue;

private:
	Collider2DQueue _Collide2DQuePre;
	Collider2DQueue _Collide2DQueCurr;

	Collider2DQueue _Trigger2DQuePre;
	Collider2DQueue _Trigger2DQueCurr;

	IdQueue _MouseClickQuePre;
	IdQueue _MouseClickQueCurr;

	IdQueue _MouseHoverQuePre;
	IdQueue _MouseHoverQueCurr;

	NewComponentQueue _NewComponentQueue;
	DeleteComponentQueue _DeleteComponentQueue;

	IdQueue _DeleteObjectQueue;

public:
	EventHandler() {}
	virtual ~EventHandler();

	void BroadcastCollisionEvents();
	void BroadcastInputEvents();
	void BroadcastObjectEvents();

	void AddCollided2DEvent(Collider2D* first, Collider2D* second);
	void AddTriggered2DEvent(Collider2D* first, Collider2D* second);
	void AddMouseClickEvent(size_t id);
	void AddMouseHoverEvent(size_t id);
	void AddDeletionEvent(size_t id, ComponentId cId = ComponentId::CT_Count);
	void AddCreationEvent(size_t id, ComponentId cId, IComponent* ptr);

	void ClearAllEvents();

private:
	void BroadcastCollided2DEvents();
	void BroadcastTriggered2DEvents();
	void BroadcastMouseClickEvents();
	void BroadcastMouseHoverEvents();
	void BroadcastObjectDeletionEvents();

	void BroadcastComponentDeletionEvents();
	void BroadcastComponentCreationEvents();

	void RemoveCollider2DEvent(Collider2DQueue& queue, size_t first, size_t second = 0);

	template<typename T>
	void SendLogicEventMessage(size_t uId, EventMessageType type, T message = 0);

	template<typename T>
	void SendSystemEventMessage(size_t uId, EventMessageType type, ComponentId message = ComponentId::COUNTCOMPONENT, T message2 = 0);
};

#define MyEventHandler EventHandler::GetInstance()

#include "EventHandler.hpp"

#endif
