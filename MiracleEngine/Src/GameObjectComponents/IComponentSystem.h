#pragma once
#include <string>
#include "IComponentSystem.h"



class IComponentSystem
{
public:

	virtual std::string ComponentName() const = 0;
	virtual size_t GetParentId() const = 0;
};

