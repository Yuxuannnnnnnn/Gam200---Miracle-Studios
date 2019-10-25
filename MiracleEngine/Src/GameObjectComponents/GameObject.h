#pragma once
#include "PrecompiledHeaders.h"
#include "GraphicComponent.h"
#include "RigidBodyComponent.h"
#include "TransformComponent.h"
#include "PhysicsComponent.h"
#include "LogicComponent.h"
#include "PhysicSystem/CollisionComponent/Collider2D.h"
#include "PhysicSystem/PhysicComponent/RigidBody2D.h"
#include "Tools/FileIO.h"
#include <unordered_map>


//namespace FilePathNames {
//	const char* path_player = "./Resources/TextFiles/player.json";
//	const char* path_init = "./Resources/TextFiles/init.json";
//	const char* path_outTest = "./Resources/TextFiles/test.txt";
//	const char* path_crashLog = "./Resources/TextFiles/crashlog.txt";
//	const char* path_GameObjectList = "./Resources/TextFiles/ListOfGameObjects.txt";
//}

/**
\brief GameObjectTypeID
*/
enum GameObjectTypeID {
	TYPE_UNKNOWN = 0,
	TYPE_WALL, TYPE_FLOOR, TYPE_OBSTACLE, //Setting
	TYPE_PLAYER, TYPE_ENEMY, //Mobile objects
	TYPE_WEAPON, TYPE_PISTOL, TYPE_SHOTGUN, TYPE_SNIPER, TYPE_RPG, //Weapons	
};

enum ComponentTypes
{
	TRANSFORMCOMPONENT = 0,
	GRAPHICSCOMPONENT = 1,
	RIGIDBODYCOMPONENT = 2,
	COLLIDERCOMPONENT = 3,
	LOGICCOMPONENT = 4,
};


class GameObject
{
public:
// Component List
	std::unordered_map < ComponentTypes, IComponentSystem* > _ComponentList;
// GameObject Type
	size_t _typeId;
// Unique ID
	size_t _uId;

// Ctor : Inits w/ a Unique id
	GameObject(size_t uId = 0, size_t typeId = 0);
// Dtor : Deletes all Components in a Game Object
	virtual ~GameObject();
// Return GameObjectType Name
	virtual GameObjectTypeID GameObjectType() const;
// InUpEx
	virtual void Init() { std::cout << "IGO : INIT" << std::endl; }
	virtual void Update() { std::cout << "IGO : UPDATE" << std::endl; }
	virtual void Exit() { std::cout << "IGO : EXIT" << std::endl; }
// Components
	//Add a specific component to the GameObject
	IComponentSystem* addcomponent(ComponentTypes componentType);
	// 'addcomponent' Varient for Serialization, allows addComponent during serialization
	void SerialAddComponent
	(ComponentTypes componentType, rapidjson::Value& s, rapidjson::Document& d);
	// based on ComponentIdList, copy from original and create new ones for a given obj
	void CopyComponent(std::unordered_map< ComponentTypes, IComponentSystem* >& original);
	// delete all components in _ComponentList
	void DeleteAllComponents();
// Cloning
	virtual GameObject* Clone();

// Serialisation
	virtual void SerialInPrefab_Player() {
	// Get & Parse File
		std::cout << std::endl << "FileRead_PlayerInfo -----------------" << std::endl;
		rapidjson::Document d;
		char* iBuffer = FileRead_FileToCharPtr("./Resources/TextFiles/playerNew.json");
		ASSERT(iBuffer != nullptr);
		std::cout << iBuffer << std::endl;
		d.Parse<rapidjson::kParseStopWhenDoneFlag>(iBuffer);
	// Component List
		rapidjson::Value& s = d["ComponentList"];
		std::vector<int> compList;
		JsonDynamicStore(compList, s);
		std::vector<int>::iterator itr = compList.begin();
		while (itr != compList.end())
			SerialAddComponent((ComponentTypes)* itr++, s, d);
	// Other Values
		//s = d["Weapons"];
		//JsonDynamicStore(_WeaponListId, s);
		// ConvertWeaponIdToWeapon(); // MAY BE CAUSING MEM LEAK
		std::cout << "-------------------------------------" << std::endl;
		delete[] iBuffer;
		PrintStats_Player(); // for checking serialisation
	}
	void PrintStats_Player() {
		IComponentSystem* temp = nullptr;
		temp = _ComponentList[TRANSFORMCOMPONENT];
		std::cout
			<< "FilePrint_PlayerInfo ----------------" << std::endl
			<< "\tTrans.Pos      :  " << ((TransformComponent*)temp)->GetPos() << std::endl
			<< "\tTrans.Sca      :  " << ((TransformComponent*)temp)->GetScale() << std::endl
			<< "\tTrans.Rot      :  " << ((TransformComponent*)temp)->GetRotate() << std::endl;
		temp = _ComponentList[GRAPHICSCOMPONENT];
		std::cout
			<< "\tGraphics       :  " << "[placeHolder] " << std::endl;
		temp = _ComponentList[RIGIDBODYCOMPONENT];
		std::cout
			<< "\tRBod.Mass      :  " << ((RigidBody2D*)temp)->_mass << std::endl
			<< "\tRBod.Friction  :  " << ((RigidBody2D*)temp)->_fictionVal << std::endl
			<< "\tRBod.Static    :  " << ((RigidBody2D*)temp)->_static << std::endl;
		temp = _ComponentList[COLLIDERCOMPONENT];
		std::cout
			<< "\tCollider.TypId :  " << ((Collider2D*)temp)->_type << std::endl;
		temp = _ComponentList[LOGICCOMPONENT];
		std::cout
			<< "\tLogic.Health   :  " << ((LogicComponent*)temp)->GetHealth() << std::endl
			<< "\tLogic.Speed    :  " << ((LogicComponent*)temp)->GetSpeed() << std::endl
			<< "\tLogic.Lifetime :  " << ((LogicComponent*)temp)->GetLifetime() << std::endl
			<< "\tLogic.ScriptIds:  ";
		std::vector<int> tempScriptList = ((LogicComponent*)temp)->GetScriptId();
		std::vector<int>::iterator itr = tempScriptList.begin();
		while (itr != tempScriptList.end())
			std::cout << *itr++ << " ";
			//	<< "Weapons :   ";
		//std::vector<int>::iterator itr = _WeaponListId.begin();
		//while (itr != _WeaponListId.end())
		//	std::cout << *itr++;
		std::cout << std::endl
			<< "-------------------------------------"
			<< std::endl << std::endl;
	}
};


