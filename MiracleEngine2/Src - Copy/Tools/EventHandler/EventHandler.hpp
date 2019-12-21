#pragma once

#include "PrecompiledHeaders.h"
#include "EventHandler.h"
#include "Engine/EngineSystems.h"

template<typename T>
void EventHandler::SendLogicEventMessage(size_t uId, EventMessageType type, T message)
{
	GameObject* gameObject = EngineSystems::GetInstance()._gameObjectFactory->getObjectlist()[uId];

	if (!gameObject)
		return;

	Map_ScriptList list = EngineSystems::GetInstance()._gameObjectFactory->getObjectScript(gameObject);

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

template<typename T>
void EventHandler::SendSystemEventMessage(size_t uId, EventMessageType type, ComponentId message, T message2)
{
	if (type == EventMessageType::COMPONENT_CREATION)
	{
		if (message2 == nullptr)
			return;

		switch (message)
		{
		case ComponentId::IDENTITY_COMPONENT:
			break;
		case ComponentId::TRANSFORM_COMPONENT:
			MyTransformManager.AddObject(uId, message2);
			break;
		case ComponentId::GRAPHICS_COMPONENT:
//			MyGraphicsSystem.AddSpriteObject(uId, message2);
			break;
		case ComponentId::ANIMATION_COMPONENT:
		//	MyGraphicsSystem.AddAnimationObject(uId, message2);
			break;
		case ComponentId::CAMERA_COMPONENT:
			//MyTransformManager.AddObject(uId, message2);
			break;
		case ComponentId::FONT_COMPONENT:
			//MyGraphicsSystem.AddFontObject(uId, message2);
			break;
		case ComponentId::RIGIDBODY_COMPONENT:
			MyRigidbodyManager.AddObject(uId, message2);
			break;
		case ComponentId::CIRCLECOLLIDER_COMPONENT:
			MyCollisionManager.AddObject(uId, message2);
			break;
		case ComponentId::BOXCOLLIDER_COMPONENT:
			MyCollisionManager.AddObject(uId, message2);
			break;
		case ComponentId::EDGECOLLIDER_COMPONENT:
			MyCollisionManager.AddObject(uId, message2);
			break;
		case ComponentId::LOGIC_COMPONENT:
			MyLogicSystem.AddObject(uId, message2);
			break;
		case ComponentId::AUDIO_COMPONENT:
			MyAudioSystem.AddObject(uId, message2);
			break;
		case ComponentId::BUTTON_COMPONENT:
			MyButtonManager.AddObject(uId, message2);
			break;
		case ComponentId::TILEMAP_COMPONENT:
			break;
		case ComponentId::COUNTCOMPONENT:
			break;
		default:
			break;
		}
	}
	else if (type == EventMessageType::COMPONENT_DELETION)
	{
		switch (message)
		{
		case ComponentId::IDENTITY_COMPONENT:
			break;
		case ComponentId::TRANSFORM_COMPONENT:
			MyTransformManager.RemoveObject(uId);
			break;
		case ComponentId::GRAPHICS_COMPONENT:
			//MyGraphicsSystem.RemoveSpriteObject(uId);
			break;
		case ComponentId::ANIMATION_COMPONENT:
			//MyGraphicsSystem.RemoveAnimationObject(uId);
			break;
		case ComponentId::CAMERA_COMPONENT:
			//MyTransformManager.AddObject(uId, message2);
			break;
		case ComponentId::FONT_COMPONENT:
			//MyGraphicsSystem.RemoveFontObject(uId);
			break;
		case ComponentId::RIGIDBODY_COMPONENT:
			MyRigidbodyManager.RemoveObject(uId);
			break;
		case ComponentId::CIRCLECOLLIDER_COMPONENT:
			MyCollisionManager.RemoveObject(uId);
			break;
		case ComponentId::BOXCOLLIDER_COMPONENT:
			MyCollisionManager.RemoveObject(uId);
			break;
		case ComponentId::EDGECOLLIDER_COMPONENT:
			MyCollisionManager.RemoveObject(uId);
			break;
		case ComponentId::LOGIC_COMPONENT:
			MyLogicSystem.RemoveObject(uId);
			break;
		case ComponentId::AUDIO_COMPONENT:
			MyAudioSystem.RemoveObject(uId);
			break;
		case ComponentId::BUTTON_COMPONENT:
			MyButtonManager.RemoveObject(uId);
			break;
		case ComponentId::TILEMAP_COMPONENT:
			break;
		case ComponentId::COUNTCOMPONENT:
			break;
		default:
			break;
		}
	}
	else if (type == EventMessageType::OBJECT_DELETION)
	{
	MyGameObjectFactory.getObjectlist()[uId]->DestoryGameObject();
	}

	(void)message;
	(void)message2;
}
