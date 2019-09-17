#pragma once
#include <vector>
#include "GameObject.h"


//No inheritance 
//Static object
class GameObjectFactory final
{
	//Dynamic array of GameObjects
	std::vector<IGameObject*> _ListObject;

public:
	//No replication of class object
	GameObjectFactory(const GameObjectFactory& rhs) = delete;
	GameObjectFactory& operator= (const GameObjectFactory& rhs) = delete;

	GameObjectFactory() 
		:_ListObject{nullptr}
	{}

	//Deletes all gameObjects in the list
	~GameObjectFactory() 
	{
		std::vector<IGameObject*>::iterator iterator = _ListObject.begin();
		while (iterator != _ListObject.end())
		{
			delete *iterator;
			iterator++;
		}
	}

	IGameObject* CreateGameObject(GameObjectID gameObjectID)
	{
		switch (gameObjectID)
		{
		case PLAYER:
			_ListObject.emplace_back(new Player());
		//Other Objects
		}
	}

};
