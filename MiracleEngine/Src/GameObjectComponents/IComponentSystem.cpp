#include "PrecompiledHeaders.h"
#include "IComponentSystem.h"

IComponentSystem::IComponentSystem() :
	_ParentPtr{ nullptr },
	_ParentId{ 0 }
{}

std::string IComponentSystem::ComponentName() const
{
	std::cout << "IComponentSystem::ComponentName()" << std::endl;
	return "&";
}

size_t IComponentSystem::GetParentId() const
{
	return _ParentId;
}
void IComponentSystem::SetParentId(size_t inVal)
{
	_ParentId = inVal;
}

GameObject* IComponentSystem::GetParentPtr()
{
	return _ParentPtr;
}
void IComponentSystem::SetParentPtr(GameObject* inVal)
{
	_ParentPtr = inVal;
	_ParentId = inVal->Get_uID();
}

IComponentSystem* IComponentSystem::GetSibilingComponent(unsigned _componentId)
{
	return _ParentPtr->GetComponentList()[_componentId];
}
