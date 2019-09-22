#pragma once
#include "PrecompiledHeaders.h"
#include "IComponentSystem.h"



class IComponentSystem
{
public:

	virtual std::string ComponentName() const = 0;

};

