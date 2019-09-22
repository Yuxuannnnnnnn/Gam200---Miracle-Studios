#pragma once

#include "GameObject.h"


//No inheritance 
//Static object
class GameObjectFactory final
{
private:

	//Dynamic array of GameObjects
	std::map < size_t, IGameObject* > _listObject;
	//Unique ID for the next newly created object
	size_t _id;

	//Array of GraphicComponents for GraphicsSystem
	std::map < size_t, GraphicComponent* >  _graphicComponents;
	//Array of TransformComponents for GraphicsSystem
	std::map < size_t, TransformComponent* >  _transformComponents;	
	//Array of RigidBodyComponent 
	std::map < size_t, RigidBodyComponent* >  _rigidBodyComponents;	
	//Array of PhysicsComponent 
	std::map < size_t, PhysicsComponent* >  _physicsComponent;

public:
	//No replication of class object
	GameObjectFactory(const GameObjectFactory& rhs) = delete;
	GameObjectFactory& operator= (const GameObjectFactory& rhs) = delete;

	GameObjectFactory() 
		:_id{ 0 }
	{}


	const std::map < size_t, GraphicComponent* >& getGraphicComponent() const
	{
		return _graphicComponents;
	}	
	
	const std::map < size_t, TransformComponent* >& getTransformComponent() const
	{
		return _transformComponents;
	}	
	
	const std::map < size_t, RigidBodyComponent* >& getRigidBodyComponent() const
	{
		return _rigidBodyComponents;
	}	
	
	const std::map < size_t, PhysicsComponent* >& getPhysicsComponent() const
	{
		return _physicsComponent;
	}


	const std::map<size_t, IGameObject*>& getObjectlist() const
	{
		return _listObject;
	}

	//Deleting a gameObject entirely from the gameObjectFactory
	void DeleteGameObjectID(size_t id)
	{
		delete _listObject[id];

		_listObject.erase(id);
		_graphicComponents.erase(id);
		_transformComponents.erase(id);
		_rigidBodyComponents.erase(id);
		_physicsComponent.erase(id);
	}

	//Deletes all gameObjects in the gameObjectFactory
	~GameObjectFactory() 
	{
		for (auto gameObject : _listObject)
		{
			delete gameObject.second;
			//_listObject.erase(gameObject.first);
		}
		//for (size_t i = 0; i < _listObject.size(); i++)
		//{
		//
		//	std::map < size_t, IGameObject* >::iterator it = _listObject.begin();
		//	delete it->second;
		//	it++;
		//}
	}

	//Create a gameObject type along with its Components
	IGameObject* CreateGameObject(GameObjectID gameObjectID)
	{
		IGameObject* gameObject = nullptr;

		switch (gameObjectID)
		{
		case PLAYER:
			gameObject = new Player(_id);
			_listObject[_id] = gameObject;

			_transformComponents[_id] = dynamic_cast<TransformComponent*> (gameObject->addcomponent(TRANSFORMCOMPONENT));
			_graphicComponents[_id] = dynamic_cast<GraphicComponent*> (gameObject->addcomponent(GRAPHICSCOMPONENT));
			_rigidBodyComponents[_id] = dynamic_cast<RigidBodyComponent*> (gameObject->addcomponent(RIGIDBODYCOMPONENT));
			_physicsComponent[_id] = dynamic_cast<PhysicsComponent*> (gameObject->addcomponent(PHYSICSCOMPONENT));

			_id++;
			break;

		//Other Objects
		}

		return gameObject;
	}

};
