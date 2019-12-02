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
	ClearAllEvents();
}

void EventHandler::BroadcastCollisionEvents()
{
	BroadcastCollided2DEvents();
	BroadcastTriggered2DEvents();
}

void EventHandler::BroadcastInputEvents()
{
	BroadcastMouseClickEvents();
	BroadcastMouseHoverEvents();
}

void EventHandler::BroadcastObjectEvents()
{
	BroadcastComponentCreationEvents();
	BroadcastComponentDeletionEvents();
	BroadcastObjectDeletionEvents();
	
}


void EventHandler::AddCollided2DEvent(Collider2D* first, Collider2D* second)
{
	auto it = _Collide2DQueCurr.find(first->GetParentId());

	if (it == _Collide2DQueCurr.end())
	{
		//create a new pair;
		_Collide2DQueCurr.insert({ first->GetParentId(), Collider2DList{} });

		it = _Collide2DQueCurr.find(first->GetParentId());
	}
		
	// insert into the Collider2DList
	it->second.insert({ second->GetParentId(), ColliderPair(first ,second) });
}

void EventHandler::AddTriggered2DEvent(Collider2D* first, Collider2D* second)
{
	auto it = _Trigger2DQueCurr.find(first->GetParentId());

	if (it == _Trigger2DQueCurr.end())
	{
		//create a new pair;
		_Trigger2DQueCurr.insert({ first->GetParentId(), Collider2DList{} });

		it = _Trigger2DQueCurr.find(first->GetParentId());
	}

	// insert into the Collider2DList
	it->second.insert({ second->GetParentId(), ColliderPair(first ,second) });
}

void EventHandler::AddMouseClickEvent(size_t id)
{
	_MouseClickQueCurr.insert(id);
}

void EventHandler::AddMouseHoverEvent(size_t id)
{
	_MouseHoverQueCurr.insert(id);
}

void EventHandler::AddDeletionEvent(size_t id, ComponentId cId)
{
	if(cId == ComponentId::COUNTCOMPONENT)
		_DeleteObjectQueue.insert(id);

	_DeleteComponentQueue.insert({ id, cId });
}

void EventHandler::AddCreationEvent(size_t id, ComponentId cId, IComponentSystem* ptr)
{
	_NewComponentQueue.insert({ id, ComponentPair(cId, ptr) });
}

////////////////////////////////////////////////////////////////////////////////////

void EventHandler::BroadcastCollided2DEvents()
{
	Collider2DQueue tempQueue;

	for (auto it = _Collide2DQueCurr.begin(); it != _Collide2DQueCurr.end(); ++it)
	{
		auto it2 = _Collide2DQuePre.find(it->first);

		if (it2 != _Collide2DQuePre.end())
		{
			for (auto it3 = it->second.begin(); it3 != it->second.end(); ++it3)
			{
				auto it4 = it2->second.find(it3->first);

				if (it4 != it2->second.end())
				{
					auto it5 = tempQueue.find(it->first);

					if (it5 == tempQueue.end())
					{
						//create a new pair;
						tempQueue.insert({ it->first, Collider2DList{} });

						it5 = tempQueue.find(it->first);
					}
				
					// insert into the Collider2DList
					it5->second.insert({ it3->first, 
						ColliderPair(it3->second.first ,it3->second.second) });

				}
			}
		}	
	}

	for (auto it = tempQueue.begin(); it != tempQueue.end(); ++it)
	{
		for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
		{
			// Send ON_COLLISION_STAY
			SendLogicEventMessage(it->first, EventMessageType::ON_COLLISION_STAY, it2->second.second);

			RemoveCollider2DEvent(_Collide2DQuePre, it->first, it2->first);
			RemoveCollider2DEvent(_Collide2DQueCurr, it->first, it2->first);
		}
	}

	for (auto it = _Collide2DQuePre.begin(); it != _Collide2DQuePre.end(); ++it)
	{
		for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
		{
			// Send ON_COLLISION_EXIT
			SendLogicEventMessage(it->first, EventMessageType::ON_COLLISION_EXIT, it2->second.second);
		}
	}

	for (auto it = _Collide2DQueCurr.begin(); it != _Collide2DQueCurr.end(); ++it)
	{
		for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
		{
			// Send ON_COLLISION_TRIGGER
			SendLogicEventMessage(it->first, EventMessageType::ON_COLLISION_TRIGGER, it2->second.second);

			auto it3 = tempQueue.find(it->first);

			if (it3 == tempQueue.end())
			{
				//create a new pair;
				tempQueue.insert({ it->first, Collider2DList{} });

				it3 = tempQueue.find(it->first);
			}

			// insert into the Collider2DList
			it3->second.insert({ it2->first,
				ColliderPair(it2->second.first ,it2->second.second) });
		}
	}

	_Collide2DQuePre.clear();
	_Collide2DQueCurr.clear();

	_Collide2DQuePre = tempQueue;
}

