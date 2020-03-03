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

	void Update(float dt); ///Update the factory, destroying dead objects.
	
	void InitScene();
	void UpdateScene();
	void ChangeScene(const std::string& scene);

	const std::string& GetCurrentScene();
	
	void SetNewScene(); //For Level Editor

	void SerialiseLevel(std::string FileName);		//Read LevelText and Instantiate GObj //Level is read when NextGameState is In-GameState

	void ClearLevel();				
	void De_SerialiseLevel(std::string filename);
	void WindowsDialogSaveLevel();

	void SerialiseScenes(Serialiser GameSceneFile); //For GamePlay 
	void LoadAllSceneAssets(std::unordered_map<std::string, std::string>& GameSceneFile); //For Level Editor

	//void SerialPrefabObjects(Serialiser& Level); //Gameplay mode
	void SerialiseAllPrefabAssets(std::unordered_map<std::string, std::string>& list); //LevelEditor mode

	void AddNewPrototypeAsset(GameObject* NewPrototype, std::string filePath);

	void SaveNewLinkID(int Id, size_t objectUId);
	GameObject* GetLinkIDObject(int Id);

	std::unordered_map<std::string, ComponentCreator*>& GetComponentList();
	std::unordered_map<size_t, GameObject*>& getObjectlist();

	int CheckObjOrignialPointer(GameObject* obj);

	///Create and Id a GOC at runtime. Used to dynamically build GOC.
	///After components have been added call GOC->Initialize().
	GameObject* CreateEmptyGameObject();
	GameObject* CreateEmptyChildGameObject();

	GameObject* CloneGameObject(GameObject* gameobject); ///Create initialize and Id a GOC from the data file.

	size_t GetNextGameObjectUId();

	GameObject* GetObjectWithId(size_t id); ///Get the game object with given id. This function will return NULL if the object has been destroyed.

	void AddComponentCreator(const std::string& name, ComponentCreator* creator); ///Add a component creator enabling data driven composition

	IComponent* CreateEmptyComponent(const std::string& name);

	void Destroy(GameObject* gameObject); 	///Add a GOC to the destroy list for delayed destruction.
	void DestroyAll(); 	///Destroy all the GOCs in the world. Used for final shutdown.

private:
	///Map of component creator used for data driven composition
	typedef std::unordered_map<std::string, ComponentCreator*> ComponentMapType;
	ComponentMapType _componentMap; 

	///Map of GameObject to their Ids used for safe referencing of game objects
	typedef std::unordered_map<size_t, GameObject*> GameObjectIdMapType;
	GameObjectIdMapType _gameObjectIdMap;

	///Objects to be deleted
	std::unordered_set<GameObject*> _objectsToBeDeleted;

	// linking
	std::unordered_map<int, size_t> _objectLinkMap;

	std::string _prevScene;
	std::string _currentScene;

	unsigned _lastGameObjectId; ///Used to incrementally generate unique id's.
};

#define AddEmptyComponent(type) MyFactory->CreateEmptyComponent( #type );

#define GetLinkObject(linkID) MyFactory->GetLinkIDObject(linkID);