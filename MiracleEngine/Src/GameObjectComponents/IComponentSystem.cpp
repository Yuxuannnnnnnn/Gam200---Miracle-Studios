#include "PrecompiledHeaders.h"
#include "IComponentSystem.h"

IComponentSystem::~IComponentSystem()
{
	delete _factoryPtr;
}




std::string IComponentSystem::ComponentName() const
{
	std::cout << "IComponentSystem::ComponentName()" << std::endl;
	return "&";
}

size_t IComponentSystem::GetParentId() const
{
	return _ParentId;
}