void EventHandler::BroadcastTriggered2DEvents()
{
	Collider2DQueue tempQueue;

	for (auto it = _Trigger2DQueCurr.begin(); it != _Trigger2DQueCurr.end(); ++it)
	{
		auto it2 = _Trigger2DQuePre.find(it->first);

		if (it2 != _Trigger2DQuePre.end())
		{
			for (auto it3 = it->second.begin(); it3 != it->second.end(); ++it3)
			{
				auto it4 = it2->second.find(it3->first);

				if (it4 != it2->second.end())
				{
					auto it5 = tempQueue.find(it->first);

					if (it5 == tempQueue.end())
					{
						//create a new pair;
						tempQueue.insert({ it->first, Collider2DList{} });

						it5 = tempQueue.find(it->first);
					}

					// insert into the Collider2DList
					it5->second.insert({ it3->first,
						ColliderPair(it3->second.first ,it3->second.second) });

				}
			}
		}
	}

	for (auto it = tempQueue.begin(); it != tempQueue.end(); ++it)
	{
		for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
		{
			// Send ON_TRIGGER_STAY
			SendLogicEventMessage(it->first, EventMessageType::ON_TRIGGER_STAY, it2->second.second);

			RemoveCollider2DEvent(_Trigger2DQuePre, it->first, it2->first);
			RemoveCollider2DEvent(_Trigger2DQueCurr, it->first, it2->first);
		}
	}

	for (auto it = _Trigger2DQuePre.begin(); it != _Trigger2DQuePre.end(); ++it)
	{
		for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
		{
			// Send ON_TRIGGER_EXIT
			SendLogicEventMessage(it->first, EventMessageType::ON_TRIGGER_EXIT, it2->second.second);
		}
	}

	for (auto it = _Trigger2DQueCurr.begin(); it != _Trigger2DQueCurr.end(); ++it)
	{
		for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
		{
			// Send ON_TRIGGER_ENTER
			SendLogicEventMessage(it->first, EventMessageType::ON_TRIGGER_ENTER, it2->second.second);

			auto it3 = tempQueue.find(it->first);

			if (it3 == tempQueue.end())
			{
				//create a new pair;
				tempQueue.insert({ it->first, Collider2DList{} });

				it3 = tempQueue.find(it->first);
			}

			// insert into the Collider2DList
			it3->second.insert({ it2->first,
				ColliderPair(it2->second.first ,it2->second.second) });
		}
	}

	_Trigger2DQuePre.clear();
	_Trigger2DQueCurr.clear();

	_Trigger2DQuePre = tempQueue;
}

void EventHandler::BroadcastMouseClickEvents()
{
	IdQueue tempQueue;

	for (auto it = _MouseClickQueCurr.begin(); it != _MouseClickQueCurr.end(); ++it)
	{
		auto it2 = _MouseClickQuePre.find(*it);

		if (it2 != _MouseClickQuePre.end())
			tempQueue.insert(*it);
	}

	for (auto it = tempQueue.begin(); it != tempQueue.end(); it++)
	{
		// send ON_MOUSE_CLICK_DRAG
		SendLogicEventMessage(*it, EventMessageType::ON_MOUSE_CLICK_DRAG, nullptr);

		_MouseClickQuePre.erase(*it);
		_MouseClickQueCurr.erase(*it);
	}

	for (auto it = _MouseClickQuePre.begin(); it != _MouseClickQuePre.end(); ++it)
	{
		// send ON_MOUSE_CLICK_UP
		SendLogicEventMessage(*it, EventMessageType::ON_MOUSE_CLICK_UP, nullptr);
	}

	for (auto it = _MouseClickQueCurr.begin(); it != _MouseClickQueCurr.end(); ++it)
	{
		// send ON_MOUSE_CLICK_DOWN
		SendLogicEventMessage(*it, EventMessageType::ON_MOUSE_CLICK_DOWN, nullptr);

		tempQueue.insert(*it);
	}

	_MouseClickQuePre.clear();
	_MouseClickQueCurr.clear();

	_MouseClickQuePre = tempQueue;
}

