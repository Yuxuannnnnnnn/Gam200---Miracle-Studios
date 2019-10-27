#pragma once
#include <string>
#include "IComponentSystem.h"

class IComponentSystem
{
protected:
	size_t _ParentId{ 0 };

public:
	virtual std::string ComponentName() const;
	virtual size_t GetParentId() const;
};
