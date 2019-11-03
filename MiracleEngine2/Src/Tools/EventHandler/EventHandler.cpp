///////////////////////////////////////////////////////////////////////////////////////
//
//	EventHandler.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#include "PrecompiledHeaders.h"
#include "EventHandler.h"

EventHandler::~EventHandler()
{
	ClearAllQueue();
}

void EventHandler::UpdateEvent()
{
	UpdateCollided2DEvent();
	UpdateTriggered2DEvent();

	UpdateMouseClickEvent();
	UpdateMouseHoverEvent();
}

void EventHandler::UpdateCollided2DEvent()
{
	Collide2DQueue tempQueue;

	for (auto it = _Collide2DQueCurr.begin(); it != _Collide2DQueCurr.end();)
	{
		bool incement = true;

		auto range = _Collide2DQuePre.equal_range(it->first);

		for (auto it2 = range.first; it2 != range.second; ++it2)
		{
			if (it->second == it2->second)
			{

				/*Coin* object = dynamic_cast<Coin*>(it->first->_gameObject);
				if (object)
					object->OnCollision2DStay(it->second);*/
				SendEventMessage(it->first->GetParentPtr(), EventMessageType::ON_COLLISION_STAY, it->second);

				tempQueue.insert(*it);

				RemoveCollided2DEvent(_Collide2DQuePre, it2->first, it2->second);
				RemoveCollided2DEvent(_Collide2DQueCurr, it->first, it->second);
				it = _Collide2DQueCurr.begin();
				incement = false;
				break;
			}
		}

		if (incement)
			++it;
	}

	for (auto it = _Collide2DQuePre.begin(); it != _Collide2DQuePre.end();)
	{
		/*Coin* object = dynamic_cast<Coin*>(it->first->_gameObject);
		if (object)
			object->OnCollision2DExit(it->second);*/
		//object->OnCollisionExit(it->second);
		SendEventMessage(it->first->GetParentPtr(), EventMessageType::ON_COLLISION_EXIT, it->second);

		RemoveCollided2DEvent(_Collide2DQuePre, it->first, it->second);

		it = _Collide2DQuePre.begin();
	}



	for (auto it = _Collide2DQueCurr.begin(); it != _Collide2DQueCurr.end();)
	{


		/*Coin* object = dynamic_cast<Coin*>(it->first->_gameObject);
		if (object)
			object->OnCollision2DTrigger(it->second);*/
		//object->OnCollisionTrigger(it->second);
		SendEventMessage(it->first->GetParentPtr(), EventMessageType::ON_COLLISION_TRIGGER, it->second);

		tempQueue.insert(*it);

		RemoveCollided2DEvent(_Collide2DQueCurr, it->first, it->second);

		it = _Collide2DQueCurr.begin();
	}

	_Collide2DQuePre.clear();

	_Collide2DQuePre = tempQueue;

	_Collide2DQueCurr.clear();
}


void EventHandler::AddCollided2DEvent(Collider2D& first, Collider2D& second)
{
	_Collide2DQueCurr.insert({ &first ,&second });
}

void EventHandler::RemoveCollided2DEvent(Collide2DQueue& queue, Collider2D* first, Collider2D* second)
{
	auto range = queue.equal_range(first);

	for (auto it2 = range.first; it2 != range.second;)
	{
		if (it2->second == second)
		{
			queue.erase(it2);
			range = queue.equal_range(first);
			it2 = range.first;
		}
		else
		{
			++it2;
		}
	}
}

void EventHandler::UpdateTriggered2DEvent()
{
	Collide2DQueue tempQueue;

	for (auto it = _Trigger2DQueCurr.begin(); it != _Trigger2DQueCurr.end();)
	{

		bool incement = true;

		auto range = _Trigger2DQuePre.equal_range(it->first);

		for (auto it2 = range.first; it2 != range.second; ++it2)
		{
			if (it->second == it2->second)
			{
				/*Coin* object = dynamic_cast<Coin*>(it->first->_gameObject);
				if (object)
					object->OnCollision2DStay(it->second);*/
				SendEventMessage(it->first->GetParentPtr(), EventMessageType::ON_TRIGGER_STAY, it->second);

				tempQueue.insert(*it);

				RemoveTriggered2DEvent(_Trigger2DQuePre, it2->first, it2->second);
				RemoveTriggered2DEvent(_Trigger2DQueCurr, it->first, it->second);
				it = _Trigger2DQueCurr.begin();
				incement = false;
				break;
			}
		}

		if (incement)
			++it;
	}

	for (auto it = _Trigger2DQuePre.begin(); it != _Trigger2DQuePre.end();)
	{

		/*Coin* object = dynamic_cast<Coin*>(it->first->_gameObject);
		if (object)
			object->OnCollision2DExit(it->second);*/
			//object->OnCollisionExit(it->second);
		SendEventMessage(it->first->GetParentPtr(), EventMessageType::ON_TRIGGER_EXIT, it->second);

		RemoveTriggered2DEvent(_Trigger2DQuePre, it->first, it->second);

		it = _Trigger2DQuePre.begin();
	}



	for (auto it = _Trigger2DQueCurr.begin(); it != _Trigger2DQueCurr.end();)
	{

		/*Coin* object = dynamic_cast<Coin*>(it->first->_gameObject);
		if (object)
			object->OnCollision2DTrigger(it->second);*/
			//object->OnCollisionTrigger(it->second);
		SendEventMessage(it->first->GetParentPtr(), EventMessageType::ON_TRIGGER_ENTER, it->second);

		tempQueue.insert(*it);

		RemoveTriggered2DEvent(_Trigger2DQueCurr, it->first, it->second);

		it = _Trigger2DQueCurr.begin();
	}

	_Trigger2DQuePre.clear();

	_Trigger2DQuePre = tempQueue;

	_Trigger2DQueCurr.clear();
}

