#pragma once

#include "PrecompiledHeaders.h"
#include "EventHandler.h"

template<typename T>
void EventHandler::SendLogicEventMessage(size_t uId, EventMessageType type, T message)
{
	if (!GetComponentMap(Logic)[uId])
		return;

	for (auto it : MyLogicSystem.GetScriptList(uId))
	{
		switch (type)
		{
		case EventMessageType::ON_COLLISION_TRIGGER:
			it->OnCollision2DTrigger(message);
			break;
		case EventMessageType::ON_COLLISION_STAY:
			it->OnCollision2DStay(message);
			break;
		case EventMessageType::ON_COLLISION_EXIT:
			it->OnCollision2DExit(message);
			break;
		case EventMessageType::ON_TRIGGER_ENTER:
			it->OnTrigger2DEnter(message);
			break;
		case EventMessageType::ON_TRIGGER_STAY:
			it->OnTrigger2DStay(message);
			break;
		case EventMessageType::ON_TRIGGER_EXIT:
			it->OnTrigger2DExit(message);
			break;
		case EventMessageType::ON_MOUSE_CLICK_DOWN:
			it->OnMouseDown();
			break;
		case EventMessageType::ON_MOUSE_CLICK_DRAG:
			it->OnMouseDrag();
			break;
		case EventMessageType::ON_MOUSE_CLICK_UP:
			it->OnMouseUp();
			break;
		case EventMessageType::ON_MOUSE_HOVER_ENTER:
			it->OnMouseEnter();
			break;
		case EventMessageType::ON_MOUSE_HOVER_OVER:
			it->OnMouseOver();
			break;
		case EventMessageType::ON_MOUSE_HOVER_EXIT:
			it->OnMouseExit();
			break;
		default:
			break;
		}
	}
	(void)message;
}

template<typename T>
void EventHandler::SendSystemEventMessage(size_t uId, EventMessageType type, ComponentId message, T message2)
{
	if (type == EventMessageType::COMPONENT_CREATION)
	{
		if (message2 == nullptr)
			return;

		switch (message)
		{
		default:
			break;
		}
	}
	else if (type == EventMessageType::COMPONENT_DELETION)
	{
		switch (message)
		{
		default:
			break;
		}
	}
	else if (type == EventMessageType::OBJECT_DELETION)
	{
	//MyGameObjectFactory.getObjectlist()[uId]->DestoryGameObject();
	}

	(void)message;
	(void)message2;
}
