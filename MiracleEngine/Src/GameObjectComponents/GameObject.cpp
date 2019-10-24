#include "PrecompiledHeaders.h"
#include "GameObject.h"

//-----------------------------------
// GameObject : ISerial
// START
//-----------------------------------
GameObject::GameObject(size_t uId, size_t typeId)
	:_uId{ uId }, _typeId{ typeId }
{
}

GameObject::~GameObject()
{
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
		_ComponentList[RIGIDBODYCOMPONENT] = new RigidBodyComponent();
		break;
	case PHYSICSCOMPONENT:
		_ComponentList[PHYSICSCOMPONENT] = new PhysicsComponent();
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
	switch (componentType)
	{
		IComponentSystem* temp;
	case TRANSFORMCOMPONENT:
		_ComponentList[TRANSFORMCOMPONENT] = new TransformComponent();
		temp = _ComponentList[TRANSFORMCOMPONENT];
		s = d["Position"];
		JsonDynamicStore(((TransformComponent*)temp)->GetPos(), s);
		s = d["Scale"];
		JsonDynamicStore(((TransformComponent*)temp)->GetScale(), s);
		s = d["Rotate"];
		JsonDynamicStore(((TransformComponent*)temp)->GetRotate(), s);
		return;
	case GRAPHICSCOMPONENT:
		_ComponentList[GRAPHICSCOMPONENT] = new GraphicComponent();
		return;
	case RIGIDBODYCOMPONENT:
		_ComponentList[RIGIDBODYCOMPONENT] = new RigidBodyComponent();
		return;
	case PHYSICSCOMPONENT:
		_ComponentList[PHYSICSCOMPONENT] = new PhysicsComponent();
		return;
	case LOGICCOMPONENT:
		_ComponentList[LOGICCOMPONENT] = new LogicComponent();
		temp = _ComponentList[LOGICCOMPONENT];
		s = d["ScriptId"];
		JsonDynamicStore(((LogicComponent*)temp)->GetScriptId(), s);
		s = d["Health"];
		JsonDynamicStore(((LogicComponent*)temp)->GetHealth(), s);
		s = d["Speed"];
		JsonDynamicStore(((LogicComponent*)temp)->GetSpeed(), s);
		return;
	}
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
GameObject* GameObject::Clone(Vector3 pos, Vector3 scale, float rotate)
{
	(void)pos; (void)scale; (void)rotate;
	return new Player(0);
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