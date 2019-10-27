#include "PrecompiledHeaders.h"




std::string IComponentSystem::ComponentName() const
{
	std::cout << "IComponentSystem::ComponentName()" << std::endl;
	return "&";
}

size_t IComponentSystem::GetParentId() const
{
	return _ParentId;
}