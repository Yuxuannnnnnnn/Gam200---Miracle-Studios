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


	///////////////////////////////////////////////

	GameObject* Clone();
	void Set_uID(size_t uid);
	//////////////////////////////////////////////

	bool GetAlive();
	void SetAlive(bool alive);
	bool GetDestory() const;
	void SetDestory();
	bool GetEnable() const;
	void SetEnable(bool enable);
};


#endif