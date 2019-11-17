///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
//
//	MemoryManager.cpp
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#include "MemoryManager.h"

MemoryManager::MemoryManager() :
	_basePoint{ nullptr },
	_freeMemory{},
	_usedMemory{}
{
	_basePoint = malloc(GAME_MEMORY_SIZE);

	if (!_basePoint)
		throw MMException(MMException::E_NO_MEMORY, "");

	_freeMemory.insert(std::pair<void*, size_t>(_basePoint, GAME_MEMORY_SIZE));
}




MemoryManager::~MemoryManager()
{

	_freeMemory.clear();
	_usedMemory.clear();
	free(_basePoint);
}

void* MemoryManager::Allocate(MEMORYTYPE type, size_t size)
{
	switch (type)
	{
	case M_NEW:
		return NewMemory(size);
		break;
	case M_OBJECT:
		break;
	}

	return nullptr;
}

void MemoryManager::Deallocate(MEMORYTYPE type, void* memory)
{
	if (!memory)
		throw MMException(MMException::E_NO_MEMORY, "Free Nullptr");

	switch (type)
	{
	case M_NEW:
		DeleteMemory(memory);
		break;
	case M_OBJECT:
		break;
	}
}

void* MemoryManager::NewMemory(size_t size) 
{
	void* result = nullptr;

	for (auto it : _freeMemory)
	{
		if (it.second >= size)
		{
			result = it.first;

			std::pair<void*, size_t> data;
			data.first = result;
			data.second = size;

			_usedMemory.insert(data);

			if (size != it.second)
			{
				data.first = reinterpret_cast<void*>(reinterpret_cast<unsigned char*>(result) + size);
				data.second = it.second - size;

				_freeMemory.insert(data);
			}

			_freeMemory.erase(it.first);
			break;
		}
	}
	return result;
}
void MemoryManager::DeleteMemory(void* memory)
{

	std::map<void*, size_t>::iterator it = _usedMemory.find(memory);

	if (it != _usedMemory.end())
	{
		std::pair<void*, size_t> data;
		data.first = memory;
		data.second = it->second;

		void* nextBlock = reinterpret_cast<void*>(reinterpret_cast<unsigned char*>(memory) + it->second);

		std::map<void*, size_t, AddressComp>::iterator prevIt = _freeMemory.end();
		std::map<void*, size_t, AddressComp>::iterator currIt = _freeMemory.begin();

		while (currIt != _freeMemory.end())
		{
			if (currIt->first == nextBlock)
			{
				if (prevIt != _freeMemory.end())
				{
					void* test = reinterpret_cast<void*>(reinterpret_cast<unsigned char*>(prevIt->first) + prevIt->second);

					if (test == memory)
					{
						data.first = prevIt->first;
						data.second += prevIt->second;
						_freeMemory.erase(prevIt);
					}
				}
				data.second += currIt->second;
				_freeMemory.erase(currIt);
				break;
			}
			prevIt = currIt;
			currIt++;
		}

		_freeMemory.insert(data);
		_usedMemory.erase(it);
	}
}