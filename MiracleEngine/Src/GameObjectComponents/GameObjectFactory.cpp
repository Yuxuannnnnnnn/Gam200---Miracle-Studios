#include "PrecompiledHeaders.h"
#include "GameObjectFactory.h"

GameObjectProrotype::GameObjectProrotype()
{}
GameObjectProrotype::~GameObjectProrotype()
{
	for (auto gameObject : _listObjectPrototype)
		delete gameObject.second;
	_listObjectPrototype.clear();
}

// Get _listObjectProrotype
PrototypeList& GameObjectProrotype::GetPrototypeList()
{
	return _listObjectPrototype;
}

//Create a gameObject type along with its Components
GameObject* GameObjectProrotype::PrefabGameObject(TypeIdGO typeId)
{
	size_t uId = 0;
	GameObject* gameObject = nullptr;
	switch (typeId)
	{
	case TypeIdGO::PLAYER:
		gameObject = new GameObject(uId, (unsigned)TypeIdGO::PLAYER);
		gameObject->SerialInPrefab_Player();
		break;
	case TypeIdGO::WALL:
		gameObject = new GameObject(uId, (unsigned)TypeIdGO::WALL);
		gameObject->SerialInPrefab_Wall();
		break;
		//Other Objects
	}
	return gameObject;
}

//Create a gameObject type along with its Components
GameObject* GameObjectProrotype::CloneGameObject(TypeIdGO typeId)
{
	GameObject* gameObject = nullptr;

	switch (typeId)
	{
	case TypeIdGO::PLAYER:
		//gameObject = new Player(0);
		//gameObject->SerialInPrefab();
		break;
	case TypeIdGO::WALL:
		break;
		//Other Objects
	}
	return gameObject;
}

// call on start up
void GameObjectProrotype::Init()
{
	GameObject* temp = nullptr;
	// Prototype_Player
	temp = new GameObject(0, (unsigned)TypeIdGO::PLAYER);
	temp->SerialInPrefab_Player();
	_listObjectPrototype.insert(std::pair < TypeIdGO, GameObject*>(TypeIdGO::PLAYER, temp));
	// Prototype_Player
	temp = new GameObject(0, (unsigned)TypeIdGO::WALL);
	temp->SerialInPrefab_Wall();
	_listObjectPrototype.insert(std::pair < TypeIdGO, GameObject*>(TypeIdGO::WALL, temp));
}
void GameObjectProrotype::Update()
{
	// works as Load()
}
void GameObjectProrotype::Exit()
{
	// remove all GOs
}




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
	}
	_listObject.clear();
}

GameObjectFactory& GameObjectFactory::GetGOFac()
{
	return *this;
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

const std::unordered_map < size_t, RigidBody2D* >&
GameObjectFactory::getRigidBodyComponent() const
{
	return _rigidBody2dComponents;
}

const std::unordered_map < size_t, Collider2D* >&
GameObjectFactory::getCollider2dComponent() const
{
	return _collider2dComponents;
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

//Deleting a gameObject entirely from the gameObjectFactory
void GameObjectFactory::DeleteGameObjectID(size_t id)
{
	std::cout << "DeleteGameObjectID(" << id << ")" << std::endl;
	delete _listObject[id];

	_listObject.erase(id);
	_graphicComponents.erase(id);
	_transformComponents.erase(id);
	_rigidBody2dComponents.erase(id);
	_collider2dComponents.erase(id);
}

//Create a gameObject type along with its Components
GameObject* GameObjectFactory::CreateGameObject(TypeIdGO typeId)
{
	//std::cout << "CreateGameObject(" << typeId << ")" << std::endl;
	//GameObject* gameObject = nullptr;

	//switch (typeId)
	//{
	//case PLAYER:
	//	gameObject = new Player(_uId);
	//	_listObject[_uId] = gameObject;

	//	_transformComponents[_uId] = dynamic_cast<TransformComponent*> (gameObject->addcomponent(TRANSFORMCOMPONENT));
	//	_graphicComponents[_uId] = dynamic_cast<GraphicComponent*> (gameObject->addcomponent(GRAPHICSCOMPONENT));
	//	_rigidBodyComponents[_uId] = dynamic_cast<RigidBodyComponent*> (gameObject->addcomponent(RIGIDBODYCOMPONENT));
	//	_physicsComponents[_uId] = dynamic_cast<PhysicsComponent*> (gameObject->addcomponent(PHYSICSCOMPONENT));

	//	_uId++;
	//	break;
	//case WALL:
	//	break;
	//	//Other Objects
	//}
	//return gameObject;
	return nullptr;
}
//Create a gameObject type along with its Components
void GameObjectFactory::CloneGameObject(TypeIdGO gameObjectTypeID)
{
	std::cout << "\t CloneGameObject(" << (unsigned)gameObjectTypeID << ")" << std::endl;
	GameObject* temp = nullptr;
	switch (gameObjectTypeID)
	{
	case TypeIdGO::PLAYER:
		temp = _prototypes.GetPrototypeList()[TypeIdGO::PLAYER]->Clone();
		break;
	default:
		break;
	}
	// add 'temp' to the _listObj;
	if (!temp)
		return;
	_listObject.insert(std::pair<size_t, GameObject*>(++_uId, temp));
	// based on temp's _ComponentList, add the components into GOFac's different systems
	std::unordered_map< TypeIdComponent, IComponentSystem* >::iterator itr = temp->_ComponentList.begin();
	while (itr != temp->_ComponentList.end())
	{
		switch (itr->first)
		{
		case TypeIdComponent::TRANSFORMCOMPONENT:
			_transformComponents[_uId] = (TransformComponent*)itr->second;
			break;
		case TypeIdComponent::GRAPHICSCOMPONENT:
			_graphicComponents[_uId] = (GraphicComponent*)itr->second;
			break;
		case TypeIdComponent::RIGIDBODYCOMPONENT:
			_rigidBody2dComponents[_uId] = (RigidBody2D*)itr->second;
			break;
		case TypeIdComponent::COLLIDERCOMPONENT:
			_collider2dComponents[_uId] = (Collider2D*)itr->second;
			break;
		case TypeIdComponent::LOGICCOMPONENT:
			_logicComponents[_uId] = (LogicComponent*)itr->second;
			break;
		}
		++itr;
	}
}

//InUpEx
void GameObjectFactory::Init() {
	std::cout << "GOFac Init" << std::endl;
	_state.Init();

	_prototypes.Init();

	// load initial level
}
void GameObjectFactory::Update() {

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
void GameObjectFactory::Exit() {
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
//Read LevelText and Instantiate GObj
std::vector<GameObject*> GameObjectFactory::FileRead_Level(const char* FileName)
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
			obj.id = (unsigned)TypeIdGO::WALL;
		if (std::strcmp(strType, "Floor") == 0)
			obj.id = (unsigned)TypeIdGO:: FLOOR;
		if (std::strcmp(strType, "Player") == 0)
			obj.id = (unsigned)TypeIdGO::PLAYER;
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
		//if (temp.id == PLAYER)
		//	ret.push_back(_listObjectPrototype[PLAYER]->Clone(temp.pos, temp.scale, temp.rot));
		//else if (temp.id ==  FLOOR)
		//	ret.push_back(_listObjectPrototype[ FLOOR]->Clone(temp.pos, temp.scale, temp.rot));
		//else if (temp.id == WALL)
		//	ret.push_back(_listObjectPrototype[WALL]->Clone(temp.pos, temp.scale, temp.rot));
		//else;
		++itr;
	}
	return ret;
}
