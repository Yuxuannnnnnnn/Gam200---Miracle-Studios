///////////////////////////////////////////////////////////////////////////////////////
//
//	MemoryManager.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _MEMORY_MANAGER_H
#define _MEMORY_MANAGER_H

#include "IMemoryInfo.h"
#include "../ISingleton.h"

#define DEFAULT_OBJECT_SIZE 400

class MemoryManager final : public ISingleton<MemoryManager>
{
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
	MemoryManager(bool UseCPPMemManager = false, bool DebugOn = false);
	virtual ~MemoryManager();

	void* Allocate();
	void Free(void* Object);

	// check and free empty page
	unsigned FreeEmptyPages();

	MMConfig GetConfig() const;

	//No replication of class object
	MemoryManager(const MemoryManager& rhs) = delete;
	MemoryManager& operator= (const MemoryManager& rhs) = delete;

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

#define MyMemoryManager MemoryManager::GetInstance()

#endif
