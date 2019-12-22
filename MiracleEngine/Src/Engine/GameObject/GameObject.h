#pragma once
#include "rapidjson.h"		// J
#include "document.h"		// S
#include "writer.h"			// O
#include "stringbuffer.h"	// N
#include "error/en.h"		// Json error displaying

#include "Tools/FileIO/FileIO.h"
#include "Tools/FileIO/DeSerialiser.h"

#include "Components/Logic/LogicComponent.h"

#ifndef GAMEOBJECT_H
#define	GAMEOBJECT_H

//enum class TypeIdGO {
//	NONE = 0,
//	WALL, FLOOR, OBSTACLE,//Setting
//	PLAYER, ENEMY, BULLET, TURRET, //Mobile objects
//	WEAPON, PISTOL, SHOTGUN, SNIPER, RPG, //Weapons	
//	SPAWNER, CAMERA, FONT, ENEMYTWO, BULLET_T, BULLET_E, SPAWNERTWO,
//	EXPLOSION, BUTTON_UI,
//	MAPEDGE, PICK_UPS_HEALTH, PICK_UPS_AMMO, BOSS,
//	BGM, ENEMYTHREE, SPAWNERTHREE,
//
//	COUNT
//};

//inline const char* ToString(TypeIdGO type)	//Convert TypeIdGO Enum type to const char* - For Use only in Imgui
//{
//	switch (type)
//	{
//	case TypeIdGO::WALL:		return "Wall";
//	case TypeIdGO::FLOOR:		return "Floor";
//	case TypeIdGO::OBSTACLE:	return "Obstacle";
//	case TypeIdGO::SPAWNER:		return "Spawner";
//	case TypeIdGO::PLAYER:		return "Player";
//	case TypeIdGO::ENEMY:		return "Enemy";
//	case TypeIdGO::BULLET:		return "Bullet";
//	case TypeIdGO::TURRET:		return "Turret";
//	case TypeIdGO::WEAPON:		return "Weapon";
//	case TypeIdGO::PISTOL:		return "Pistol";
//	case TypeIdGO::SHOTGUN:		return "Shotgun";
//	case TypeIdGO::SNIPER:		return "Sniper";
//	case TypeIdGO::RPG:			return "RPG";
//	case TypeIdGO::CAMERA:		return "Camera";
//	case TypeIdGO::ENEMYTWO:	return "EnemyTwo";
//	case TypeIdGO::FONT:		return "Font";
//	case TypeIdGO::BULLET_T:	return "Bullet_T";
//	case TypeIdGO::BULLET_E:	return "Bullet_E";
//	case TypeIdGO::SPAWNERTWO:	return "SpawnerTwo";
//	case TypeIdGO::EXPLOSION:	return "Explosion";
//	case TypeIdGO::BUTTON_UI:	return "Button_UI";
//	case TypeIdGO::MAPEDGE:		return "MapEdge";
//	case TypeIdGO::PICK_UPS_HEALTH:	return "Health_PickUps";
//	case TypeIdGO::PICK_UPS_AMMO:	return "Ammo_PickUps";
//	case TypeIdGO::BOSS:		return "Boss";
//	case TypeIdGO::ENEMYTHREE:		return "EnemyThree";
//	case TypeIdGO::SPAWNERTHREE:		return "SpawnerThree";
//	default:      return "[Unknown TypeIdGO]";
//	}
//}

typedef std::unordered_map <ComponentId, IComponent* > Map_ComponentList;

class GameObject
{
private:
	Map_ComponentList _ComponentList; // Component List
	size_t _uId; // Unique ID

	//unsigned _typeId; // GameObject Type

	bool _destory;
	bool _enable;
	bool _alive;

public:
	GameObject(size_t uId = 0); // Ctor : Inits w/ a Unique id

	virtual ~GameObject();// Dtor : Deletes all Components in a Game Object

	//virtual unsigned GameObjectType() const; // Return GameObjectType Name
	//unsigned Get_typeId() const; // Return _typeId;
	//void Set_typeId(TypeIdGO type);



	size_t Get_uID() const; // Return _uId

	void Serialise(Serialiser& document);
	//void SerialiseFromLevel(Serialiser& fileObject);
	void DeSerialise(std::string filePath);

	Map_ComponentList& GetComponentList(); // Get ComponentList

	bool CheckComponent(ComponentId componentType, ScriptId script = ScriptId::EMPTY);
	IComponent* GetComponent(ComponentId typeId, ScriptId script = ScriptId::EMPTY); // GetChildComponent

	IComponent* AddComponent(ComponentId componentType, ScriptId script = ScriptId::EMPTY);
	void RemoveComponent(ComponentId componentType, ScriptId script = ScriptId::EMPTY);
	void DestoryGameObject();

	bool GetAlive();
	void SetAlive(bool alive);
	bool GetDestory() const;
	void SetDestory();
	bool GetEnable() const;
	void SetEnable(bool enable);
};


#endif