#include "PrecompiledHeaders.h"
#include "GameObject.h"

#include "GameObjectComponents/PrecompiledComponentHeader.h"
#include "Engine/EngineSystems.h"

GameObject::GameObject(size_t uId, unsigned typeId)
	:_uId{ uId }, _typeId{ typeId }, _destory{ false }, _alive{ true }
{
	//std::cout << "GameObject::GameObject()" << std::endl;
}

GameObject::~GameObject()
{
}


unsigned GameObject::GameObjectType() const
{
	return _typeId;
}
unsigned GameObject::Get_typeId() const
{
	return _typeId;
}
size_t GameObject::Get_uID() const
{
	return _uId;
}


IComponentSystem* GameObject::GetComponent(ComponentId typeId, ScriptId script) // GetChildComponent
{
	if (CheckComponent(typeId))
	{
		if (typeId == ComponentId::LOGIC_COMPONENT && script != ScriptId::EMPTY)
			return reinterpret_cast<LogicComponent*>(_ComponentList[(unsigned)typeId])->GetScript(script);

		return _ComponentList[(unsigned)typeId];
	}

	return nullptr;
}

Map_ComponentList& GameObject::GetComponentList() // Get ComponentList
{
	return _ComponentList;
}


bool  GameObject::CheckComponent(ComponentId componentType, ScriptId script)
{
	Map_ComponentList::iterator it = _ComponentList.find((unsigned)componentType);

	if (it == _ComponentList.end() || !it->second)
		return false;

	if (componentType == ComponentId::LOGIC_COMPONENT && script != ScriptId::EMPTY &&
		!reinterpret_cast<LogicComponent*>(it->second)->CheckScript(script))
	{
		return false;
	}

	return true;
}

IComponentSystem* GameObject::AddComponent(ComponentId componentType, ScriptId script)
{
	if (CheckComponent(componentType, script))
	{
		return GetComponent(componentType, script);
	}

	IComponentSystem* newComponent = EngineSystems::GetInstance()._gameObjectFactory->AddComponent(this, componentType, script);
	
	if (!CheckComponent(componentType))
		_ComponentList.insert(std::pair<unsigned, IComponentSystem*>((unsigned)componentType, newComponent));


	return GetComponent(componentType, script);
}
void GameObject::RemoveComponent(ComponentId componentType, ScriptId script)
{
	if (!CheckComponent(componentType, script))
		return;

	EngineSystems::GetInstance()._gameObjectFactory->RemoveComponent(this, componentType, script);

	if (script == ScriptId::EMPTY)
		_ComponentList.erase((unsigned)componentType + (unsigned)script);
}

void GameObject::DestoryGameObject()
{
	EngineSystems::GetInstance()._gameObjectFactory->DestoryGameObject(this);
}

void GameObject::Set_typeId(TypeIdGO type)
{
	_typeId = (unsigned)type;
}