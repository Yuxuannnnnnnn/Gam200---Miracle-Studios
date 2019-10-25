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
		case TYPE_PLAYER:
			gameObject = new Player(uId);
			gameObject->SerialInPrefab();
			break;
		case TYPE_WALL:
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
		case TYPE_PLAYER:
			//gameObject = new Player(0);
			//gameObject->SerialInPrefab();
			break;
		case TYPE_WALL:
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
		// remove all GOs
	}
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
	std::unordered_map < size_t, PhysicsComponent* >  _physicsComponents;
//Array of LogicComponent 
	std::unordered_map < size_t, LogicComponent* >  _logicComponents;

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
	const std::unordered_map < size_t, LogicComponent* >& getLogicComponent() const;

	const std::unordered_map < size_t, GameObject*>& getObjectlist() const;

//Deleting a gameObject entirely from the gameObjectFactory
	void DeleteGameObjectID(size_t id)
	{
		std::cout << "DeleteGameObjectID(" << id << ")" << std::endl;
		delete _listObject[id];

		_listObject.erase(id);
		_graphicComponents.erase(id);
		_transformComponents.erase(id);
		_rigidBodyComponents.erase(id);
		_physicsComponents.erase(id);
	}

//Create a gameObject type along with its Components
	GameObject* CreateGameObject(GameObjectTypeID typeId)
	{
		std::cout << "CreateGameObject(" << typeId << ")" << std::endl;
		GameObject* gameObject = nullptr;

		switch (typeId)
		{
		case TYPE_PLAYER:
			gameObject = new Player(_uId);
			_listObject[_uId] = gameObject;

			_transformComponents[_uId] = dynamic_cast<TransformComponent*> (gameObject->addcomponent(TRANSFORMCOMPONENT));
			_graphicComponents[_uId] = dynamic_cast<GraphicComponent*> (gameObject->addcomponent(GRAPHICSCOMPONENT));
			_rigidBodyComponents[_uId] = dynamic_cast<RigidBodyComponent*> (gameObject->addcomponent(RIGIDBODYCOMPONENT));
			_physicsComponents[_uId] = dynamic_cast<PhysicsComponent*> (gameObject->addcomponent(PHYSICSCOMPONENT));

			_uId++;
			break;
		case TYPE_WALL:
			break;
			//Other Objects
		}
		return gameObject;
	}
//Create a gameObject type along with its Components
	void CloneGameObject(GameObjectTypeID gameObjectTypeID)
	{
		std::cout << "\t CloneGameObject(" << gameObjectTypeID << ")" << std::endl;
		GameObject* temp = nullptr;
		switch (gameObjectTypeID)
		{
		case TYPE_PLAYER:
			temp = _listObjectPrototype[TYPE_PLAYER]->Clone();
			break;
		default:
			break;
		}
		// add 'temp' to the _listObj;
		if (!temp)
			return;
		_listObject.insert(std::pair<size_t, GameObject*>(++_uId, temp));
		// based on temp's _ComponentList, add the components into GOFac's different systems
		std::unordered_map< ComponentTypes, IComponentSystem* >::iterator itr = temp->_ComponentList.begin();
		while (itr != temp->_ComponentList.end())
		{
			switch (itr->first)
			{
			case TRANSFORMCOMPONENT:
				_transformComponents[_uId] = (TransformComponent*)itr->second;
				break;
			case GRAPHICSCOMPONENT:
				_graphicComponents[_uId] = (GraphicComponent*)itr->second;
				break;
			case RIGIDBODYCOMPONENT:
				_rigidBodyComponents[_uId] = (RigidBodyComponent*)itr->second;
				break;
			case PHYSICSCOMPONENT:
				_physicsComponents[_uId] = (PhysicsComponent*)itr->second;
				break;
			case LOGICCOMPONENT:
				_logicComponents[_uId] = (LogicComponent*)itr->second;
				break;
			}
			++itr;
		}
	}
	void ObjectClone()
	{
		// clone from prototype, based on desired type

	}

//InUpEx
	void Init() {
		std::cout << "GOFac Init" << std::endl;
		_state.Init();

		// get all prorotypes and save it into the _listObjectPrototype(map)
		// get list of all objects
	//	std::vector<std::string>listOfObjs =
	//		FileRead_FileToStringVector("./Resources/TextFiles/ListOfGameObjects.txt");
		GameObject* temp = nullptr;
	// Prototype_Player
		temp = new GameObject(0, TYPE_PLAYER);
		temp->SerialInPrefab_Player();
		_listObjectPrototype.insert(std::pair < GameObjectTypeID, GameObject*>(TYPE_PLAYER, temp));
		
			//_listObjectPrototype.insert(std::pair < GameObjectTypeID, GameObject*>(TYPE_WALL, CreateGameObject(TYPE_WALL)));

		// load initial level
	}
	void Update() {
		
		//std::cout << "GOFac Update" << std::endl;


		// run through all GOs, run their Update()s in order
			//std::unordered_map< size_t, GameObject* >::iterator itr = _listObject.begin();
			//while (itr != _listObject.end())
			//{
			//	GameObject* temp = itr->second;
			//	temp->Update();
			//	itr++;
			//}		

		// detect any level changes
		_state.Update();
		if (_state.GetCurrState() == GS_LEVELCHANGE)
		{
			// remove all GOs

			// load new level
		}
	}
	void Exit() {
		std::cout << "GOFac Exit" << std::endl;
	}

	// TempGO for Serialising from LevelText.txt
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
		std::cout << "FileRead_Level(" << FileName << ")" << std::endl;
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
				obj.id = TYPE_WALL;
			if (std::strcmp(strType, "Floor") == 0)
				obj.id = TYPE_FLOOR;
			if (std::strcmp(strType, "Player") == 0)
				obj.id = TYPE_PLAYER;
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
//if (temp.id == TYPE_PLAYER)
//	ret.push_back(_listObjectPrototype[TYPE_PLAYER]->Clone(temp.pos, temp.scale, temp.rot));
//else if (temp.id == TYPE_FLOOR)
//	ret.push_back(_listObjectPrototype[TYPE_FLOOR]->Clone(temp.pos, temp.scale, temp.rot));
//else if (temp.id == TYPE_WALL)
//	ret.push_back(_listObjectPrototype[TYPE_WALL]->Clone(temp.pos, temp.scale, temp.rot));
//else;
			++itr;
		}
		return ret;
	}



	// TEST FUNCTION - to add some GOs 'dyamically'
	void TEST_AddGameObjects()
	{
		std::cout << std::endl << "-------------------------------------" << std::endl;
		std::cout << "TEST_AddGameObjects()" << std::endl;
		CloneGameObject(TYPE_PLAYER);
		CloneGameObject(TYPE_PLAYER);
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
			_listObject.erase(itr->first);
			++itr;
		}
		/*for (auto gameObject : _listObject)
		{
			delete gameObject.second;
			_listObject.erase(gameObject.first);
		}*/
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