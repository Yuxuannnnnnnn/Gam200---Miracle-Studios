#pragma once
#include <string>



class IComponentSystem
{
public:

	virtual std::string ComponentName() const = 0;

};