void EventHandler::BroadcastMouseHoverEvents()
{
	IdQueue tempQueue;

	for (auto it = _MouseHoverQueCurr.begin(); it != _MouseHoverQueCurr.end(); ++it)
	{
		auto it2 = _MouseHoverQuePre.find(*it);

		if (it2 != _MouseHoverQuePre.end())
			tempQueue.insert(*it);
	}

	for (auto it = tempQueue.begin(); it != tempQueue.end(); it++)
	{
		// send ON_MOUSE_HOVER_OVER
		SendLogicEventMessage(*it, EventMessageType::ON_MOUSE_HOVER_OVER, nullptr);

		_MouseHoverQuePre.erase(*it);
		_MouseHoverQueCurr.erase(*it);
	}


	for (auto it = _MouseHoverQuePre.begin(); it != _MouseHoverQuePre.end(); ++it)
	{
		// send ON_MOUSE_HOVER_EXIT
		SendLogicEventMessage(*it, EventMessageType::ON_MOUSE_HOVER_EXIT, nullptr);
	}



	for (auto it = _MouseHoverQueCurr.begin(); it != _MouseHoverQueCurr.end(); ++it)
	{
		SendLogicEventMessage(*it, EventMessageType::ON_MOUSE_HOVER_ENTER, nullptr);

		tempQueue.insert(*it);
	}

	_MouseHoverQuePre.clear();
	_MouseHoverQueCurr.clear();

	_MouseHoverQuePre = tempQueue;
}

void EventHandler::BroadcastObjectDeletionEvents()
{
	for (auto it = _DeleteObjectQueue.begin(); it != _DeleteObjectQueue.end(); ++it)
	{
		SendSystemEventMessage(*it, EventMessageType::OBJECT_DELETION, nullptr, nullptr);

		RemoveCollider2DEvent(_Collide2DQuePre, *it);
		RemoveCollider2DEvent(_Collide2DQueCurr, *it);
		RemoveCollider2DEvent(_Trigger2DQuePre, *it);
		RemoveCollider2DEvent(_Trigger2DQueCurr, *it);

		_MouseClickQuePre.erase(*it);
		_MouseClickQueCurr.erase(*it);
		_MouseHoverQuePre.erase(*it);
		_MouseHoverQueCurr.erase(*it);
	}

	_DeleteObjectQueue.clear();
}

void EventHandler::BroadcastComponentDeletionEvents()
{
	for (auto it = _DeleteComponentQueue.begin(); it != _DeleteComponentQueue.end(); ++it)
	{
		SendSystemEventMessage(it->first, EventMessageType::COMPONENT_DELETION, nullptr, nullptr);

		if (it->second == ComponentId::BUTTON_COMPONENT)
		{
			_MouseClickQuePre.erase(it->first);
			_MouseClickQueCurr.erase(it->first);
			_MouseHoverQuePre.erase(it->first);
			_MouseHoverQueCurr.erase(it->first);
		}
		else if (it->second == ComponentId::BOXCOLLIDER_COMPONENT || 
			it->second == ComponentId::CIRCLECOLLIDER_COMPONENT || 
			it->second == ComponentId::EDGECOLLIDER_COMPONENT)
		{
			RemoveCollider2DEvent(_Collide2DQuePre, it->first);
			RemoveCollider2DEvent(_Collide2DQueCurr, it->first);
			RemoveCollider2DEvent(_Trigger2DQuePre, it->first);
			RemoveCollider2DEvent(_Trigger2DQueCurr, it->first);
		}

	}

	_DeleteComponentQueue.clear();
}

void EventHandler::BroadcastComponentCreationEvents()
{
	for (auto it = _NewComponentQueue.begin(); it != _NewComponentQueue.end(); ++it)
	{
		SendSystemEventMessage(it->first, EventMessageType::COMPONENT_CREATION, it->second.first, it->second.second);
	}

	_NewComponentQueue.clear();
}

void EventHandler::RemoveCollider2DEvent(Collider2DQueue& queue, size_t first, size_t second)
{
	auto it = queue.find(first);

	if (it != queue.end())
	{
		if (second)
		{
			auto it2 = it->second.find(second);

			if (it2 != it->second.end())
				it->second.erase(it2);

			return;
		}
		queue.erase(it);
	}

	if (!second)
	{
		for (auto it = queue.begin(); it != queue.end(); ++it)
		{
			auto it2 = it->second.find(first);

			if (it2 != it->second.end())
				it->second.erase(it2);
		}
	}
}

void EventHandler::ClearAllEvents()
{
	_Collide2DQuePre.clear();
	_Collide2DQueCurr.clear();

	_Trigger2DQuePre.clear();
	_Trigger2DQueCurr.clear();

	_MouseClickQuePre.clear();
	_MouseClickQueCurr.clear();

	_MouseHoverQuePre.clear();
	_MouseHoverQueCurr.clear();

	_DeleteObjectQueue.clear();

	_NewComponentQueue.clear();
	_DeleteComponentQueue.clear();
}