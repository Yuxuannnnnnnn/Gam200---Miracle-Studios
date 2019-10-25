#include "PrecompiledHeaders.h"
#include "GameObjectFactory.h"

//Constructor
GameObjectFactory::GameObjectFactory()
	:_uId{ 0 }
{
}

//Destructor
//Deletes all gameObjects in the gameObjectFactory
GameObjectFactory::~GameObjectFactory()
{
	for (auto gameObject : _listObject)
	{
		delete gameObject.second;
		//_listObject.erase(gameObject.first);
	}
	//for (size_t i = 0; i < _listObject.size(); i++)
	//{
	//
	//	std::map < size_t, GameObject* >::iterator it = _listObject.begin();
	//	delete it->second;
	//	it++;
	//}
}

GameObjectFactory* GameObjectFactory::GetGOFac()
{
	return this;
}

const std::unordered_map < size_t, GraphicComponent* >&
GameObjectFactory::getGraphicComponent() const
{
	return _graphicComponents;
}

const std::unordered_map < size_t, TransformComponent* >&
GameObjectFactory::getTransformComponent() const
{
	return _transformComponents;
}

const std::unordered_map < size_t, RigidBodyComponent* >&
GameObjectFactory::getRigidBodyComponent() const
{
	return _rigidBodyComponents;
}

const std::unordered_map < size_t, PhysicsComponent* >&
GameObjectFactory::getPhysicsComponent() const
{
	return _physicsComponents;
}

const std::unordered_map < size_t, LogicComponent* >&
GameObjectFactory::getLogicComponent() const
{
	return _logicComponents;
}

const std::unordered_map<size_t, GameObject*>&
GameObjectFactory::getObjectlist() const
{
	return _listObject;
}