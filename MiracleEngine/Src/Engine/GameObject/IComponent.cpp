#include "PrecompiledHeaders.h"
#include "IComponent.h"

IComponent::IComponent() 
	:
	_ParentPtr{ nullptr },
	_ParentId{ 0 },
	_enable{ true }
{}


IComponent::IComponent(GameObject* parent, size_t uId)
	: _ParentPtr{ parent }, _ParentId{ uId }, _enable{ true }
{}


size_t IComponent::GetParentId() const
{
	return _ParentId;
}
void IComponent::SetParentId(size_t inVal)
{
	_ParentId = inVal;
}

GameObject* IComponent::GetParentPtr()
{
	return _ParentPtr;
}
void IComponent::SetParentPtr(GameObject* inVal)
{
	_ParentPtr = inVal;
	_ParentId = inVal->Get_uID();
}

IComponent* IComponent::GetSibilingComponent(ComponentId _componentId)
{

	if(_ParentPtr->GetComponentList().find(_componentId) != _ParentPtr->GetComponentList().end())
		return _ParentPtr->GetComponentList()[_componentId];

	return nullptr;
}

void IComponent::DestoryThis() 
{
	_ParentPtr->SetDestory();
}


void  IComponent::Inspect()
{
	ImGui::Spacing();
	std::string string = "Component Enable " + ComponentName();
	ImGui::Checkbox(string.c_str(), &_enable);
	ImGui::Spacing();
}