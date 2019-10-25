#pragma once
#include <string>
#include "IComponentSystem.h"



class IComponentSystem
{
	
public:
	size_t _ParentId;
	virtual std::string ComponentName() const = 0;
	virtual size_t GetParentId() const = 0;
};

