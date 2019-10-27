#pragma once
#include "PrecompiledHeaders.h"
#include "GameObjectComponents/GameObject.h"
#include "LogicSystem/GameState.h"


class ResourceManager
{
	//	start with the basic resources manager, single class that ctrl all loading freeing of HDD stuff
	//	not absolutely necessary to load ALL resources at start.
	//	GOFac should have a resources manager, which based on which level im loading, which assets I should load
	//	level file, at the top, should have a list of all assets to load, then loadand then continue the instancing of the level
	//	can worry about this after segment
	//	when saving a level in editor, it should save the assets necessary, and then save the instancing of the objects
	//	will have func() to load things like texture, obj prefabbing, audio, etc

	std::vector<std::string*> VecFilePaths; // for future use for dynamic file path getting	
};


typedef std::unordered_map<TypeIdGO, GameObject*> PrototypeList;


class GameObjectPrototype final // : ISingleton ????
{
	PrototypeList _listObjectPrototype;		//Dynaic array of GameObject Prototypes

public:
	GameObjectPrototype();
	~GameObjectPrototype();
	GameObjectPrototype(const GameObjectPrototype& rhs) = delete;
	GameObjectPrototype& operator=(const GameObjectPrototype& rhs) = delete;

	PrototypeList& GetPrototypeList();	// Get _listObjectProrotype

	GameObject* PrefabGameObject(TypeIdGO typeId);	// Create a gameObject type along with its Components

	void Init();	// InUpEx
	void Update();	//
	void Exit();	//
};



class GameObjectFactory final	//No inheritance - Static object
{
private:

	GameState _state; //Current GameState

	std::unordered_map < size_t, GameObject* > _listObject; //Dynamic array of GameObjects

	GameObjectPrototype _prototypes; //Dynaic array of GameObject Prototypes

	size_t _uId; //Unique ID for the next newly created object

	std::unordered_map < size_t, GraphicComponent* >  _graphicComponents;		//Array of Components
	std::unordered_map < size_t, TransformComponent* >  _transformComponents;	//
	std::unordered_map < size_t, RigidBody2D* >  _rigidBody2dComponents;		//
	std::unordered_map < size_t, Collider2D* >  _collider2dComponents;			//
	std::unordered_map < size_t, LogicComponent* >  _logicComponents;			//

public:

	GameObjectFactory();
	~GameObjectFactory();
	GameObjectFactory(const GameObjectFactory& rhs) = delete;
	GameObjectFactory& operator= (const GameObjectFactory& rhs) = delete;


	GameObjectFactory& GetGOFac(); //Get Self

	const std::unordered_map < size_t, GraphicComponent* >& getGraphicComponent() const;		//Get Components
	const std::unordered_map < size_t, TransformComponent* >& getTransformComponent() const;	//	
	const std::unordered_map < size_t, RigidBody2D* >& getRigidBodyComponent() const;			//
	const std::unordered_map < size_t, Collider2D* >& getCollider2dComponent() const;			//
	const std::unordered_map < size_t, LogicComponent* >& getLogicComponent() const;			//


	const std::unordered_map < size_t, GameObject*>& getObjectlist() const; //Get _listObject

	void DeleteGameObjectID(size_t id); //Deleting a gameObject entirely from the gameObjectFactory

	GameObject* CreateGameObject(TypeIdGO typeId); //Create a gameObject type along with its Components

	GameObject* CloneGameObject(TypeIdGO gameObjectTypeID); //Create a gameObject type along with its Components

	void Init();	//InUpEx
	void Update();	//
	void Exit();	//

	void FileRead_Level(const char* FileName); //Read LevelText and Instantiate GObj

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
	}
};