#include "PrecompiledHeaders.h"
#include "GameObject.h"

//-----------------------------------
// GameObject : ISerial
// START
//-----------------------------------
GameObject::GameObject(size_t uId, size_t typeId)
	:_uId{ uId }, _typeId{ typeId }
{
	std::cout << "GameObject::GameObject()" << std::endl;
}

GameObject::~GameObject()
{
	std::cout << "GameObject::~GameObject()" << std::endl;
	std::unordered_map< ComponentTypes, IComponentSystem* >::iterator iterator = _ComponentList.begin();
	while (iterator != _ComponentList.end())
	{
		delete iterator->second;
		iterator++;
	}
}

GameObjectTypeID GameObject::GameObjectType() const
{
	return (GameObjectTypeID)_typeId;
}

//Add a specific component to the GameObject
IComponentSystem* GameObject::addcomponent(ComponentTypes componentType)
{
	switch (componentType)
	{
	case TRANSFORMCOMPONENT:
		_ComponentList[TRANSFORMCOMPONENT] = new TransformComponent();
		break;
	case GRAPHICSCOMPONENT:
		_ComponentList[GRAPHICSCOMPONENT] = new GraphicComponent();
		break;
	case RIGIDBODYCOMPONENT:
		_ComponentList[RIGIDBODYCOMPONENT] = new RigidBody2D();
		break;
	case COLLIDERCOMPONENT:
		_ComponentList[COLLIDERCOMPONENT] = new Collider2D();
		break;
	case LOGICCOMPONENT:
		_ComponentList[LOGICCOMPONENT] = new LogicComponent();
		break;
	}
	return  _ComponentList[componentType];
}

// 'addcomponent' Varient for Serialization, allows addComponent during serialization
void GameObject::SerialAddComponent
	(ComponentTypes componentType, rapidjson::Value& s, rapidjson::Document& d)
{
	std::cout << "\t GameObject::SerialAddComponent(" << componentType << ") : ";
	switch (componentType)
	{
		IComponentSystem* temp;
	case TRANSFORMCOMPONENT:
		std::cout << "Transform";
		_ComponentList[TRANSFORMCOMPONENT] = new TransformComponent();
		temp = _ComponentList[TRANSFORMCOMPONENT];
		s = d["Position"];
		JsonDynamicStore(((TransformComponent*)temp)->GetPos(), s);
		s = d["Scale"];
		JsonDynamicStore(((TransformComponent*)temp)->GetScale(), s);
		s = d["Rotate"];
		JsonDynamicStore(((TransformComponent*)temp)->GetRotate(), s);
		break;
	case GRAPHICSCOMPONENT:
		std::cout << "Graphics";
		_ComponentList[GRAPHICSCOMPONENT] = new GraphicComponent();
		break;
	case RIGIDBODYCOMPONENT:
		std::cout << "R. Body";
		_ComponentList[RIGIDBODYCOMPONENT] = new RigidBody2D();
		temp = _ComponentList[RIGIDBODYCOMPONENT];
		s = d["Mass"];
		JsonDynamicStore(((RigidBody2D*)temp)->_mass, s);
		s = d["Friction"];
		JsonDynamicStore(((RigidBody2D*)temp)->_fictionVal, s);
		s = d["Static"];
		JsonDynamicStore(((RigidBody2D*)temp)->_static, s);
		break;
	case COLLIDERCOMPONENT:
		std::cout << "Collider";
		_ComponentList[COLLIDERCOMPONENT] = new Collider2D();
		temp = _ComponentList[COLLIDERCOMPONENT];
		s = d["ColliderTypeId"];
		JsonDynamicStore(((Collider2D*)temp)->_type, s);
		break;
	case LOGICCOMPONENT:
		std::cout << "Logic";
		_ComponentList[LOGICCOMPONENT] = new LogicComponent();
		temp = _ComponentList[LOGICCOMPONENT];
		s = d["ScriptId"];
		JsonDynamicStore(((LogicComponent*)temp)->GetScriptId(), s);
		s = d["Health"];
		JsonDynamicStore(((LogicComponent*)temp)->GetHealth(), s);
		s = d["Speed"];
		JsonDynamicStore(((LogicComponent*)temp)->GetSpeed(), s);
		break;
	default:
		temp = nullptr;
		break;
	}
	std::cout << std::endl;
}

void GameObject::CopyComponent
	(std::unordered_map< ComponentTypes, IComponentSystem* >& original)
{
	std::cout << "\t\t GameObject::CopyComponent() : ";
	std::unordered_map< ComponentTypes, IComponentSystem* >::iterator itr = original.begin();
	while (itr != original.end())
	{
		IComponentSystem* temp;
		switch (itr->first)
		{
		case TRANSFORMCOMPONENT:
			std::cout << "Transform, ";
			temp = new TransformComponent(
				*((TransformComponent*)itr->second)
			); // using copyCtor to copy var, idk if it works
			_ComponentList[TRANSFORMCOMPONENT] =  temp;
			break;
		case GRAPHICSCOMPONENT:
			std::cout << "Graphics, ";
			_ComponentList[GRAPHICSCOMPONENT] = new GraphicComponent();
			break;
		case RIGIDBODYCOMPONENT:
			std::cout << "R. Body, ";
			temp = new RigidBodyComponent(
				*((RigidBodyComponent*)itr->second)
			);
			_ComponentList[RIGIDBODYCOMPONENT] = temp;
			break;
		case COLLIDERCOMPONENT:
			std::cout << "Collider, ";
			temp = new Collider2D(
				*((Collider2D*)itr->second)
			);
			_ComponentList[COLLIDERCOMPONENT] = temp;
			break;
		case LOGICCOMPONENT:
			std::cout << "Logic, ";
			temp = new LogicComponent(
				*((LogicComponent*)itr->second)
			);
			_ComponentList[LOGICCOMPONENT] = temp;

			//_ComponentList[LOGICCOMPONENT] = new LogicComponent();
			//temp = _ComponentList[LOGICCOMPONENT];
			//s = d["ScriptId"];
			//JsonDynamicStore(((LogicComponent*)temp)->GetScriptId(), s);
			//s = d["Health"];
			//JsonDynamicStore(((LogicComponent*)temp)->GetHealth(), s);
			//s = d["Speed"];
			//JsonDynamicStore(((LogicComponent*)temp)->GetSpeed(), s);
			break;
		default:
			temp = nullptr;
			break;
		}
		++itr;
	}
	std::cout << std::endl;
}

// delete all components in _ComponentList
void GameObject::DeleteAllComponents()
{
	for (auto comp : _ComponentList)
	{
		delete comp.second;
	}
}

// Cloning IGO
GameObject* GameObject::Clone()
{
	std::cout << "GameObject::Clone()" << std::endl;
	GameObject* temp = new GameObject(_uId, _typeId);
	// copy _ComponentList;
	temp->CopyComponent(_ComponentList);
	// return GO so that can put into GOFac's _listObj
	return temp;
}

//-----------------------------------
// END
// GameObject
//-----------------------------------



//-----------------------------------
// Weapon : IGO
// START
//-----------------------------------
//-----------------------------------
// END
// Weapon : IGO
//-----------------------------------


//-----------------------------------
// PLAYER : IGO
// START
//-----------------------------------
//-----------------------------------
// END
// PLAYER : IGO
//-----------------------------------