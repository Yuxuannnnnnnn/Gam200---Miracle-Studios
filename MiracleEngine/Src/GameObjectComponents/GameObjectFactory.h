#pragma once
#include "PrecompiledHeaders.h"
#include "GameObject.h"
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
class GameObjectProrotype final // : ISingleton ????
{
	//Dynaic array of GameObject Prototypes
	PrototypeList _listObjectPrototype;
public:
	GameObjectProrotype();
	~GameObjectProrotype();
	GameObjectProrotype(const GameObjectProrotype& rhs) = delete;
	GameObjectProrotype& operator=(const GameObjectProrotype& rhs) = delete;

// Get _listObjectProrotype
	PrototypeList& GetPrototypeList();

// Create a gameObject type along with its Components
	GameObject* PrefabGameObject(TypeIdGO typeId);

// Create a gameObject type along with its Components
	GameObject* CloneGameObject(TypeIdGO typeId);

// InUpEx
	void Init();
	void Update();
	void Exit();
};


//No inheritance 
//Static object
class GameObjectFactory final
{
private:
//Current GameState
	GameState _state;
//Dynamic array of GameObjects
	std::unordered_map < size_t, GameObject* > _listObject;
//Dynaic array of GameObject Prototypes
	GameObjectProrotype _prototypes;

//Unique ID for the next newly created object
	size_t _uId;

//Array of Components
	std::unordered_map < size_t, GraphicComponent* >  _graphicComponents;
	std::unordered_map < size_t, TransformComponent* >  _transformComponents;
	std::unordered_map < size_t, RigidBody2D* >  _rigidBody2dComponents;
	std::unordered_map < size_t, Collider2D* >  _collider2dComponents;
	std::unordered_map < size_t, LogicComponent* >  _logicComponents;

public:
	GameObjectFactory();
	~GameObjectFactory();
	GameObjectFactory(const GameObjectFactory& rhs) = delete;
	GameObjectFactory& operator= (const GameObjectFactory& rhs) = delete;
//Get Self
	GameObjectFactory& GetGOFac();
//Get Components
	const std::unordered_map < size_t, GraphicComponent* >& getGraphicComponent() const;
	const std::unordered_map < size_t, TransformComponent* >& getTransformComponent() const;
	const std::unordered_map < size_t, RigidBody2D* >& getRigidBodyComponent() const;
	const std::unordered_map < size_t, Collider2D* >& getCollider2dComponent() const;
	const std::unordered_map < size_t, LogicComponent* >& getLogicComponent() const;
//Get _listObject
	const std::unordered_map < size_t, GameObject*>& getObjectlist() const;

//Deleting a gameObject entirely from the gameObjectFactory
	void DeleteGameObjectID(size_t id);

//Create a gameObject type along with its Components
	GameObject* CreateGameObject(TypeIdGO typeId);
//Create a gameObject type along with its Components
	void CloneGameObject(TypeIdGO gameObjectTypeID);

//InUpEx
	void Init();
	void Update();
	void Exit();

//Read LevelText and Instantiate GObj
	std::vector<GameObject*> FileRead_Level(const char* FileName);



// TEST FUNCTION - to add some GOs 'dyamically'
	void TEST_AddGameObjects()
	{
		std::cout << std::endl << "-------------------------------------" << std::endl;
		std::cout << "TEST_AddGameObjects()" << std::endl;
		CloneGameObject(TypeIdGO::PLAYER);
		CloneGameObject(TypeIdGO::PLAYER);
		std::cout << std::endl << "-------------------------------------" << std::endl;
	}
	void TEST_DeleteAllGameObjects()
	{
		std::cout << std::endl << "-------------------------------------" << std::endl;
		std::cout << "TEST_DeleteAllGameObjects()" << std::endl;
		std::unordered_map < size_t, GameObject* >::iterator itr = _listObject.begin();
		while (itr != _listObject.end())
		{
			delete _listObject[itr->first];
			++itr;
		}
		_listObject.clear();

		std::cout << std::endl << "-------------------------------------" << std::endl;
	}
// TEST FUNCTION - to see all GOs in _listObj
	void TEST_DisplayAllGameObj()
	{
		std::cout << std::endl << "-------------------------------------" << std::endl;
		std::cout << "TEST_DisplayAllGameObj()" << std::endl;
		std::unordered_map < size_t, GameObject* >::iterator itr = _listObject.begin();
		while (itr != _listObject.end())
		{
			std::cout << " " << itr->first << " : " << itr->second->_typeId;
			++itr;
		}
		std::cout << std::endl << "-------------------------------------" << std::endl;
	}
};