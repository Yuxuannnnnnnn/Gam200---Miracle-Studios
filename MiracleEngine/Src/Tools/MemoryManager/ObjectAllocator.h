///////////////////////////////////////////////////////////////////////////////////////
//
//	ObjectAllocator.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _OBJECT_ALLOCATOR_H
#define _OBJECT_ALLOCATOR_H

#include "CommonBase.h"

template<typename T>
class ObjectAllocator final
{
public:
	typedef T ObjectTpye;

private:
	GenericObject* _PageList; //!< the beginning of the list of pages
	GenericObject* _FreeList; //!< the beginning of the list of objects

	MMStats _Stats;
	MMConfig _Config;

	// offset of page pointer to the first object pointer in page
	size_t _PageObjectOffset;
	// size of the object with header, padding, interalign size included
	size_t _ObjectBlockSize;

public:
	ObjectAllocator();
	~ObjectAllocator();

	void* Allocate();
	void Free(void* Object);

	// check and free empty page
	unsigned FreeEmptyPages();

	//No replication of class object
	ObjectAllocator(const ObjectAllocator& rhs) = delete;
	ObjectAllocator& operator= (const ObjectAllocator& rhs) = delete;

private:
	void CreateNewPage(); // new/allocate a new page
	void FreePage(void* Page); // free/deallocate the page
	// Check for invalid Object pointer being pass in
	void CheckInvalidObject(void* Object) const;
	// Check if the object is an empty object
	bool CheckEmptyObject(void* Object) const;
	// removing empty object from freeList
	void RemoveEmptyObject(void* Object);
	
};

#include "ObjectAllocator.hpp"

#endif
