#pragma once
#include "Tools/FileIO/Serialiser.h"



class GameObjectPrototype final
{
private:
//For Level Editor
	typedef std::unordered_map<std::string, std::string> NamePath;
	NamePath _prototypeFileList;
//--------------------------------------------------------------------

	typedef std::unordered_map<std::string, GameObject*> NameObject;		//Dynamic array of GameObject Prototypes
	NameObject _listObjectPrototype;

	std::deque<std::string> ComponentTypes;//Dynamic string of Component Types

public:
	GameObjectPrototype(const GameObjectPrototype& rhs) = delete;
	GameObjectPrototype& operator=(const GameObjectPrototype& rhs) = delete;

	GameObjectPrototype();
	~GameObjectPrototype();	//Destructed when GameStateQuit

	std::unordered_map<std::string, GameObject*>& GetPrototypeList();	// Get _listObjectProrotype
	
	GameObject* GetPrototypeObj(std::string prototypeName)
	{
		if (_listObjectPrototype.find(prototypeName) != _listObjectPrototype.end())
		{
			return _listObjectPrototype[prototypeName];
		}
		return nullptr;	//indicates Prototype object does not exist
	}

	const NamePath& GetPrototypeFileList()
	{
		return _prototypeFileList;
	}

	std::string GetPrototypeFile(std::string prototypeName)
	{
		if (_prototypeFileList.find(prototypeName) != _prototypeFileList.end())
		{
			return _prototypeFileList[prototypeName];
		}

		return std::string{}; //Empty String indicates prototypeFile does not exist 
	}


	//Gameplay mode
	//void SerialPrefabObjects(Serialiser& Level);	

//LevelEditor mode functions
	void SerialiseAllPrefabAssets(NamePath& list);
	void AddNewPrototypeAsset(GameObject* NewPrototype, std::string filePath)
	{
		NewPrototype->DeSerialise(filePath);	//Deserialise prototype into a .json File

		//Add Prototype Resource to editor Prototype List 
		IdentityComponent* IdCom = dynamic_cast<IdentityComponent*>(NewPrototype->GetComponent(ComponentId::CT_Identity));
		_listObjectPrototype.insert(std::pair <std::string, GameObject*>(IdCom->ObjectType(), NewPrototype));
		_prototypeFileList.insert(std::pair<std::string, std::string>(IdCom->ObjectType(), filePath));
	}


	//void RegisterComponent(std::string componentName);
	
	std::deque<std::string> GetComponentTypes()
	{
		return ComponentTypes;
	}



	//GameObject* SerialPrefabObjects(TypeIdGO type);

	//void CreatePreFabObject();


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
