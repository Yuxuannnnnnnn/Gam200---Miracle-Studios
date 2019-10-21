#pragma once
#include "PrecompiledHeaders.h"
#include "GameObject.h"

class ResourceManager
{
	//	start with the basic resources manager, single class that ctrl all loading freeing of HDD stuff
	//	not absolutely necessary to load ALL resources at start.
	//	GOFac should have a resources manager, which based on which level im loading, which assets I should load
	//	level file, at the top, should have a list of all assets to load, then loadand then continue the instancing of the level
	//	can worry about this after segment
	//	when saving a level in editor, it should save the assets necessary, and then save the instancing of the objects
	//	will have func() to load things like texture, obj prefabbing, audio, etc
};

typedef std::unordered_map<GameObjectTypeID, GameObject*> PrototypeList;

class GameObjectProrotype // : ISingleton ????
{
	//Dynaic array of GameObject Prototypes
	PrototypeList _listObjectPrototype;
public:
	GameObjectProrotype() {}
	~GameObjectProrotype()
	{
		for (auto gameObject : _listObjectPrototype)
			delete gameObject.second;
	}
	PrototypeList& GetPrototypeList()
	{
		return _listObjectPrototype;
	}

	//Create a gameObject type along with its Components
	GameObject* PrefabGameObject(GameObjectTypeID typeId)
	{
		size_t uId = 0;
		GameObject* gameObject = nullptr;
		switch (typeId)
		{
		case PLAYER:
			gameObject = new Player(uId);
			gameObject->SerialInPrefab();
			break;
		case WALL:
			break;
			//Other Objects
		}
		return gameObject;
	}

	//Create a gameObject type along with its Components
	GameObject* CloneGameObject(GameObjectTypeID typeId)
	{
		GameObject* gameObject = nullptr;

		switch (typeId)
		{
		case PLAYER:
			//gameObject = new Player(0);
			//gameObject->SerialInPrefab();
			break;
		case WALL:
			break;
			//Other Objects
		}
		return gameObject;
	}

	// call on start up
	void Init() {
		// get all prorotypes and save it into the _listObjectPrototype(map)
		// get list of all objects
	//	std::vector<std::string>listOfObjs =
	//		FileRead_FileToStringVector("./Resources/TextFiles/ListOfGameObjects.txt");
				//_listObjectPrototype.insert(std::pair < GameObjectTypeID, GameObject*>(PLAYER, CreateGameObject(PLAYER)));
				//_listObjectPrototype.insert(std::pair < GameObjectTypeID, GameObject*>(WALL, CreateGameObject(WALL)));
		// serialise each object
	}
	void Update() { // works as Load()

	}
	void Exit() {
	}
};


//No inheritance 
//Static object
class GameObjectFactory final
{
private:

//Dynamic array of GameObjects
	std::unordered_map < size_t, GameObject* > _listObject;
//Dynaic array of GameObject Prototypes
	PrototypeList _listObjectPrototype;

//Unique ID for the next newly created object
	size_t _uId;

//Array of GraphicComponents for GraphicsSystem
	std::unordered_map < size_t, GraphicComponent* >  _graphicComponents;
//Array of TransformComponents for GraphicsSystem
	std::unordered_map < size_t, TransformComponent* >  _transformComponents;
//Array of RigidBodyComponent 
	std::unordered_map < size_t, RigidBodyComponent* >  _rigidBodyComponents;
//Array of PhysicsComponent 
	std::unordered_map < size_t, PhysicsComponent* >  _physicsComponent;
//Array of LogicComponent 
	std::unordered_map < size_t, LogicComponent* >  _logicComponent;

public:
//No replication of class object
	GameObjectFactory(const GameObjectFactory& rhs) = delete;
	GameObjectFactory& operator= (const GameObjectFactory& rhs) = delete;

//Constructor
	GameObjectFactory();
//Destructor
	~GameObjectFactory();
//Get self
	GameObjectFactory* GetGOFac();
//Get Components
	const std::unordered_map < size_t, GraphicComponent* >& getGraphicComponent() const;
	const std::unordered_map < size_t, TransformComponent* >& getTransformComponent() const;
	const std::unordered_map < size_t, RigidBodyComponent* >& getRigidBodyComponent() const;
	const std::unordered_map < size_t, PhysicsComponent* >& getPhysicsComponent() const;

