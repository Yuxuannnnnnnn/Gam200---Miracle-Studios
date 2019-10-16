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

#include "ISingleton.h"

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <map>

#define GAME_MEMORY_SIZE (10 * 1048576) // 100 kb

// 1 kb = 1024 btye 
// 1 mb = 1024 kb = 1048576 btye 


class MMException
{
public:
	enum MM_EXCEPTION
	{
		E_NO_MEMORY
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

// try
// {
// }
// catch (const MAException& e)
// {
// }

struct AddressComp {
	bool operator() (const void* lhs, const void* rhs) const
	{
		return lhs < rhs;
	}
};


class MemoryManager final : public ISingleton<MemoryManager>
{
public:

	enum MEMORYTYPE
	{
		M_NEW,
		M_OBJECT
	};

private:
	void* _basePoint;

	std::map<void*, size_t, AddressComp> _freeMemory;
	std::map<void*, size_t> _usedMemory;

public:
	MemoryManager();

	void init()
	{
		_basePoint = malloc(GAME_MEMORY_SIZE);

		if (!_basePoint)
			throw MMException(MMException::E_NO_MEMORY, "");

		_freeMemory.insert(std::pair<void*, size_t>(_basePoint, GAME_MEMORY_SIZE));

	}

	//No replication of class object
	MemoryManager(const MemoryManager& rhs) = delete;
	MemoryManager& operator= (const MemoryManager& rhs) = delete;

	~MemoryManager();

	void* Allocate(MEMORYTYPE type, size_t size = 0);
	void Deallocate(MEMORYTYPE type, void* memory);

private:

	// take care of gobal new and delete function
	void* NewMemory(size_t size);
	void DeleteMemory(void* memory);
};

#endif
