#include "PrecompiledHeaders.h"
#include "IScript2.h"

IScript2::IScript2() :
	_parent{ nullptr },
	_parentUId{ 0 },
	_uId{ 0 },
	_type{ ScriptType::SCRIPT_COUNT },
	_scriptEnable{ true }
{
}

void IScript2::SetParentPtr(GameObject* parent)
{
	_parent = parent;
}

GameObject* IScript2::GetParentPtr() const
{
	return _parent;
}

void IScript2::SetParentId(size_t uid)
{
	_parentUId = uid;
}

size_t IScript2::GetParentId() const
{
	return _parentUId;
}

IComponent* IScript2::GetSibilingComponent(ComponentId id)
{
	return _parent->GetComponent(id);
}

IScript2* IScript2::GetSibilingScript(ScriptType type)
{
	size_t uId = ((LogicComponent*)_parent->GetComponent(ComponentId::CT_Logic))->GetScript2Id(type);
	return MyLogicSystem.GetScriptList()[uId];
}