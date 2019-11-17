///////////////////////////////////////////////////////////////////////////////////////
//
//	Coin.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _COIN_H
#define _COIN_H

#include "IColliderHandler.h"
#include "GameObject.h"

struct Coin : public GameObject, public IColliderHandler {

	void OnCollision2DTrigger(Collider2D* other)
	{
		if (other->_type == ColliderType::CIRCLE_COLLIDER)
		{
			std::cout << "Trigger Coin" << std::endl;
		}
	}

	void OnCollision2DStay(Collider2D* other)
	{
		if (other->_type == ColliderType::CIRCLE_COLLIDER)
		{
			std::cout << "In Coin" << std::endl;
		}
	}

	void OnCollision2DExit(Collider2D* other)
	{
		if (other->_type == ColliderType::CIRCLE_COLLIDER)
		{
			std::cout << "Exit Coin" << std::endl;
		}
	}

	void* operator new(std::size_t n)
	{
		void* result = MemoryManager::GetInstance().Allocate(MemoryManager::M_NEW, n);

		if (result == nullptr)
			throw std::bad_alloc();

		std::cout << "My memory manager : " << (long long)(result) << std::endl;

		return result;
	}
	void operator delete(void* p) throw()
	{
		MemoryManager::GetInstance().Deallocate(MemoryManager::M_NEW, p);

		std::cout << "My memory manager deleted " << std::endl;
	}

	void* operator new[](std::size_t s)
	{
		return ::operator new(s);
	}
		void operator delete[](void* p) throw()
	{
		::operator delete(p);
	}
};

#endif
