
#include "PrecompiledHeaders.h"
#include "GameObject.h"

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


IComponent* GameObject::GetComponent(ComponentId typeId, ScriptId script) // GetChildComponent
{
	if (CheckComponent(typeId))
	{
		return _ComponentList[typeId];
	}

	return nullptr;
}

//For Level File
//void GameObject::SerialiseFromLevel(Serialiser& fileObject)
//{
//	for (auto& ComPair : _ComponentList)
//	{
//		ComPair.second->SerialiseComponent(fileObject);
//	}
//
//}

//For Prototype Files
void GameObject::Serialise(Serialiser& document)
{
	IComponent* component = nullptr;

	//Serialiser document(file);
	int i = 0;
	//auto ComponentTypes = EngineSystems::GetInstance()._prefabFactory->GetComponentTypes();


	for (int i = 0; i < (int)ComponentId::CT_Count; i++)
	{
		if (document.HasMember(ToString((ComponentId)i)))
		{
			//AddComponent already has a checkComponent(), will return existing component if have
			component = AddComponent((ComponentId)i);
			component->SerialiseComponent(document);
		}
	}

}

void GameObject::DeSerialise(std::string filePath)
{
	//IdentityComponent* IdComponent = dynamic_cast<IdentityComponent*> (_ComponentList[ComponentId::IDENTITY_COMPONENT]);
	//std::string fileName = "./Resources/TextFiles/GameObjects/" + IdComponent->ObjectType() + ".json";
	DeSerialiser prototypeDoc(filePath);

	for (auto& ComponentPair : _ComponentList)
	{
		rapidjson::Value value;
		//value.Clear();

		IComponent* component = ComponentPair.second;
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

	return true;
}

IComponent* GameObject::AddComponent(ComponentId componentType, ScriptId script)
{
	if (CheckComponent(componentType, script))
	{
		return GetComponent(componentType, script);
	}

	IComponent* newComponent = EngineSystems::GetInstance()._gameObjectFactory->AddComponent(this, componentType, script);
	
	if (!CheckComponent(componentType))
		_ComponentList.insert(std::pair<ComponentId, IComponent*>(componentType, newComponent));


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


bool GameObject::GetAlive()
{ 
	return _alive; 
}

void GameObject::SetAlive(bool alive)
{ 
	_alive = alive; 
}

bool GameObject::GetDestory() const
{ 
	return _destory; 
}

void GameObject::SetDestory()
{
	_destory = true;
	SetEnable(false);
	//MyEventHandler.AddDeletionEvent(_uId);
}

bool GameObject::GetEnable() const
{ 
	return _enable; 
}

void GameObject::SetEnable(bool enable)
{
	_enable = enable;

	for (auto it : _ComponentList)
		it.second->SetEnable(enable);
}

GameObject* GameObject::Clone()
{
	GameObject* newGameObject = new GameObject();

	for (auto it : _ComponentList)
	{
		newGameObject->_ComponentList[it.first] = it.second->CloneComponent();
	}

	return newGameObject;
}

void GameObject::Set_uID(size_t uid)
{
	_uId = uid;
}