class Weapon: public GameObject
{
private:

	float _FireRate{ 0.0f };

public:
	Weapon() = default;
	Weapon(size_t id, float firerate)
		: GameObject(id, TYPE_WEAPON), _FireRate{ firerate }
	{}

	~Weapon() = default;

	GameObjectTypeID GameObjectType() const override
	{
		return TYPE_WEAPON;
	}
};


class Player : public GameObject
{
	unsigned int _Health{ 0 };
	float _Speed{ 0.0f };
	std::vector<int> _WeaponListId;
	std::vector<Weapon> _WeaponList;
public:
	// Ctor
Player(size_t uId)
		:GameObject(uId, TYPE_PLAYER) // init with uId & type::PLAYER
	{
	}
// Dtor
	~Player() {}
// InUpEx
	virtual void Init() override {
		SerialInPrefab();
	}
	virtual void Update() override {
	}
	virtual void Exit() override {
	}
// FileIO
	virtual void SerialInPrefab() {
	// Get & Parse File
		std::cout << "FileRead_PlayerInfo -----------------" << std::endl;
		rapidjson::Document d;
		char* iBuffer = FileRead_FileToCharPtr("./Resources/TextFiles/playerNew.json");
		ASSERT(iBuffer != nullptr);
		std::cout << iBuffer << std::endl;
		d.Parse<rapidjson::kParseStopWhenDoneFlag>(iBuffer);
	// Component List
		rapidjson::Value& s = d["ComponentList"];
		std::vector<int> compList;
		JsonDynamicStore(compList, s);
		std::vector<int>::iterator itr = compList.begin();
		while (itr != compList.end())
			SerialAddComponent((ComponentTypes)* itr++, s, d);
	// Other Values
		s = d["Health"];
		JsonDynamicStore(_Health, s);
		s = d["Speed"];
		JsonDynamicStore(_Speed, s);
		s = d["Weapons"];
		JsonDynamicStore(_WeaponListId, s);
	// ConvertWeaponIdToWeapon(); // MAY BE CAUSING MEM LEAK
		std::cout << "-------------------------------------" << std::endl;
		delete[] iBuffer;
		PrintStats(); // for checking serialisation
	}
	virtual void SerialInLevel() {
	}
// Cloning
	Player& Clone(Player& original, unsigned id, Vector3 pos, Vector3 scale, float rotate)
	{
		(void)id; (void)pos; (void)scale; (void)rotate;

		Player temp = original;
		return temp;
	}
// Others - WeapID to Weap helper()
	void ConvertWeaponIdToWeapon() {
		_WeaponList.clear();
		std::vector<int>::iterator itr = _WeaponListId.begin();
		while (itr != _WeaponListId.end()) {
			_WeaponList.push_back(Weapon(*itr, 0.0f));
		}
	}
// Others - print to check seriaisation
	void PrintStats() {
		TransformComponent* tempTrans =
			dynamic_cast<TransformComponent*>(_ComponentList[TRANSFORMCOMPONENT]);
		std::cout
			<< "FilePrint_PlayerInfo ----------------" << std::endl
			<< "Trans.Pos : " << tempTrans->GetPos() << std::endl
			<< "Trans.Sca : " << tempTrans->GetScale() << std::endl
			<< "Trans.Rot : " << tempTrans->GetRotate() << std::endl
			<< "Health :    " << _Health << std::endl
			<< "Speed :     " << _Speed << std::endl
			<< "Weapons :   ";
		std::vector<int>::iterator itr = _WeaponListId.begin();
		while (itr != _WeaponListId.end())
			std::cout << *itr++;
		std::cout << std::endl
			<< "-------------------------------------"
			<< std::endl;
	}

	GameObjectTypeID GameObjectType() const override
	{
		return TYPE_PLAYER;
	}
};