void EventHandler::AddTriggered2DEvent(Collider2D& first, Collider2D& second)
{
	_Trigger2DQueCurr.insert({ &first ,&second });
}

void EventHandler::RemoveTriggered2DEvent(Collide2DQueue& queue, Collider2D* first, Collider2D* second)
{
	auto range = queue.equal_range(first);

	for (auto it2 = range.first; it2 != range.second;)
	{
		if (it2->second == second)
		{
			queue.erase(it2);
			range = queue.equal_range(first);
			it2 = range.first;
		}
		else
		{
			++it2;
		}
	}
}

void EventHandler::UpdateMouseClickEvent()
{
	MouseQueue tempQueue;

	for (auto it = _MouseClickQueCurr.begin(); it != _MouseClickQueCurr.end();)
	{
		MouseQueue::iterator it2 = _MouseClickQuePre.find(*it);

		if (it2 != _MouseClickQuePre.end())
		{
			tempQueue.insert(*it);
		}
	}

	for (auto it = tempQueue.begin(); it != tempQueue.end();)
	{
		/*Coin* object = dynamic_cast<Coin*>(it->first->_gameObject);
		if (object)
			object->OnCollision2DStay(it->second);*/

		RemoveMouseHoverEvent(_MouseClickQuePre, *it);
		RemoveMouseHoverEvent(_MouseClickQueCurr, *it);
	}


	for (auto it = _MouseClickQuePre.begin(); it != _MouseClickQuePre.end();)
	{

		/*Coin* object = dynamic_cast<Coin*>(it->first->_gameObject);
		if (object)
			object->OnCollision2DExit(it->second);*/
			//object->OnCollisionExit(it->second);
	}



	for (auto it = _MouseClickQueCurr.begin(); it != _MouseClickQueCurr.end();)
	{
		/*Coin* object = dynamic_cast<Coin*>(it->first->_gameObject);
		if (object)
			object->OnCollision2DTrigger(it->second);*/
			//object->OnCollisionTrigger(it->second);

		tempQueue.insert(*it);
	}

	_MouseClickQuePre.clear();

	_MouseClickQuePre = tempQueue;

	_MouseClickQueCurr.clear();
}

void EventHandler::AddMouseClickEvent(size_t id)
{
	_MouseClickQueCurr.insert(id);
}

void EventHandler::RemoveMouseClickEvent(MouseQueue& queue, size_t id)
{
	queue.erase(id);
}

void EventHandler::UpdateMouseHoverEvent()
{
	MouseQueue tempQueue;

	for (auto it = _MouseHoverQueCurr.begin(); it != _MouseHoverQueCurr.end();)
	{
		MouseQueue::iterator it2 = _MouseClickQuePre.find(*it);

		if (it2 != _MouseClickQuePre.end())
		{
			tempQueue.insert(*it);
		}
	}

	for (auto it = tempQueue.begin(); it != tempQueue.end();)
	{
		/*Coin* object = dynamic_cast<Coin*>(it->first->_gameObject);
		if (object)
			object->OnCollision2DStay(it->second);*/

		RemoveMouseHoverEvent(_MouseClickQuePre, *it);
		RemoveMouseHoverEvent(_MouseHoverQueCurr, *it);
	}


	for (auto it = _MouseClickQuePre.begin(); it != _MouseClickQuePre.end();)
	{

		/*Coin* object = dynamic_cast<Coin*>(it->first->_gameObject);
		if (object)
			object->OnCollision2DExit(it->second);*/
			//object->OnCollisionExit(it->second);
	}



	for (auto it = _MouseHoverQueCurr.begin(); it != _MouseHoverQueCurr.end();)
	{
		/*Coin* object = dynamic_cast<Coin*>(it->first->_gameObject);
		if (object)
			object->OnCollision2DTrigger(it->second);*/
			//object->OnCollisionTrigger(it->second);

		tempQueue.insert(*it);
	}

	_MouseClickQuePre.clear();

	_MouseClickQuePre = tempQueue;

	_MouseHoverQueCurr.clear();
}

void EventHandler::AddMouseHoverEvent(size_t id)
{
	_MouseHoverQueCurr.insert(id);
}

void EventHandler::RemoveMouseHoverEvent(MouseQueue& queue, size_t id)
{
	queue.erase(id);
}

void EventHandler::ClearAllQueue()
{
	_Collide2DQuePre.clear();
	_Collide2DQueCurr.clear();
	
	_Trigger2DQuePre.clear();
	_Trigger2DQueCurr.clear();

	_MouseClickQuePre.clear();
	_MouseClickQueCurr.clear();

	_MouseHoverQuePre.clear();
	_MouseHoverQueCurr.clear();
}