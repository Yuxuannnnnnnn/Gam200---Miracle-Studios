#include "PrecompiledHeaders.h"

template<typename T>
ObjectAllocator<T> IMemoryPool<T>::_OA;

template<typename T>
void* IMemoryPool<T>::operator new(std::size_t n)
{
	(void)n;
	void* newResult = reinterpret_cast<void*>(_OA.Allocate());

	if (nullptr)
		throw std::bad_alloc();

	return newResult;
}

template<typename T>
void IMemoryPool<T>::operator delete(void* p) throw()
{
	_OA.Free(p);
}

template<typename T>
void* IMemoryPool<T>::operator new[](std::size_t n)
{
	return ::operator new(n);
}

template<typename T>
void IMemoryPool<T>::operator delete[](void* p) throw()
{
	::operator delete(p);
}