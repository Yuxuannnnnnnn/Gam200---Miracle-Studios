#include "PrecompiledHeaders.h"
#include "GameObject.h"
#include "GlobalContainer.h"
#include "Editor/ImGuizmoManager.h"

GameObject::GameObject(size_t uId)
	:_uId{ uId }, _destory{ false }, _enable{ true }, _alive{ true }, _independent{ true }, _anyChild{false}
{
	//std::cout << "GameObject::GameObject()" << std::endl;
}

GameObject::~GameObject()
{
	for (auto& it : _ComponentList)
	{
		MyComponentManger.GetComponentContainer(it.first)->erase(it.second->GetParentId());
		delete it.second;
	}

	_ComponentList.clear();

	for (auto& it : _childObjects)
	{
		delete it.second;
		MyFactory.RemoveChildGameObject(it.first);
	}
	_childObjects.clear();
}

void GameObject::Init()
{
	for (auto& it : _ComponentList)
	{
		it.second->Init();
	}
}

void GameObject::LoadResource()
{
	for (auto& it : _ComponentList)
	{
		it.second->LoadResource();
	}
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


IComponent* GameObject::GetComponent(ComponentId componentType) // GetChildComponent
{
	Map_ComponentList::iterator it = _ComponentList.find(componentType);

	if (it != _ComponentList.end())
		return _ComponentList[componentType];

	return nullptr;
}


IComponent* GameObject::AddComponent(ComponentId componentType)
{
	IComponent* result = GetComponent(componentType);

	if (result)
		return result;

	result = MyFactory.CreateEmptyComponent(ToRegisterID(componentType));
	result->SetParentId(_uId);
	result->SetParentPtr(this);

	_ComponentList.insert(std::pair<ComponentId, IComponent*>(componentType, result));

	if (_uId) // all prototype should be 0
		MyComponentManger.GetComponentContainer(componentType)->insert({ _uId, result });

	return result;
}

void GameObject::RemoveComponent(ComponentId componentType)
{
	Map_ComponentList::iterator it = _ComponentList.find(componentType);

	if (it != _ComponentList.end())
	{
		delete it->second;

		if (_uId) // all prototype should be 0
			MyComponentManger.GetComponentContainer(componentType)->erase(_uId);

		_ComponentList.erase(componentType);
	}
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

//For Prototype Files and Objects in SceneFile
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
			if (document[ToString((ComponentId)i)].IsNull())
			{
				if(GetComponent((ComponentId)i))
					RemoveComponent((ComponentId)i);
			}
			else
			{
				//AddComponent already has a checkComponent(), will return existing component if have
				component = AddComponent((ComponentId)i);
				component->SerialiseComponent(document);
			}
		}
	}

	if (document.HasMember("HaveChild"))
	{
		_anyChild = true;

		if (document.HasMember("ChildObjects") && document["ChildObjects"].IsArray())
		{

			for (auto& childObjects : _childObjects)
			{
				delete childObjects.second; //delete all the gameObjects within this childObject and itself
				MyFactory.RemoveChildGameObject(childObjects.first); //remove the child Object from the factory lists
			}
			_childObjects.clear(); //Clear child list


			unsigned size = document["ChildObjects"].Size();

			for (unsigned i = 0; i < size; ++i)
			{
				Serialiser datafile(document["ChildObjects"][i]);

				GameObject* child = new GameObject();

				child->Serialise(datafile);
				child->SetIndependent(false);
				child->SetParent(this);

				_childObjects[i] = child;
			}
		}
	}
	else //If the cloned object in the hierarchy should not have any child objects
	{
		//Clear all the childObjects if they were cloned from the prototype earlier
		for (auto& childObjects : _childObjects)
		{
			delete childObjects.second;
			MyFactory.RemoveChildGameObject(childObjects.first);
		}
		_childObjects.clear();
	}
}

//For Prototype Deserialisation
void GameObject::DeSerialise(/*std::string filePath*/ DeSerialiser& document)
{
	//IdentityComponent* IdComponent = dynamic_cast<IdentityComponent*> (_ComponentList[ComponentId::IDENTITY_COMPONENT]);
	//std::string fileName = "./Resources/TextFiles/GameObjects/" + IdComponent->ObjectType() + ".json";

	//DeSerialiser prototypeDoc(filePath);


	for (auto& ComponentPair : _ComponentList)
	{
		//rapidjson::Value value;
		//value.Clear();

		IComponent* component = ComponentPair.second;
		component->DeSerialiseComponent(document);
	}

	if (_childObjects.size()) //If there is any childObjects
	{
		rapidjson::Value haveChild(true);
		document.AddMember("HaveChild", haveChild);

		rapidjson::Value ChildObjects;
		ChildObjects.SetArray();

		for (auto& child: _childObjects)
		{
			//rapidjson::Value ChildObject;
			//ChildObject.SetObject();
			DeSerialiser childObj(document.GetAllocator());

			child.second->DeSerialise(childObj);

			ChildObjects.PushBack(childObj.getValue(), document.GetAllocator());
		}

		document.AddMember("ChildObjects", ChildObjects);

	}

}

