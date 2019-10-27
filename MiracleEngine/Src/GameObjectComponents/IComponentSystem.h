#pragma once
#include <string>
#include "PrecompiledHeaders.h"

class GameObjectFactory;

class IComponentSystem
{
public:
	GameObjectFactory* _factoryPtr;
	size_t _ParentId{ 0 };

	virtual ~IComponentSystem();
	virtual std::string ComponentName() const;
	virtual size_t GetParentId() const;
};
