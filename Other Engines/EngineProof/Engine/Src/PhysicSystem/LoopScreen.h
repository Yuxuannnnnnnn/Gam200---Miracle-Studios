///////////////////////////////////////////////////////////////////////////////////////
//
//	LoppScreen.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _LOOP_SCREEN_H
#define _LOOP_SCREEN_H

#include "GameObject.h"

struct LoopScreen : public GameObject {

	LoopScreen(Vector3 pos = Vector3{ 0,0 }, Vector3 scale = Vector3{ 20,20 }, float angle = 0, const std::string & name = "zombie", bool isanimated = false) :
		GameObject(pos, scale, angle, name, isanimated)
	{
	}

	void Update()
	{
		if (_pos._x > 400)
			_pos._x = -400.f;

		if (_pos._x < -400)
			_pos._x = 400.f;

		if (_pos._y > 300)
			_pos._y = -300.f;

		if (_pos._y < -300)
			_pos._y = 300.f;

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