void GameObject::DeSerialise( rapidjson::Value& document, rapidjson::MemoryPoolAllocator<>& allocator)
{
	IdentityComponent* comp = dynamic_cast<IdentityComponent*>(GetComponent(ComponentId::CT_Identity));

	GameObject* proObj = MyResourceSystem.GetPrototypeResource(comp->ObjectType());

	std::unordered_map <ComponentId, IComponent* >& comList = GetComponentList();

	if (proObj) //If Object actually exists in the Prototype List
	{
		std::unordered_map <ComponentId, IComponent* >& protoComList = proObj->GetComponentList(); //List of components in the prototype

		for (auto& protoComPair : protoComList)  //Go thru the componentlist in the prototype
		{
			//If the  object does not have a certain component from the Prototype.
			if (comList.find(protoComPair.first) == comList.end())
			{
				rapidjson::Value value;
				value.SetNull();
				document.AddMember(rapidjson::StringRef(ToString(protoComPair.first)), value, allocator); //Add component as null
			}
		}

		for (auto& IdComPair : comList)  //Go thru the componentlist in the current object
		{
			IComponent* protoCom = proObj->GetComponent(IdComPair.first);
			IdComPair.second->DeserialiseComponentSceneFile(protoCom, document, allocator);
		}

		//clonableObjects.PushBack(obj, SceneFile.Allocator());

	}
	else  //Object does not exists in PrototypeAssetList - Save in NonClonableObjects list
	{

		for (auto& IdComPair : comList)
		{
			//IComponent* protoCom = proObj->GetComponent(IdComPair.first);
			IdComPair.second->DeSerialiseComponent(document, allocator);
		}

	}


	if (_childObjects.size()) //If there is any childObjects in this current Object
	{
		rapidjson::Value haveChild(true);
		document.AddMember("HaveChild", haveChild, allocator);

		rapidjson::Value ChildObjects;
		ChildObjects.SetArray();
		
		for (auto& childObject : _childObjects)
		{
			DeSerialiser childObj(allocator);
			childObject.second->DeSerialise(childObj);
			ChildObjects.PushBack(childObj.getValue(), allocator);
		}
		
		document.AddMember("ChildObjects", ChildObjects, allocator);
	}
}


Map_ComponentList& GameObject::GetComponentList() // Get ComponentList
{
	return _ComponentList;
}

void GameObject::DestoryGameObject()
{
	MyFactory.Destroy(this);
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
	MyFactory.Destroy(this);
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

GameObject* GameObject::Clone(size_t uid)
{
	GameObject* newGameObject = new GameObject();
	newGameObject->_uId = uid;

	for (auto& it : _ComponentList)
	{
		IComponent* temp = nullptr;
		if (it.first == ComponentId::CT_Logic)
			temp = ((LogicComponent*)it.second)->CloneComponent(newGameObject, this);
		else
			temp = it.second->CloneComponent();

		temp->SetParentId(uid);
		temp->SetParentPtr(newGameObject);

		newGameObject->_ComponentList[it.first] = temp;

		//if(uid)
			MyComponentManger.GetComponentContainer(it.first)->insert({ uid, temp });
	}

	newGameObject->SetChild(_anyChild);
	newGameObject->SetIndependent(_independent);

	if (_anyChild)
	{
		for (auto& it : _childObjects)
		{
			GameObject* newChildObject = MyFactory.CloneChildGameObject(it.second);
			newChildObject->SetParent(newGameObject);

			newGameObject->AddChildObject(newChildObject);
		}
	}

	return newGameObject;
}

GameObject* GameObject::CloneChildPrototype()
{
	GameObject* newGameObject = new GameObject();
	newGameObject->_uId = 0;

	for (auto& it : _ComponentList)
	{
		IComponent* temp = nullptr;
		if (it.first == ComponentId::CT_Logic)
			temp = ((LogicComponent*)it.second)->CloneComponent(newGameObject, this);
		else
		{
			temp = it.second->CloneComponent();
			temp->SetParentId(0);
			temp->SetParentPtr(newGameObject);
		}

		newGameObject->_ComponentList[it.first] = temp;

	}

	newGameObject->SetChild(_anyChild);
	newGameObject->SetIndependent(_independent);

	if (_anyChild)
	{
		for (auto& it : _childObjects)
		{
			GameObject* newChildObject = MyFactory.CloneChildGameObjectPrototype(it.second);
			newChildObject->SetParent(newGameObject);

			newGameObject->AddChildObject(newChildObject);
		}
	}

	return newGameObject;
}

///////////////////////////////////////////////
bool GameObject::GetIndependent() const
{
	return _independent;
}

void GameObject::SetIndependent(bool independent)
{
	_independent = independent;
}

bool GameObject::GetChild() const
{
	return _anyChild;
}

void GameObject::SetChild(bool child)
{
	_anyChild = child;
}

GameObject* GameObject::GetParent() const
{
	return _parentObject;
}

void GameObject::SetParent(GameObject* parent)
{
	_parentObject = parent;
}

std::unordered_map<size_t, GameObject*>& GameObject::GetChildList()
{
	return _childObjects;
}

void GameObject::AddChildObject(GameObject* child)
{
	if (!child)
		return;

	if (child->Get_uID())
		_childObjects[child->Get_uID()] = child;
	else
		_childObjects[_childObjects.size()] = child;

	_anyChild = true;

	child->_independent = false;
	child->SetParent(this);
}

void GameObject::RemoveChildObject(GameObject* child)
{
	if (!child)
		return;

	if (_childObjects.find(child->Get_uID()) != _childObjects.end())
		_childObjects.erase(child->Get_uID());

	if (_childObjects.size() == 0)
		_anyChild = false;
}