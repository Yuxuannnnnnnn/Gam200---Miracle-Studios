#pragma once
#include <unordered_map>
#include <unordered_set>
#include "GameObject/GameObject.h"
#include "GameObject/ComponentCreator.h"

///Forward Declaration of Component Creator
class ComponentCreator;

class Factory
{
public:
	Factory();
	~Factory();

	Factory(const Factory& rhs) = delete;
	Factory& operator= (const Factory& rhs) = delete;

	///Build a GameObject and serialize from the data file but do not initialize the GameObject.
	///Used to create a GameObject and then adjust its data before initialization
	GameObject* BuildAndSerialize(const std::string& filename);

	///Create initialize and Id a GOC from the data file.
	GameObject* CloneGameObject(GameObject* gameobject);

	///Add a GOC to the destroy list for delayed destruction.
	void Destroy(GameObject* gameObject);

	///Update the factory, destroying dead objects.
	void Update(float dt);

	///Destroy all the GOCs in the world. Used for final shutdown.
	void DestroyAll();

	///Create and Id a GOC at runtime. Used to dynamically build GOC.
	///After components have been added call GOC->Initialize().
	GameObject* CreateEmptyGameObject();

	GameObject* CreateEmptyChildGameObject();

	size_t GetNextGameObjectUId();

	IComponent* CreateEmptyComponent(const std::string& name);

	///Add a component creator enabling data driven composition
	void AddComponentCreator(const std::string& name, ComponentCreator* creator);

	///Get the game object with given id. This function will return NULL if
	///the object has been destroyed.
	GameObject* GetObjectWithId(size_t id);

	////////////////////////////////////////////////////////////////////////

	bool CheckObjOrignialPointer(GameObject* obj);

	std::unordered_map<size_t, GameObject*>& getObjectlist();

	void SerialiseLevel(std::string FileName);		//Read LevelText and Instantiate GObj //Level is read when NextGameState is In-GameState
	void DeleteLevel();								//Level is Deleted when out of In-GameState
	void DeleteLevelNotPrefab();
	void De_SerialiseLevel(std::string filename);
	void WindowsDialogSaveLevel();

	////////////////////////////////////////////////////////////////////////////

	//Gameplay mode
	//void SerialPrefabObjects(Serialiser& Level);

	//LevelEditor mode
	void SerialiseAllPrefabAssets(std::unordered_map<std::string, std::string>& list);

	void AddNewPrototypeAsset(GameObject* NewPrototype, std::string filePath);

	///////////////////////////////////////////////////////////////////////////

	std::unordered_map<std::string, ComponentCreator*>& GetComponentList();

	///////////////////////////////////////////////////////////////////////////

	void ReInitScene();

	void UpdateScene();

	void ChangeScene(const std::string& scene);

	//For GamePlay 
	void SerialiseScenes(Serialiser GameSceneFile);

	//For Level Editor
	void LoadAllSceneAssets(std::unordered_map<std::string, std::string>& GameSceneFile);

	const std::string& GetCurrentScene();

	//For Level Editor
	void SetNewScene();

private:
	///Used to incrementally generate unique id's.
	unsigned _lastGameObjectId;

	///Map of component creator used for data driven composition
	typedef std::unordered_map<std::string, ComponentCreator*> ComponentMapType;
	ComponentMapType _componentMap;

	///Map of GameObject to their Ids used for safe referencing of game objects
	typedef std::unordered_map<size_t, GameObject*> GameObjectIdMapType;
	GameObjectIdMapType _gameObjectIdMap;

	///Objects to be deleted
	std::unordered_set<GameObject*> _objectsToBeDeleted;

	std::string _prevScene;
	std::string _currentScene;
};

#define AddEmptyComponent(type) MyFactory->CreateEmptyComponent( #type );
