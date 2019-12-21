///////////////////////////////////////////////////////////////////////////////////////
//
//	IBase.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _IBASE_H
#define _IBASE_H

#include "Tools/Memory/ObjectAllocator.h"

template<typename T>
class IBase
{
private:
	static ObjectAllocator<T> _OA;

public:
	IBase() {}
	virtual ~IBase() {}

public:
	void* operator new(std::size_t n);
	void operator delete(void* p) throw();
	void* operator new[](std::size_t n);
	void operator delete[](void* p) throw();
};

#include "IAllocator.hpp"

#endif
