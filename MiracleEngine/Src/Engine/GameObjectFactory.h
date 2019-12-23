#pragma once
#include "GameObject/GameObject.h"


#include "GameObject/Components/PrecompiledComponentHeader.h"
#include "Tools/FileIO/Serialiser.h"
#include <algorithm>

class GameObjectFactory final
{	
	size_t _uId;		// start from StartID, 0 to StartID are prefabs	//Unique ID for the next newly created object
	size_t _prefabId;

	std::unordered_map < size_t, GameObject* >			_listObject; //Dynamic array of GameObjects
public:


	bool CheckObjOrignialPointer(GameObject * obj)
	{
		for (auto& pair : _listObject)
		{
			if(pair.second == obj)
				return true;
		}
		return false;
	}
	std::unordered_map < size_t, GameObject*>& getObjectlist();

	GameObjectFactory(const GameObjectFactory& rhs) = delete;
	GameObjectFactory& operator= (const GameObjectFactory& rhs) = delete;

	GameObjectFactory();
	~GameObjectFactory();

	void UpdateDestoryObjects();

	Map_ScriptList getObjectScript(GameObject* object);

	GameObject* CreateNewGameObject(bool prefab = false);
	GameObject* CloneGameObject(GameObject* object);
	void DestoryGameObject(GameObject* object);

	IComponent* AddComponent(GameObject* object, ComponentId tpye, ScriptId script = ScriptId::EMPTY);
	IComponent* CloneComponent(GameObject* object, IComponent* component, ComponentId tpye);
	void RemoveComponent(GameObject* object, ComponentId tpye, ScriptId script = ScriptId::EMPTY);

	LogicComponent* CloneLogicComponent(GameObject* object, LogicComponent* component);


	void SerialiseLevel(std::string filePath);		//Read LevelText and Instantiate GObj //Level is read when NextGameState is In-GameState
	void DeleteLevel();								//Level is Deleted when out of In-GameState
	void DeleteLevelNotPrefab();

	void De_SerialiseLevel(std::string filePath);
};