///////////////////////////////////////////////////////////////////////////////////////
//
//	MemoryManager.cpp
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#include "PrecompiledHeaders.h"
#include "MemoryManager.h"

MemoryManager::MemoryManager(bool UseCPPMemManager, bool DebugOn) :
	_PageList{ nullptr },
	_FreeList{ nullptr },
	_Stats{},
	_Config{ MMConfig{UseCPPMemManager, DebugOn} },
	_PageObjectOffset{ 0 },
	_ObjectBlockSize{ 0 }
{
	_Stats._ObjectSize = DEFAULT_OBJECT_SIZE;

	// update offsets
	_PageObjectOffset = sizeof(GenericObject) + _Config._HeaderBytes;
	_ObjectBlockSize = _Config._HeaderBytes + _Stats._ObjectSize;


	_Stats._PageSize = sizeof(GenericObject) + _Config._ObjectsPerPage * _ObjectBlockSize;

	// Check we need to create our own custom memory blocks 
	if (_Config._UseCPPMemManager)
		return;

	// Create the a new Page of memory
	CreateNewPage();
}

MemoryManager::~MemoryManager()
{
	// Check we need to create our own custom memory blocks 
	if (_Config._UseCPPMemManager)
		return;

	// free all page of memory in the custom memory allocator
	while (_PageList)
	{
		GenericObject* page = _PageList;
		_PageList = _PageList->_Next;
		FreePage(page);
	}
}

void* MemoryManager::Allocate()
{
	// Check we need to create our own custom memory blocks 
	if (_Config._UseCPPMemManager)
	{
		void* object = new(std::nothrow) unsigned char[_Stats._ObjectSize];

		if (object == nullptr)
			throw MMException(MMException::MM_EXCEPTION::E_NO_MEMORY, "Memory allocation problem");

		// Update OAStasts 
		++_Stats._Allocations;
		++_Stats._ObjectsInUse;

		if (_Stats._MostObjects < _Stats._ObjectsInUse)
			_Stats._MostObjects = _Stats._ObjectsInUse;

		return object;
	}

	// Check for available
	if (!_Stats._FreeObjects)
		CreateNewPage();

	// Get and update Objectblock 
	GenericObject* object = _FreeList;
	_FreeList = _FreeList->_Next;

	unsigned char* bytes = reinterpret_cast<unsigned char*>(object) - _Config._HeaderBytes;

	*bytes = TRUE_PATTERN;

	// Update OAStasts 
	--_Stats._FreeObjects;
	++_Stats._Allocations;
	++_Stats._ObjectsInUse;

	if (_Stats._MostObjects < _Stats._ObjectsInUse)
		_Stats._MostObjects = _Stats._ObjectsInUse;

	return reinterpret_cast<void*>(object);
}

void MemoryManager::Free(void* Object)
{
	// Check we need to create our own custom memory blocks 
	if (_Config._UseCPPMemManager)
	{
		// Update OAStasts 
		++_Stats._Deallocations;
		--_Stats._ObjectsInUse;

		delete[] reinterpret_cast<unsigned char*>(Object);
		return;
	}

	// just for invalid object pointer, throw Exception
	CheckInvalidObject(Object);

	if (CheckEmptyObject(Object))
		throw MMException(MMException::MM_EXCEPTION::E_MULTIPLE_FREE, "Freeing object twice");

	unsigned char* bytes = reinterpret_cast<unsigned char*>(Object) - _Config._HeaderBytes;

	*bytes = FALSE_PATTERN;

	// Update freed object into FreeList_
	GenericObject* object = reinterpret_cast<GenericObject*>(Object);
	object->_Next = _FreeList;
	_FreeList = object;

	// Update OAStasts 
	--_Stats._ObjectsInUse;
	++_Stats._FreeObjects;
	++_Stats._Deallocations;
}

void MemoryManager::CreateNewPage()
{
	GenericObject* newPage = reinterpret_cast<GenericObject*>(malloc(_Stats._PageSize));

	if (newPage == nullptr)
		throw MMException(MMException::MM_EXCEPTION::E_NO_MEMORY, "Memory allocation problem");

	// Setup all the objects in the new page
	for (unsigned int n = 0; n < _Config._ObjectsPerPage; ++n)
	{
		GenericObject* object =
			reinterpret_cast<GenericObject*>(
				reinterpret_cast<unsigned char*>(newPage) + _PageObjectOffset + _ObjectBlockSize * n);

		unsigned char* bytes =
			reinterpret_cast<unsigned char*>(object) - _Config._HeaderBytes;

		*bytes = FALSE_PATTERN;

		object->_Next = _FreeList;
		_FreeList = object;
	}

	newPage->_Next = _PageList;
	_PageList = newPage;

	// update OAStats
	++_Stats._PagesInUse;
	_Stats._FreeObjects += _Config._ObjectsPerPage;
}

