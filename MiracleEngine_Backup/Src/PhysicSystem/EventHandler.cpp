///////////////////////////////////////////////////////////////////////////////////////
//
//	EventHandler.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#include "EventHandler.h"
#include "Engine/GameObject.h"

void EventHandler::UpdateEvent()
{
	UpdateCollisionEvent();
	UpdateStaticCollisionEvent();
}

void EventHandler::UpdateStaticCollisionEvent()
{
	for (auto it : _staticCollsionQueue)
	{
		if (!it.first->_enable)
			continue;

		GameObject* object = it.first->_gameObject;
		//object->StaticCollisionCheck(it.second);
	}

	_staticCollsionQueue.clear();
}

void EventHandler::UpdateCollisionEvent()
{
	std::multimap<Collider2D*, Collider2D*> tempQueue;


	for (auto it = _collisionQueueCurr.begin(); it != _collisionQueueCurr.end();)
	{
		if (!it->first->_enable)
		{
			++it;
			continue;
		}

		bool incement = true;

		auto range = _collisionQueuePre.equal_range(it->first);

		for (auto it2 = range.first; it2 != range.second; ++it2)
		{
			if (it->second == it2->second)
			{
				if (!it2->first->_enable)
					continue;

				GameObject* object = it->first->_gameObject;
				//object->OnCollisionStay(it->second);

				tempQueue.insert(*it);

				RemoveCollisionEventPre(it2->first, it2->second);
				RemoveCollisionEventCurr(it->first, it->second);
				it = _collisionQueueCurr.begin();
				incement = false;
				break;
			}
		}

		if (incement)
			++it;
	}

	for (auto it = _collisionQueuePre.begin(); it != _collisionQueuePre.end();)
	{
		if (!it->first->_enable)
		{
			++it;
			continue;
		}

		GameObject* object = it->first->_gameObject;
		//object->OnCollisionExit(it->second);

		RemoveCollisionEventPre(it->first, it->second);

		it = _collisionQueuePre.begin();
	}



	for (auto it = _collisionQueueCurr.begin(); it != _collisionQueueCurr.end();)
	{
		if (!it->first->_enable)
		{
			++it;
			continue;
		}

		GameObject* object = it->first->_gameObject;
		//object->OnCollisionTrigger(it->second);

		tempQueue.insert(*it);

		RemoveCollisionEventCurr(it->first, it->second);

		it = _collisionQueueCurr.begin();
	}

	_collisionQueuePre.clear();

	_collisionQueuePre = tempQueue;

	_collisionQueueCurr.clear();
}


void EventHandler::AddCollisionEvent(Collider2D& first, Collider2D& second)
{
	_collisionQueueCurr.insert({ &first ,&second });
}

void EventHandler::AddStaticCollisionEvent(Collider2D& first, int second)
{
	_staticCollsionQueue.insert({ &first, second });
}

void EventHandler::RemoveCollisionEventPre(Collider2D* first, Collider2D* second)
{
	auto range = _collisionQueuePre.equal_range(first);

	for (auto it2 = range.first; it2 != range.second;)
	{
		if (it2->second == second)
		{
			_collisionQueuePre.erase(it2);
			range = _collisionQueuePre.equal_range(first);
			it2 = range.first;
		}
		else
		{
			++it2;
		}
	}
}

void EventHandler::RemoveCollisionEventCurr(Collider2D* first, Collider2D* second)
{
	auto range = _collisionQueueCurr.equal_range(first);

	for (auto it2 = range.first; it2 != range.second;)
	{
		if (it2->second == second)
		{
			_collisionQueueCurr.erase(it2);

			range = _collisionQueueCurr.equal_range(first);
			it2 = range.first;
		}
		else
		{
			++it2;
		}
	}
}

void EventHandler::ClearAllQueue()
{
	_collisionQueuePre.clear();
	_collisionQueueCurr.clear();
	_staticCollsionQueue.clear();
}