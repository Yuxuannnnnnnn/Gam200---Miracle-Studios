#pragma once
#include <string>
#include "IComponentSystem.h"

class IComponentSystem
{
public:
	size_t _ParentId{ 0 };
	virtual std::string ComponentName() const;
	virtual size_t GetParentId() const;
};
