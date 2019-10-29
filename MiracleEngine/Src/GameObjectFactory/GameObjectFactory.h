#pragma once
#include "PrecompiledHeaders.h"
#include "GameObject.h"
#include "GameStateManager/GameStateManager.h"
#include "GameObjectPrototype.h"

class GameObjectFactory final
{
private:
	GameObjectPrototype _prototypes;						//Dynamic array of GameObject Prototypes

	std::unordered_map < size_t, GameObject* > _listObject; //Dynamic array of GameObjects

	size_t _uId;											//Unique ID for the next newly created object

	std::unordered_map < size_t, GraphicComponent* >	 _graphicComponents;	//Array of Components
	std::unordered_map < size_t, TransformComponent* >  _transformComponents;	//
	std::unordered_map < size_t, RigidBody2D* >			_rigidBody2dComponents;	//
	std::unordered_map < size_t, Collider2D* >			_collider2dComponents;	//
	std::unordered_map < size_t, LogicComponent* >		_logicComponents;		//

public:
	GameObjectFactory(const GameObjectFactory& rhs) = delete;
	GameObjectFactory& operator= (const GameObjectFactory& rhs) = delete;


	GameObjectFactory();
	~GameObjectFactory();

	//GameObjectFactory& GetGOFac(); //Get Self

	const std::unordered_map < size_t, GraphicComponent* >& getGraphicComponent() const;		//Get Components
	std::unordered_map < size_t, TransformComponent* >& getTransformComponent();				//	
	const std::unordered_map < size_t, RigidBody2D* >& getRigidBodyComponent() const;			//
	const std::unordered_map < size_t, Collider2D* >& getCollider2dComponent() const;			//
	const std::unordered_map < size_t, LogicComponent* >& getLogicComponent() const;			//


	const std::unordered_map < size_t, GameObject*>& getObjectlist() const; //Get _listObject

	void FileRead_Level(const char* FileName);		//Read LevelText and Instantiate GObj //Level is read when NextGameState is In-GameState
	void DeleteLevel();								//Level is Deleted when out of In-GameState


	GameObject* CloneGameObject(TypeIdGO gameObjectTypeID); //Create a gameObject type along with its Components
	void DeleteGameObjectID(size_t id);						//Deleting a gameObject from _listObject



	void TEST_AddGameObjects()	// TEST FUNCTION - to add some GOs 'dyamically'
	{
		std::cout << std::endl
			<< "-------------------------------------" << std::endl;
		std::cout << "TEST_AddGameObjects()" << std::endl;
		CloneGameObject(TypeIdGO::PLAYER);
		CloneGameObject(TypeIdGO::ENEMY);
		CloneGameObject(TypeIdGO::ENEMY);
		CloneGameObject(TypeIdGO::WALL);
		CloneGameObject(TypeIdGO::WALL);
		CloneGameObject(TypeIdGO::WALL);
		std::cout
			<< "-------------------------------------" << std::endl;
	}

	void TEST_DeleteAllGameObjects()
	{
		std::cout << std::endl
			<< "-------------------------------------" << std::endl;
		std::cout << "TEST_DeleteAllGameObjects()" << std::endl;
		std::unordered_map < size_t, GameObject* >::iterator itr = _listObject.begin();
		while (itr != _listObject.end())
		{
			delete _listObject[itr->first];
			++itr;
		}
		_listObject.clear();

		std::cout << std::endl
			<< "-------------------------------------" << std::endl;
	}

	void TEST_DisplayAllGameObj()	// TEST FUNCTION - to see all GOs in _listObj
	{
		std::cout << std::endl
			<< "-------------------------------------" << std::endl;
		std::cout << "TEST_DisplayAllGameObj()" << std::endl;
		std::unordered_map < size_t, GameObject* >::iterator itr = _listObject.begin();
		while (itr != _listObject.end())
		{
			std::cout
				<< " || "
				<< itr->first << " : " << itr->second->_typeId
				<< " || " << std::endl;
			++itr;
		}
		std::cout
			<< "-------------------------------------" << std::endl;

		std::cout
			<< "-------------------------------------" << std::endl;
		std::cout
			<< "-------------------------------------" << std::endl;
		std::cout
			<< "-------------------------------------" << std::endl;

		itr = _listObject.begin();
		while (itr != _listObject.end())
		{
			std::cout << " || ";

			//Map_ComponentList a = (itr->second)->GetComponentList();
			//a[(unsigned)TypeIdComponent::GRAPHICSCOMPONENT]->GetOtherComponent(0);
			//((GraphicComponent*)a[(unsigned)TypeIdComponent::GRAPHICSCOMPONENT])->TEST_getTransform();

			// get graphicsComp
			GraphicComponent* a = (GraphicComponent*)(itr->second)->GetComponentList()[(unsigned)TypeIdComponent::GRAPHICSCOMPONENT];
			a->TEST_getTransform();
			// access the TEST_getTransform from graphicsComp

			std::cout << " || " << std::endl;
			++itr;
		}
	}
};