	const std::unordered_map < size_t, GameObject*>& getObjectlist() const;

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

//Create a gameObject type along with its Components
	GameObject* CreateGameObject(GameObjectTypeID typeId)
	{
		GameObject* gameObject = nullptr;

		switch (typeId)
		{
		case PLAYER:
			gameObject = new Player(_uId);
			_listObject[_uId] = gameObject;

			_transformComponents[_uId] = dynamic_cast<TransformComponent*> (gameObject->addcomponent(TRANSFORMCOMPONENT));
			_graphicComponents[_uId] = dynamic_cast<GraphicComponent*> (gameObject->addcomponent(GRAPHICSCOMPONENT));
			_rigidBodyComponents[_uId] = dynamic_cast<RigidBodyComponent*> (gameObject->addcomponent(RIGIDBODYCOMPONENT));
			_physicsComponent[_uId] = dynamic_cast<PhysicsComponent*> (gameObject->addcomponent(PHYSICSCOMPONENT));

			_uId++;
			break;
		case WALL:
			break;
			//Other Objects
		}
		return gameObject;
	}
//Create a gameObject type along with its Components
	GameObject* CloneGameObject(GameObjectTypeID gameObjectTypeID)
	{
		(void)gameObjectTypeID;
		_listObjectPrototype[PLAYER];
	}
	void ObjectClone()
	{
		// clone from prototype, based on desired type

	}

	// call on start up
	void Init() {
		// get all prorotypes and save it into the _listObjectPrototype(map)
		// get list of all objects
	//	std::vector<std::string>listOfObjs =
	//		FileRead_FileToStringVector("./Resources/TextFiles/ListOfGameObjects.txt");
		_listObjectPrototype.insert(std::pair < GameObjectTypeID, GameObject*>(PLAYER, CreateGameObject(PLAYER)));
		_listObjectPrototype.insert(std::pair < GameObjectTypeID, GameObject*>(WALL, CreateGameObject(WALL)));
		// serialise each object
	}
	void Update() { // works as Load()

	}
	void Exit() {

	}

	struct TempGO {
		int id{ 0 };
		Vector3 pos{ Vector3() };
		Vector3 scale{ Vector3() };
		float rot{ 0.0f };
		//int scriptId{ 0 };
	// funcs()
		TempGO() {}
		~TempGO() {}
	};
	/**
	\brief Read LevelText and Instantiate GObj
	*/
	std::vector<GameObject*> FileRead_Level(const char* FileName)
	{ // will move to ObjectFactory
		std::fstream _file;
		_file.open(FileName, std::ios_base::in | std::ios_base::binary);
		if (!_file.is_open())
		{
			std::cout << "! WARNING !! File Cannot Open!!!" << std::endl
				<< ". // Resources // TextFiles // TestLevel.txt" << std::endl;
			std::vector<GameObject*> null;
			return null;
		}
		char* strType = new char[20];
		char* strNum1 = new char[10];
		char* strNum2 = new char[10];
		std::vector<TempGO> GOVec;
		float num1, num2;
		TempGO obj;

		while (_file.good()) // each loop read 4 lines: Type, Pos, Scale, Rot
		{
			// get Type
			//_file.getline(strType, 20, '\n\r');
			_file >> strType;
			if (std::strcmp(strType, "Wall") == 0)
				obj.id = WALL;
			if (std::strcmp(strType, "Floor") == 0)
				obj.id = FLOOR;
			if (std::strcmp(strType, "Player") == 0)
				obj.id = PLAYER;
			// get Position
			ASSERT(_file.getline(strNum1, 10, ','));
			ASSERT(_file.getline(strNum2, 10));
			num1 = std::stof(strNum1);
			num2 = std::stof(strNum2);
			obj.pos = Vector3(num1, num2, 1);
			// get Scale
			ASSERT(_file.getline(strNum1, 10, ','));
			ASSERT(_file.getline(strNum2, 10));
			num1 = std::stof(strNum1);
			num2 = std::stof(strNum2);
			obj.scale = Vector3(num1, num2, 1);
			// get Rotate
			ASSERT(_file.getline(strNum1, 10));
			num1 = std::stof(strNum1);
			obj.rot = num1;
			// push into tempVec
			GOVec.push_back(obj);
		}
		_file.close();
		delete[] strType;
		delete[] strNum1;
		delete[] strNum2;

		// instantiate objs into objList
		std::vector<GameObject*> ret;
		std::vector<TempGO>::iterator itr = GOVec.begin();
		while (itr != GOVec.end())
		{
			TempGO temp = *itr;
			if (temp.id == PLAYER)
				ret.push_back(_listObjectPrototype[PLAYER]->Clone(temp.pos, temp.scale, temp.rot));
			else if (temp.id == FLOOR)
				ret.push_back(_listObjectPrototype[FLOOR]->Clone(temp.pos, temp.scale, temp.rot));
			else if (temp.id == WALL)
				ret.push_back(_listObjectPrototype[WALL]->Clone(temp.pos, temp.scale, temp.rot));
			else;
			++itr;
		}
		return ret;
	}
};