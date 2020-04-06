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

	void Init();
	void Update(float dt); ///Update the factory, destroying dead objects.
	
	void InitScene();
	void UpdateScene();
	void ChangeScene(const std::string& scene);

	void SaveBackUpScene(); //For Level Editor when start play scene
	void LoadBackUpScene(); //For Level Editor when end play scene

	void LoadSceneResource();

	const std::string& GetCurrentScene();
	
	void SetNewScene(); //For Level Editor

	void SerialiseLevel(std::string FileName);		//Read LevelText and Instantiate GObj //Level is read when NextGameState is In-GameState

	void ClearLevel();				
	void De_SerialiseLevel(std::string filename);
	void DeSerialiseGameObject(GameObject* parent, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator);

	void WindowsDialogSaveLevel();

	std::string SerialiseScenes(Serialiser& GameSceneFile); //For GamePlay 
	void LoadAllSceneAssets(std::unordered_map<std::string, std::string>& GameSceneFile); //For Level Editor

	void AddNewPrototypeAsset(GameObject* NewPrototype, std::string filePath);

	void SaveNewLinkID(int Id, size_t objectUId);
	GameObject* GetLinkIDObject(int Id);

	std::unordered_map<std::string, ComponentCreator*>& GetComponentList();
	std::unordered_map<size_t, GameObject*>& getObjectlist();
	std::unordered_map<size_t, GameObject*>& getChildObjectlist();


	GameObject* GetObjOrignialPointer(size_t obj);
	GameObject* GetObjOrignialChildPointer(GameObject* obj, size_t original);


	///Create and Id a GOC at runtime. Used to dynamically build GOC.
	///After components have been added call GOC->Initialize().
	GameObject* CreateEmptyGameObject();
	GameObject* CreateEmptyChildGameObject();

	GameObject* CloneGameObject(GameObject* gameobject); ///Create initialize and Id a GOC from the data file.
	GameObject* CloneChildGameObject(GameObject* gameobject);
	GameObject* CloneChildGameObjectPrototype(GameObject* gameobject);

	void RemoveChildGameObject(size_t UId);

	size_t GetNextGameObjectUId();

	GameObject* GetObjectWithId(size_t id); ///Get the game object with given id. This function will return NULL if the object has been destroyed.

	void AddComponentCreator(const std::string& name, ComponentCreator* creator); ///Add a component creator enabling data driven composition

	IComponent* CreateEmptyComponent(const std::string& name);

	void Destroy(GameObject* gameObject); 	///Add a GOC to the destroy list for delayed destruction.
	void DestroyAll(); 	///Destroy all the GOCs in the world. Used for final shutdown.

	GameObject* CloneAndInitPrototype(std::string name);

	void SwapChildToParent(size_t UId);
	void SwapParentToChild(size_t UId);

	int CheckObjOrignialPointer(GameObject* obj);
	int CheckObjOrignialChildPointer(GameObject* obj, GameObject* original);

	bool _onceLag;
private:
	///Map of component creator used for data driven composition
	typedef std::unordered_map<std::string, ComponentCreator*> ComponentMapType;
	ComponentMapType _componentMap; 

	///Map of GameObject to their Ids used for safe referencing of game objects
	typedef std::unordered_map<size_t, GameObject*> GameObjectIdMapType;
	GameObjectIdMapType _gameObjectIdMap;
	GameObjectIdMapType _childGameObjectIdMap;

	std::unordered_set<size_t> _allExistGameObjectList;

	///Objects to be deleted
	std::unordered_set<GameObject*> _objectsToBeDeleted;

	// linking
	std::unordered_map<int, size_t> _objectLinkMap;

	std::string _prevScene;
	std::string _currentScene;

	std::string _currEditerScene;

	

	unsigned _lastGameObjectId; ///Used to incrementally generate unique id's.
};

#define AddEmptyComponent(type) MyFactory.CreateEmptyComponent( #type )

#define GetLinkObject(linkID) MyFactory.GetLinkIDObject(linkID)

#define CreateObject(name) MyFactory.CloneAndInitPrototype(name)