#pragma once
#include "PrecompiledHeaders.h"
 
#include "rapidjson.h"		// J
#include "document.h"		// S
#include "writer.h"			// O
#include "stringbuffer.h"	// N
#include "error/en.h"		// Json error displaying

#include "GraphicComponent.h"
#include "RigidBodyComponent.h"
#include "TransformComponent.h"
#include "PhysicsComponent.h"
#include "LogicComponent.h"
#include "AudioComponent.h"
#include "PhysicSystem/CollisionComponent/Collider2D.h"
#include "PhysicSystem/PhysicComponent/RigidBody2D.h"

#include "Tools/FileIO.h"

//namespace FilePathNames {
//	const char* path_player = "./Resources/TextFiles/player.json";
//	const char* path_init = "./Resources/TextFiles/init.json";
//	const char* path_level = "./Resources/TextFiles/TestLevel.txt";
//	const char* path_outTest = "./Resources/TextFiles/test.txt";
//	const char* path_crashLog = "./Resources/TextFiles/crashlog.txt";
//	const char* path_GameObjectList = "./Resources/TextFiles/ListOfGameObjects.txt";
//}

enum class TypeIdGO {
	NONE = 0,
	WALL, FLOOR, OBSTACLE, //Setting
	PLAYER, ENEMY, BULLET, //Mobile objects
	WEAPON, PISTOL, SHOTGUN, SNIPER, RPG, //Weapons	
};

inline const char* ToString(TypeIdGO type)	//Convert TypeIdGO Enum type to const char* - For Use only in Imgui
{
	switch (type)
	{
	case TypeIdGO::WALL:		return "Wall";
	case TypeIdGO::FLOOR:		return "Floor";
	case TypeIdGO::OBSTACLE:	return "Obstacle";
	case TypeIdGO::PLAYER:		return "Player";
	case TypeIdGO::ENEMY:		return "Enemy";
	case TypeIdGO::BULLET:		return "Bullet";
	case TypeIdGO::WEAPON:		return "Weapon";
	case TypeIdGO::PISTOL:		return "Pistol";
	case TypeIdGO::SHOTGUN:		return "Shotgun";
	case TypeIdGO::SNIPER:		return "Sniper";
	case TypeIdGO::RPG:			return "RPG";

	default:      return "[Unknown TypeIdGO]";
	}
}

//inline const char* ToString(TypeIdComponent type) //Convert TypeIdComponent Enum to const char* - For Use only in Imgui
//{
//	switch (type)
//	{
//	case TypeIdComponent::TRANSFORMCOMPONENT:	return "Transform Component";
//	case TypeIdComponent::GRAPHICSCOMPONENT: 	return "Graphics Component";
//	case TypeIdComponent::RIGIDBODYCOMPONENT:	return "RigidBoody Component";
//	case TypeIdComponent::COLLIDERCOMPONENT: 	return "Collider Component";
//	case TypeIdComponent::LOGICCOMPONENT:		return "Logic Component";
//	case TypeIdComponent::AUDIOCOMPONENT:		return "Audio Component";
//
//	default:      return "[Unknown TypeIdComponent]";
//	}
//}

typedef std::unordered_map < unsigned, IComponentSystem* > Map_ComponentList;

class GameObject
{
public:
	Map_ComponentList _ComponentList; // Component List

	unsigned _typeId; // GameObject Type

	size_t _uId; // Unique ID

	GameObject(size_t uId, unsigned typeId = 0); // Ctor : Inits w/ a Unique id

	virtual ~GameObject();// Dtor : Deletes all Components in a Game Object

	virtual unsigned GameObjectType() const; // Return GameObjectType Name
	size_t Get_uID() const; // Return _uId

	virtual void Init() { std::cout << "IGO : INIT" << std::endl; }			// InUpEx
	virtual void Update() { std::cout << "IGO : UPDATE" << std::endl; }		//
	virtual void Exit() { std::cout << "IGO : EXIT" << std::endl; }			//
		

	Map_ComponentList& GetComponentList() // Get ComponentList
	{
		return _ComponentList;
	}

// Components
	IComponentSystem* addcomponent(TypeIdComponent componentType); 	// DEPRECATED - Add a specific component to the GameObject

	void SerialAddComponent // AddComponent for during Serialisation
		(TypeIdComponent componentType, rapidjson::Value& s, rapidjson::Document& d); 	

	void CopyComponent // Copy all components from 'original'(Prototype/Prefab/whateverYouCallIt)
		(Map_ComponentList& original);

// Cloning
	virtual GameObject* Clone(size_t uId);

// Serialisation
	void SerialInPrefab_Player();
	void PrintStats_Player();
	void SerialInPrefab_Enemy();
	void PrintStats_Enemy();
	void SerialInPrefab_Wall();
	void PrintStats_Wall();
	void SerialInPrefab_Bullet();	// TODO
	void PrintStats_Bullet();		// TODO
};

