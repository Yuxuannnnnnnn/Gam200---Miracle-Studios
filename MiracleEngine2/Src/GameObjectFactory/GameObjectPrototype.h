#pragma once
#include "Tools/FileIO/Serialiser.h"





class GameObjectPrototype final
{
	std::unordered_map<TypeIdGO, GameObject*> _listObjectPrototype;		//Dynamic array of GameObject Prototypes

public:
	GameObjectPrototype(const GameObjectPrototype& rhs) = delete;
	GameObjectPrototype& operator=(const GameObjectPrototype& rhs) = delete;


	GameObjectPrototype();
	~GameObjectPrototype();	//Destructed when GameStateQuit

	std::unordered_map<TypeIdGO, GameObject*>& GetPrototypeList();	// Get _listObjectProrotype

	GameObject* SerialPrefabObjects(TypeIdGO type);
	GameObject* SerialPrefabObjects(Serialiser& document);

	//void SerialAddComponent(GameObject* object, SerialTypeId componentType, rapidjson::Value& s, rapidjson::Document& d);

	// Serialisation
	//GameObject* SerialInPrefab_Player();
	//GameObject* SerialInPrefab_Bullet();
	//GameObject* SerialInPrefab_Enemy();
	//GameObject* SerialInPrefab_Wall();
	//GameObject* SerialInPrefab_Floor();
	//GameObject* SerialInPrefab_Turret();
	//GameObject* SerialInPrefab_Spawner();
};