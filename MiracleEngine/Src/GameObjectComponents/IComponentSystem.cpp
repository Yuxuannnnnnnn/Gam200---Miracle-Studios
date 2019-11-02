#include "PrecompiledHeaders.h"
#include "IComponentSystem.h"



IComponentSystem::IComponentSystem(GameObject* parent, size_t uId)
	:	_ParentPtr{ parent }, _ParentId{ uId }
{}



size_t IComponentSystem::GetParentId() const
{
	return _ParentId;
}

//void IComponentSystem::SetParentId(size_t inVal)
//{
//	_ParentId = inVal;
//}

GameObject* IComponentSystem::GetParentPtr()
{
	return _ParentPtr;
}

//void IComponentSystem::SetParentPtr(GameObject* inVal)
//{
//	_ParentPtr = inVal;
//	_ParentId = inVal->Get_uID();
//}

IComponentSystem* IComponentSystem::GetSibilingComponent(unsigned _componentId)
{
	return _ParentPtr->GetComponentList()[_componentId];
}
