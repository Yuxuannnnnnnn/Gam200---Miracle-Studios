#include "PrecompiledHeaders.h"
#include "IComponentSystem.h"

IComponentSystem::IComponentSystem() 
	:
	_ParentPtr{ nullptr },
	_ParentId{ 0 },
	_enable{ true }
{}


IComponentSystem::IComponentSystem(GameObject* parent, size_t uId)
	: _ParentPtr{ parent }, _ParentId{ uId }, _enable{ true }
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

IComponentSystem* IComponentSystem::GetSibilingComponent(ComponentId _componentId)
{

	if(_ParentPtr->GetComponentList().find(_componentId) != _ParentPtr->GetComponentList().end())
		return _ParentPtr->GetComponentList()[_componentId];

	return nullptr;
}

void IComponentSystem::DestoryThis() 
{
	_ParentPtr->SetDestory();
}


void  IComponentSystem::Inspect()
{
	ImGui::Spacing();
	std::string string = "Component Enable " + ComponentName();
	ImGui::Checkbox(string.c_str(), &_enable);
	ImGui::Spacing();
}