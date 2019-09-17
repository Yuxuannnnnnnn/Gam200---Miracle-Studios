#pragma once

#include <vector>			// STL
#include <iterator>			// stuff
#include <map>

#include "Tools/FileIO.h"	// Serialization
#include "MathLib/Vector3.h"

#include "IComponentSystem.h"
#include "GraphicComponent.h"
#include "RigidBodyComponent.h"
#include "TransformComponent.h"

enum GameObjectID {
	UNKNOWN = 0,

	WALL = 1, FLOOR = 2, OBSTACLE = 3, //Setting

	PLAYER = 4, ENEMY = 5, //Mobile objects

	PISTOL = 6, SHOTGUN = 7, SNIPER = 8, RPG = 9 //Weapons
};

enum ComponentTypes
{
	TRANSFORMCOMPONENT = 0,
	GRAPHICSCOMPONENT = 1,
	RIGIDBODYCOMPONENT = 2
};

class IGameObject
{
public:

	IGameObject() = default;

	//deletes all Components in a Game Object
	virtual ~IGameObject()
	{
		std::map< ComponentTypes, IComponentSystem* >::iterator iterator = _ComponentList.begin();
		while (iterator != _ComponentList.end())
		{
			delete iterator->second;
			iterator++;
		}
	}

	//Return GameObjectType Name
	virtual std::string GameObjectType() const = 0;

	//Add a specific component to the GameObject
	void addcomponent(ComponentTypes componentType)
	{
		switch (componentType)
		{
		case TRANSFORMCOMPONENT:
			_ComponentList[TRANSFORMCOMPONENT] = new TransformComponent();
			return;
		case GRAPHICSCOMPONENT:
			_ComponentList[GRAPHICSCOMPONENT] = new GraphicComponent();
			return;
		case RIGIDBODYCOMPONENT:
			_ComponentList[RIGIDBODYCOMPONENT] = new RigidBodyComponent();
			return;
		}
	}

private:

	//List of Components for Each GameObject
	std::map< ComponentTypes, IComponentSystem* > _ComponentList;
};


class Weapon: public IGameObject
{
private:

	unsigned int _Id;

	float _FireRate{ 0.0f };

public:
	Weapon() = default;
	Weapon(unsigned int id, float firerate) 
		: _Id{ id }, _FireRate{ firerate } 
	{}

	~Weapon() = default;

	std::string GameObjectType() const override
	{
		return "Weapon";
	}
};


class Player : public IGameObject
{
private:

	unsigned int _Id;

	unsigned int _Health{ 0 };
	float _Speed{ 0.0f };

	std::vector<Weapon> _WeaponList;

public:
	Player() { Serialize(); }
	~Player() {}

	void Serialize() {
		// just bring over the FileRead_PlayerInfo from the FileIO.cpp
		// file path can now be put here since all serailization will be done within the this cpp
	}

	void PrintStats() {
		// also just bring over from FileIO area
	}


	std::string GameObjectType() const override
	{
		return "Player";
	}
};
