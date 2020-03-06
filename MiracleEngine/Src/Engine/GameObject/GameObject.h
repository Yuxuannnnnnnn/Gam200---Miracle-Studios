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
	///////////////////////////////////////////////
	bool _independent;
	bool _anyChild;

	GameObject* _parentObject;
	
	std::unordered_map<size_t, GameObject*> _childObjects; //LIst of ChildObjects that the ParentObject has
	///////////////////////////////////////////////

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

	IComponent* GetComponent(ComponentId typeId);
	IComponent* AddComponent(ComponentId componentType);
	void RemoveComponent(ComponentId componentType);

	void DestoryGameObject();


	///////////////////////////////////////////////
	GameObject* Clone(size_t uid = 0);
	//////////////////////////////////////////////

	bool GetAlive();
	void SetAlive(bool alive);
	bool GetDestory() const;
	void SetDestory();
	bool GetEnable() const;
	void SetEnable(bool enable);

	///////////////////////////////////////////////
	bool GetIndependent() const;
	void SetIndependent(bool independent);

	bool GetChild() const;
	void SetChild(bool child);

	GameObject* GetParent() const;
	void SetParent(GameObject* parent);

	std::unordered_map<size_t, GameObject*>& GetChildList();

	void AddChildObject(GameObject* child);
	void RemoveChildObject(GameObject* child);
};


#endif