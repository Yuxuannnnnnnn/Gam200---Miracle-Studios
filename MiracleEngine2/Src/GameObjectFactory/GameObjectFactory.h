#pragma once
#include "GameObject.h"
#include "GameStateManager/GameStateManager.h"
#include "GameObjectComponents/PrecompiledComponentHeader.h"
#include "GameObjectComponents/PickingCollider.h"
#include "GameObjectComponents/IdentityComponent.h"
#include "GameObjectComponents/GraphicComponents/AnimationComponent.h"
#include "GameObjectComponents/GraphicComponents/CameraComponent.h"

class GameObjectFactory final
{	
	size_t _uId;		// start from StartID, 0 to StartID are prefabs	//Unique ID for the next newly created object
	size_t _prefabId;

	std::unordered_map < size_t, GameObject* >			_listObject; //Dynamic array of GameObjects
	std::unordered_map < size_t, IdentityComponent* >	_IdentityComponents;	//Array of Components

	std::unordered_map < size_t, GraphicComponent* >	_graphicComponents;	//Array of Components
	std::unordered_map < size_t, TransformComponent*>  _transformComponents;	//
	std::unordered_map < size_t, AnimationComponent*>	_AnimationComponents;	//
	std::unordered_map < size_t, CameraComponent*>		_CameraComponents;		//
	std::unordered_map < size_t, RigidBody2D* >			_rigidBody2dComponents;	//
	std::unordered_map < size_t, Collider2D* >			_collider2dComponents;	//
	std::unordered_map < size_t, LogicComponent* >		_logicComponents;	//
	std::unordered_multimap<size_t, IScript*>			_scriptComponets;
	std::unordered_multimap<size_t, PickingCollider*>	_pickList;
	std::unordered_map<size_t, AudioComponent*>			_audioComponent;		//


public:
	GameObjectFactory(const GameObjectFactory& rhs) = delete;
	GameObjectFactory& operator= (const GameObjectFactory& rhs) = delete;

	GameObjectFactory();
	~GameObjectFactory();

	void UpdateDestoryObjects();

	std::unordered_map < size_t, GameObject*> getObjectlist();
	std::unordered_map < size_t, GraphicComponent* > getGraphicComponent();		
	std::unordered_map < size_t, TransformComponent* > getTransformComponent();
	std::unordered_map < size_t, RigidBody2D* > getRigidBodyComponent();	
	std::unordered_map < size_t, Collider2D* > getCollider2dComponent();
	std::unordered_map < size_t, LogicComponent* > getLogicComponent();
	std::unordered_multimap<size_t, IScript*> getScriptComponent();
	std::unordered_map < size_t, CameraComponent*>	 getCameraComponent()
	{
		return _CameraComponents;
	}

	Map_ScriptList getObjectScript(GameObject* object);

	GameObject* CreateNewGameObject(bool prefab = false);
	GameObject* CloneGameObject(GameObject* object);
	void DestoryGameObject(GameObject* object);

	IComponentSystem* AddComponent(GameObject* object, ComponentId tpye, ScriptId script = ScriptId::EMPTY);
	IComponentSystem* CloneComponent(GameObject* object, IComponentSystem* component, ComponentId tpye);
	void RemoveComponent(GameObject* object, ComponentId tpye, ScriptId script = ScriptId::EMPTY);

	LogicComponent* CloneLogicComponent(GameObject* object, LogicComponent* component);

	IScript* AddScript(LogicComponent* object, ScriptId scriptType);
	IScript* CloneScript(LogicComponent* object, IScript* script, ScriptId scriptType);
	void RemoveScript(LogicComponent* object, ScriptId scriptType);

	void FileRead_Level(const char* FileName);		//Read LevelText and Instantiate GObj //Level is read when NextGameState is In-GameState
	void DeleteLevel();								//Level is Deleted when out of In-GameState
};