#ifndef _IMEMORY_POOL_H
#define _IMEMORY_POOL_H

#include "Tools/Memory/ObjectAllocator.h"

template<typename T>
class IMemoryPool
{
private:
	static ObjectAllocator<T> _OA;

public:
	IMemoryPool() {}
	virtual ~IMemoryPool() {}

public:
	void* operator new(std::size_t n);
	void operator delete(void* p) throw();
	void* operator new[](std::size_t n);
	void operator delete[](void* p) throw();
};

#include "IMemoryPool.hpp"

#endif