// Definition for ChildGetCompList() in IComponentSystem
//std::unordered_map < unsigned, IComponentSystem* >IComponentSystem::ChildGetCompList(GameObject* obj)
//{
//	//std::unordered_map < unsigned, IComponentSystem* > a;
//
//	return obj->GetComponentList();
//}



//class Weapon: public GameObject
//{
//private:
//
//	float _FireRate{ 0.0f };
//
//public:
//	Weapon() = default;
//	Weapon(size_t id, float firerate)
//		: GameObject(id, (unsigned)TypeIdGO::WEAPON), _FireRate{ firerate }
//	{}
//
//	~Weapon() = default;
//
//	unsigned GameObjectType() const override
//	{
//		return (unsigned)TypeIdGO::WEAPON;
//	}
//};


//			no more player class, now Player is identified via _typeId
//class Player : public GameObject
//{
//	unsigned int _Health{ 0 };
//	float _Speed{ 0.0f };
//	std::vector<int> _WeaponListId;
//	std::vector<Weapon> _WeaponList;
//public:
//	// Ctor
//Player(size_t uId)
//		:GameObject(uId, PLAYER) // init with uId & type::PLAYER
//	{
//	}
//// Dtor
//	~Player() {}
//// InUpEx
//	virtual void Init() override {
//		SerialInPrefab();
//	}
//	virtual void Update() override {
//	}
//	virtual void Exit() override {
//	}
//// FileIO
//	virtual void SerialInPrefab() {
//	// Get & Parse File
//		std::cout << "FileRead_PlayerInfo -----------------" << std::endl;
//		rapidjson::Document d;
//		char* iBuffer = FileRead_FileToCharPtr("./Resources/TextFiles/playerNew.json");
//		ASSERT(iBuffer != nullptr);
//		std::cout << iBuffer << std::endl;
//		d.Parse<rapidjson::kParseStopWhenDoneFlag>(iBuffer);
//	// Component List
//		rapidjson::Value& s = d["ComponentList"];
//		std::vector<int> compList;
//		JsonDynamicStore(compList, s);
//		std::vector<int>::iterator itr = compList.begin();
//		while (itr != compList.end())
//			SerialAddComponent((ComponentTypes)* itr++, s, d);
//	// Other Values
//		s = d["Health"];
//		JsonDynamicStore(_Health, s);
//		s = d["Speed"];
//		JsonDynamicStore(_Speed, s);
//		s = d["Weapons"];
//		JsonDynamicStore(_WeaponListId, s);
//	// ConvertWeaponIdToWeapon(); // MAY BE CAUSING MEM LEAK
//		std::cout << "-------------------------------------" << std::endl;
//		delete[] iBuffer;
//		PrintStats(); // for checking serialisation
//	}
//	virtual void SerialInLevel() {
//	}
//// Cloning
//	Player& Clone(Player& original, unsigned id, Vector3 pos, Vector3 scale, float rotate)
//	{
//		(void)id; (void)pos; (void)scale; (void)rotate;
//
//		Player temp = original;
//		return temp;
//	}
//// Others - WeapID to Weap helper()
//	void ConvertWeaponIdToWeapon() {
//		_WeaponList.clear();
//		std::vector<int>::iterator itr = _WeaponListId.begin();
//		while (itr != _WeaponListId.end()) {
//			_WeaponList.push_back(Weapon(*itr, 0.0f));
//		}
//	}
//// Others - print to check seriaisation
//	void PrintStats() {
//		TransformComponent* tempTrans =
//			dynamic_cast<TransformComponent*>(_ComponentList[TRANSFORMCOMPONENT]);
//		std::cout
//			<< "FilePrint_PlayerInfo ----------------" << std::endl
//			<< "Trans.Pos : " << tempTrans->GetPos() << std::endl
//			<< "Trans.Sca : " << tempTrans->GetScale() << std::endl
//			<< "Trans.Rot : " << tempTrans->GetRotate() << std::endl
//			<< "Health :    " << _Health << std::endl
//			<< "Speed :     " << _Speed << std::endl
//			<< "Weapons :   ";
//		std::vector<int>::iterator itr = _WeaponListId.begin();
//		while (itr != _WeaponListId.end())
//			std::cout << *itr++;
//		std::cout << std::endl
//			<< "-------------------------------------"
//			<< std::endl;
//	}
//
//	GameObjectTypeID GameObjectType() const override
//	{
//		return PLAYER;
//	}
//};
