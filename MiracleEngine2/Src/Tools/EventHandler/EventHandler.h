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
#include "GameObjectComponents/LogicComponents/IScript.h"
#include "Engine/EngineSystems.h"

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
	ON_MOUSE_HOVER_EXIT
};

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

	template<typename T>
	void SendEventMessage(GameObject* object, EventMessageType type, T message = 0)
	{
		Map_ScriptList list = EngineSystems::GetInstance()._gameObjectFactory->getObjectScript(object);

		for (auto it : list)
		{
			switch (type)
			{
			case EventMessageType::ON_COLLISION_TRIGGER:
				it.second->OnCollision2DTrigger(message);
				break;
			case EventMessageType::ON_COLLISION_STAY:
				it.second->OnCollision2DStay(message);
				break;
			case EventMessageType::ON_COLLISION_EXIT:
				it.second->OnCollision2DExit(message);
				break;
			case EventMessageType::ON_TRIGGER_ENTER:
				it.second->OnTrigger2DEnter(message);
				break;
			case EventMessageType::ON_TRIGGER_STAY:
				it.second->OnTrigger2DStay(message);
				break;
			case EventMessageType::ON_TRIGGER_EXIT:
				it.second->OnTrigger2DExit(message);
				break;
			case EventMessageType::ON_MOUSE_CLICK_DOWN:
				it.second->OnMouseDown();
				break;
			case EventMessageType::ON_MOUSE_CLICK_DRAG:
				it.second->OnMouseDrag();
				break;
			case EventMessageType::ON_MOUSE_CLICK_UP:
				it.second->OnMouseUp();
				break;
			case EventMessageType::ON_MOUSE_HOVER_ENTER:
				it.second->OnMouseEnter();
				break;
			case EventMessageType::ON_MOUSE_HOVER_OVER:
				it.second->OnMouseOver();
				break;
			case EventMessageType::ON_MOUSE_HOVER_EXIT:
				it.second->OnMouseExit();
				break;
			default:
				break;
			}

		}

		(void)message;
	}

	void ClearAllQueue();
};


#endif
