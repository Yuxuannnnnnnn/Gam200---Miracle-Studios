#include "PrecompiledHeaders.h"
#include "GameObject.h"

//-----------------------------------
// IGameObject : ISerial
// START
//-----------------------------------
IGameObject::IGameObject(unsigned uId)
	:_uId{ uId }
{
}

IGameObject::~IGameObject()
{
	std::map< ComponentTypes, IComponentSystem* >::iterator iterator = _ComponentList.begin();
	while (iterator != _ComponentList.end())
	{
		delete iterator->second;
		iterator++;
	}
}

std::string IGameObject::GameObjectType() const
{
	return "test";
}

//Add a specific component to the GameObject
IComponentSystem* IGameObject::addcomponent(ComponentTypes componentType)
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
	}
	return  _ComponentList[componentType];
}

// 'addcomponent' Varient for Serialization, allows addComponent during serialization
void IGameObject::SerialAddComponent
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
	}
}

// Cloning IGO
IGameObject* IGameObject::Clone(Vector3 pos, Vector3 scale, float rotate)
{
	return new IGameObject();
}

//-----------------------------------
// END
// IGameObject
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