void MemoryManager::FreePage(void* Page)
{
	free(Page);

	--_Stats._PagesInUse;
	_Stats._FreeObjects -= _Config._ObjectsPerPage;
}

void MemoryManager::CheckInvalidObject(void* Object) const
{
	GenericObject* page = _PageList;

	// loop Through all pages in PageList_
	while (page)
	{
		// get page that is after page pointer
		if (reinterpret_cast<GenericObject*>(Object) < page)
		{
			page = page->_Next;
			continue;
		}

		// bytes distance bewtwwn page to object
		size_t bytes =
			reinterpret_cast<unsigned char*>(Object) - reinterpret_cast<unsigned char*>(page);

		// get page that object is within page size 
		if (bytes >= _Stats._PageSize)
		{
			page = page->_Next;
			continue;
		}

		// check object is align with page and object size
		if ((bytes - _PageObjectOffset) % _ObjectBlockSize == 0)
			return;

		page = page->_Next;
	}

	throw MMException(MMException::MM_EXCEPTION::E_BAD_BOUNDARY, "Invalid object");
}

bool MemoryManager::CheckEmptyObject(void* Object) const
{
	unsigned char* header = reinterpret_cast<unsigned char*>(Object) - _Config._HeaderBytes;

	if (*header == TRUE_PATTERN)
		return false;

	return true;
}

void MemoryManager::RemoveEmptyObject(void* Object)
{
	GenericObject* objectPrev = nullptr;
	GenericObject* objectCurr = _FreeList;

	// loop through the FreeList_ to find the object
	while (objectCurr)
	{
		GenericObject* object = objectCurr;

		if (object == reinterpret_cast<GenericObject*>(Object))
		{
			// remove the object from list
			// And link the pre-object with the next-object
			if (objectPrev)
			{
				objectPrev->_Next = object->_Next;
				objectCurr = object->_Next;
			}
			else
			{
				_FreeList = objectCurr->_Next;
				objectCurr = objectCurr->_Next;
			}
			break;
		}

		objectPrev = objectCurr;
		objectCurr = objectCurr->_Next;
	}
}

unsigned MemoryManager::FreeEmptyPages()
{
	// no page at all, if new/delete
	if (_Config._UseCPPMemManager)
		return 0;

	unsigned pageFreed = 0; // page freed counter

	GenericObject* pagePrev = nullptr;
	GenericObject* pageCurr = _PageList;

	// Loop through all the page in the pageList
	while (pageCurr)
	{
		bool emptyPage = true;

		// Loop through all the objects in the pageNext
		for (unsigned int n = 0; n < _Config._ObjectsPerPage; ++n)
		{
			void* object =
				reinterpret_cast<void*>(
					reinterpret_cast<unsigned char*>(pageCurr) + _PageObjectOffset + _ObjectBlockSize * n);

			// Check object whether is empty
			if (!CheckEmptyObject(object))
			{
				emptyPage = false;
				break;
			}
		}

		// free page and update pageList
		if (emptyPage)
		{
			GenericObject* page = pageCurr;

			if (pagePrev)
			{
				pagePrev->_Next = pageCurr->_Next;
				pageCurr = pageCurr->_Next;
			}
			else
			{
				_PageList = pageCurr->_Next;
				pageCurr = pageCurr->_Next;
			}

			// Loop through all the empty objects in the page
			for (unsigned int n = 0; n < _Config._ObjectsPerPage; ++n)
			{
				void* object =
					reinterpret_cast<void*>(
						reinterpret_cast<unsigned char*>(pageCurr) + _PageObjectOffset + _ObjectBlockSize * n);

				RemoveEmptyObject(object);
			}

			FreePage(page);

			++pageFreed;
			continue;
		}

		pagePrev = pageCurr;
		pageCurr = pageCurr->_Next;
	}

	return pageFreed;
}

MMConfig MemoryManager::GetConfig() const
{
	return _Config;
}