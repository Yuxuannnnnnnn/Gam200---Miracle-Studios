///////////////////////////////////////////////////////////////////////////////////////
//
//	CommonBase.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _COMMON_BASE_H
#define _COMMON_BASE_H

#include <iostream>
#include <string>

#define DEFAULT_OBJECTS_PER_PAGE 40

static const unsigned char TRUE_PATTERN = 0xAA;
static const unsigned char FALSE_PATTERN = 0xBB;

class MMException
{
public:
	enum class MM_EXCEPTION
	{
		E_NO_MEMORY,
		E_BAD_BOUNDARY,
		E_MULTIPLE_FREE
	};

	MMException(MM_EXCEPTION errCode, const std::string& message) :
		_errorCode(errCode), _message(message) {}

	virtual ~MMException() {}

	MM_EXCEPTION code() const {
		return _errorCode;
	}

	virtual const char* what() const {
		return _message.c_str();
	}

private:
	MM_EXCEPTION _errorCode;
	std::string _message;
};

struct MMConfig
{
	static const unsigned BASIC_HEADER_SIZE = 1; //!< flags

	MMConfig(bool UseCPPMemManager = false,
		bool DebugOn = false,
		unsigned ObjectsPerPage = DEFAULT_OBJECTS_PER_PAGE,
		unsigned HeaderBytes = BASIC_HEADER_SIZE,
		unsigned EndPadding = 0) :
		_UseCPPMemManager{ UseCPPMemManager },
		_DebugOn{ DebugOn },
		_ObjectsPerPage{ ObjectsPerPage },
		_HeaderBytes{ HeaderBytes },
		_EndPadding{ EndPadding }
	{
	}

	bool _UseCPPMemManager;      //!< by-pass the functionality of the OA and use new/delete
	bool _DebugOn;
	unsigned _ObjectsPerPage;    //!< number of objects on each page
	unsigned _HeaderBytes;       //!< size of the header for each block
	unsigned _EndPadding;		 //!< size of the padding at end of each page
};

struct MMStats
{
	MMStats() : _ObjectSize(0), _PageSize(0), _FreeObjects(0), _ObjectsInUse(0), _PagesInUse(0),
		_MostObjects(0), _Allocations(0), _Deallocations(0) {};

	size_t _ObjectSize;      //!< size of each object
	size_t _PageSize;        //!< size of a page 
	unsigned _FreeObjects;   //!< number of objects on the free list
	unsigned _ObjectsInUse;  //!< number of objects in use by client
	unsigned _PagesInUse;    //!< number of pages allocated
	unsigned _MostObjects;   //!< most objects in use by client at one time
	unsigned _Allocations;   //!< total requests to allocate memory
	unsigned _Deallocations; //!< total requests to free memory
};

struct GenericObject
{
	GenericObject* _Next; //!< The next object in the list
};

#endif
