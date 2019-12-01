
#include "PrecompiledHeaders.h"
#include "GameObject.h"

#include "GameObjectComponents/PrecompiledComponentHeader.h"
#include "Engine/EngineSystems.h"
#include "Tools/FileIO/Serialiser.h"

GameObject::GameObject(size_t uId)
	:_uId{ uId }, _destory{ false }, _enable{ true }, _alive{ true }
{
	//std::cout << "GameObject::GameObject()" << std::endl;
}

GameObject::~GameObject()
{
}


//unsigned GameObject::GameObjectType() const
//{
//	return _typeId;
//}
//unsigned GameObject::Get_typeId() const
//{
//	return _typeId;
//}

//void GameObject::Set_typeId(TypeIdGO type)
//{
//	_typeId = (unsigned)type;
//}


size_t GameObject::Get_uID() const
{
	return _uId;
}


IComponentSystem* GameObject::GetComponent(ComponentId typeId, ScriptId script) // GetChildComponent
{
	if (CheckComponent(typeId))
	{
		if (typeId == ComponentId::LOGIC_COMPONENT && script != ScriptId::EMPTY)
			return reinterpret_cast<LogicComponent*>(_ComponentList[typeId])->GetScript(script);

		return _ComponentList[typeId];
	}

	return nullptr;
}


//void GameObject::SerialiseFromLevel(rapidjson::Value& fileObject)
//{
//	for (auto& ComPair : _ComponentList)
//	{
//		ComPair.second->SerialiseComponent(fileObject);
//	}
//
//}

void GameObject::Serialise(std::string file)
{
	IComponentSystem* component = nullptr;

	Serialiser document(file);
	int i = 0;
	//auto ComponentTypes = EngineSystems::GetInstance()._prefabFactory->GetComponentTypes();


	for (int i = 0; i < (int)ComponentId::COUNTCOMPONENT; i++)
	{
		if (document.HasMember(ToString((ComponentId)i)))
		{
			component = AddComponent((ComponentId)i);
			component->SerialiseComponent(document);
		}
	}

}

void GameObject::DeSerialise()
{
	IdentityComponent* IdComponent = dynamic_cast<IdentityComponent*> (_ComponentList[ComponentId::IDENTITY_COMPONENT]);
	std::string fileName = "./Resources/TextFiles/GameObjects/" + IdComponent->ObjectType() + ".json";
	DeSerialiser prototypeDoc(fileName);

	for (auto& ComponentPair : _ComponentList)
	{
		rapidjson::Value value;
		value.SetBool(true);
		prototypeDoc.AddMember(ToString((ComponentId)ComponentPair.first), value);
		//value.Clear();

		IComponentSystem* component = ComponentPair.second;
		component->DeSerialiseComponent(prototypeDoc);
	}
}

Map_ComponentList& GameObject::GetComponentList() // Get ComponentList
{
	return _ComponentList;
}


bool  GameObject::CheckComponent(ComponentId componentType, ScriptId script)
{
	Map_ComponentList::iterator it = _ComponentList.find(componentType);

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
		_ComponentList.insert(std::pair<ComponentId, IComponentSystem*>(componentType, newComponent));


	return GetComponent(componentType, script);
}
void GameObject::RemoveComponent(ComponentId componentType, ScriptId script)
{
	if (!CheckComponent(componentType, script))
		return;

	EngineSystems::GetInstance()._gameObjectFactory->RemoveComponent(this, componentType, script);

	//if (script == ScriptId::EMPTY)
		//_ComponentList.erase((ComponentId((unsigned)componentType + (unsigned)script)));
}

void GameObject::DestoryGameObject()
{
	EngineSystems::GetInstance()._gameObjectFactory->DestoryGameObject(this);
}

