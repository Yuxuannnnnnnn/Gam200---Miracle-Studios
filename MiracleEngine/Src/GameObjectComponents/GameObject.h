#pragma once
#include "PrecompiledHeaders.h"
#include "GraphicComponent.h"
#include "RigidBodyComponent.h"
#include "TransformComponent.h"
#include "PhysicsComponent.h"
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
	UNKNOWN = 0,

	WALL = 1, FLOOR = 2, OBSTACLE = 3, //Setting

	PLAYER = 4, ENEMY = 5, //Mobile objects

	PISTOL = 6, SHOTGUN = 7, SNIPER = 8, RPG = 9 //Weapons
};


enum ComponentTypes
{
	TRANSFORMCOMPONENT = 0,
	GRAPHICSCOMPONENT = 1,
	RIGIDBODYCOMPONENT = 2,
	PHYSICSCOMPONENT = 3
};


class IGameObject : public ISerial
{
public:

	std::unordered_map < ComponentTypes, IComponentSystem* > _ComponentList;


	unsigned _typeId;	// GameObject Type
	unsigned _uId;		// Unique ID
	// Ctor : Inits w/ a Unique id
	IGameObject(unsigned uId = 0);
	// Dtor : Deletes all Components in a Game Object
	virtual ~IGameObject();
	
	virtual void Init() {}
	virtual void Update() {}
	virtual void Exit() {}

	//Return GameObjectType Name
	virtual std::string GameObjectType() const;

	//Add a specific component to the GameObject
	IComponentSystem* addcomponent(ComponentTypes componentType);

	// 'addcomponent' Varient for Serialization, allows addComponent during serialization
	void SerialAddComponent
	(ComponentTypes componentType, rapidjson::Value& s, rapidjson::Document& d);

	virtual IGameObject* Clone(Vector3 pos, Vector3 scale, float rotate);
};


class Weapon: public IGameObject
{
private:

	float _FireRate{ 0.0f };

public:
	Weapon() = default;
	Weapon(unsigned id, float firerate) 
		: IGameObject(id), _FireRate{ firerate } 
	{}

	~Weapon() = default;

	std::string GameObjectType() const override
	{
		return "Weapon";
	}
};


class Player : public IGameObject
{
	unsigned int _Health{ 0 };
	float _Speed{ 0.0f };
	std::vector<unsigned> _WeaponListId;
	std::vector<Weapon> _WeaponList;
public:
	Player(unsigned id)
		:IGameObject(id)
	{
		SerialInPrefab();
	}
	~Player() {}

	virtual void SerialInPrefab() override {
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
		JsonDynamicStore(compList,s);
		std::vector<int>::iterator itr = compList.begin();
		while (itr != compList.end())
			SerialAddComponent((ComponentTypes) *itr++, s, d);
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
	virtual void SerialInLevel() override {

	}
	virtual void Init() override {
	}
	virtual void Update() override {
	}
	virtual void Exit() override {
	}

	void ConvertWeaponIdToWeapon() {
		_WeaponList.clear();
		std::vector<unsigned int>::iterator itr = _WeaponListId.begin();
		while (itr != _WeaponListId.end()) {
			_WeaponList.push_back(Weapon(*itr, 0.0f));
		}
	}
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
		std::vector<unsigned>::iterator itr = _WeaponListId.begin();
		while (itr != _WeaponListId.end())
			std::cout << *itr++;
		std::cout << std::endl
			<< "-------------------------------------"
			<< std::endl;
	}
	/*
	void Serialize() {
		// just bring over the FileRead_PlayerInfo from the FileIO.cpp
		// file path can now be put here since all serailization will be done within the this cpp

	// just bring over the FileRead_PlayerInfo from the FileIO.cpp
	// file path can now be put here since all serailization will be done within the this cpp
	std::cout << "FileRead_PlayerInfo -----------------" << std::endl;
	rapidjson::Document d;
	char* iBuffer = FileRead_FileToCharPtr(FilePathNames::path_player);
	std::cout << iBuffer << std::endl;
	assert(iBuffer != nullptr);
	d.Parse<rapidjson::kParseStopWhenDoneFlag>(iBuffer);
// get values from the Document;
	rapidjson::Value& s = d["Health"];
		JsonDynamicStore(_Health, s);
	s = d["Speed"];
		JsonDynamicStore(_Speed, s);
	s = d["Weapons"];
		JsonDynamicStore(_WeaponListId, s);
	TransformComponent* tempTrans =
		dynamic_cast<TransformComponent*>(_ComponentList[TRANSFORMCOMPONENT]);
	s = d["Position"];
		JsonDynamicStore(tempTrans->GetPos(), s);
	s = d["Scale"];
		JsonDynamicStore(tempTrans->GetScale(), s);		
	s = d["Rotation"];
		JsonDynamicStore(tempTrans->GetRotate(), s);

	std::cout << "-------------------------------------" << std::endl;

	delete[] iBuffer;
	}

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
		std::vector<unsigned>::iterator itr = _WeaponListId.begin();
		while (itr != _WeaponListId.end())
			std::cout << *itr++;
		std::cout << std::endl
			<< "-------------------------------------"
			<< std::endl;
	}
	*/

	std::string GameObjectType() const override
	{
		return "Player";
	}
};
