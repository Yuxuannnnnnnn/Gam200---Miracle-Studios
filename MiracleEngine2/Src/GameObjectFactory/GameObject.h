#pragma once
#include "PrecompiledHeaders.h"
 
#include "rapidjson.h"		// J
#include "document.h"		// S
#include "writer.h"			// O
#include "stringbuffer.h"	// N
#include "error/en.h"		// Json error displaying

#include "Tools/FileIO/FileIO.h"

#include "GameObjectComponents/LogicComponents/LogicComponent.h"

#ifndef GAMEOBJECT_H
#define	GAMEOBJECT_H

enum class TypeIdGO {
	NONE = 0,
	WALL, FLOOR, OBSTACLE,//Setting
	PLAYER, ENEMY, BULLET, TURRET, //Mobile objects
	WEAPON, PISTOL, SHOTGUN, SNIPER, RPG, //Weapons	
	SPAWNER, CAMERA, FONT, ENEMYTWO, BULLET_T, BULLET_E, SPAWNERTWO,
	MAPEDGE, 

	COUNT
};

inline const char* ToString(TypeIdGO type)	//Convert TypeIdGO Enum type to const char* - For Use only in Imgui
{
	switch (type)
	{
	case TypeIdGO::WALL:		return "Wall";
	case TypeIdGO::FLOOR:		return "Floor";
	case TypeIdGO::OBSTACLE:	return "Obstacle";
	case TypeIdGO::SPAWNER:		return "Spawner";
	case TypeIdGO::PLAYER:		return "Player";
	case TypeIdGO::ENEMY:		return "Enemy";
	case TypeIdGO::BULLET:		return "Bullet";
	case TypeIdGO::TURRET:		return "Turret";
	case TypeIdGO::WEAPON:		return "Weapon";
	case TypeIdGO::PISTOL:		return "Pistol";
	case TypeIdGO::SHOTGUN:		return "Shotgun";
	case TypeIdGO::SNIPER:		return "Sniper";
	case TypeIdGO::RPG:			return "RPG";
	case TypeIdGO::CAMERA:		return "Camera";
	case TypeIdGO::ENEMYTWO:	return "EnemyTwo";
	case TypeIdGO::FONT:		return "Font";
	case TypeIdGO::BULLET_T:	return "Bullet_T";
	case TypeIdGO::BULLET_E:	return "Bullet_E";
	case TypeIdGO::SPAWNERTWO:	return "SpawnerTwo";

	case TypeIdGO::MAPEDGE:		return "MapEdge";
	default:      return "[Unknown TypeIdGO]";
	}
}

typedef std::unordered_map < unsigned, IComponentSystem* > Map_ComponentList;

class GameObject
{
private:

	Map_ComponentList _ComponentList; // Component List
	unsigned _typeId; // GameObject Type
	size_t _uId; // Unique ID
	bool _destory;
	bool _enable;
public:
	bool _alive;

	GameObject(size_t uId, unsigned typeId = (unsigned)TypeIdGO::NONE); // Ctor : Inits w/ a Unique id

	virtual ~GameObject();// Dtor : Deletes all Components in a Game Object

	virtual unsigned GameObjectType() const; // Return GameObjectType Name
	unsigned Get_typeId() const; // Return _typeId;
	size_t Get_uID() const; // Return _uId

	void Set_typeId(TypeIdGO type);

	virtual void Init() { std::cout << "IGO : INIT" << std::endl; }			// InUpEx
	virtual void Update() { std::cout << "IGO : UPDATE" << std::endl; }		//
	virtual void Exit() { std::cout << "IGO : EXIT" << std::endl; }			//
		
	void Serialise(std::string file);

	Map_ComponentList& GetComponentList(); // Get ComponentList

	bool CheckComponent(ComponentId componentType, ScriptId script = ScriptId::EMPTY);

	IComponentSystem* AddComponent(ComponentId componentType, ScriptId script = ScriptId::EMPTY);
	void RemoveComponent(ComponentId componentType, ScriptId script = ScriptId::EMPTY);
	void DestoryGameObject();

	bool GetDestory() const { return _destory; }
	void SetDestory() 
	{
		_destory = true; 
		SetEnable(false);
	}

	bool GetEnable() const { return _enable; }
	void SetEnable(bool enable) 
	{ 
		_enable = enable;

		for (auto it : _ComponentList)
			it.second->SetEnable(enable);
	}


	IComponentSystem* GetComponent(ComponentId typeId, ScriptId script = ScriptId::EMPTY); // GetChildComponent
};


#endif