#include "PrecompiledHeaders.h"
#include "Engine/EngineSystems.h"
#include "../GameObjectComponents/LogicComponents/PrecompiledScriptType.h"
#include "Tools/EventHandler/EventHandler.h"
#include "GameObjectFactory.h"

//Constructor - Same as Initialisation
//Prototypes initialised - Prototypes Used for during entire Game, Only when Quit Game State then delete Prototypes
GameObjectFactory::GameObjectFactory()
	: _uId{ 1000 },
	_prefabId{ 0 },
	_listObject{},
	_graphicComponents{},
	_transformComponents{},
	_rigidBody2dComponents{},
	_collider2dComponents{},
	_scriptComponets{}
{
}


//Destructor - When QuitGameState, destruct all Prototypes
GameObjectFactory::~GameObjectFactory()
{

}


void GameObjectFactory::UpdateDestoryObjects()
{
	std::unordered_map < size_t, GameObject*> temp = _listObject;

	for (auto it : temp)
	{
		if (it.second->GetDestory())
		{
			if(!it.second->_alive)
				DestoryGameObject(it.second);

			it.second->_alive = false;
		}
	}
}


std::unordered_map<size_t, GameObject*> GameObjectFactory::getObjectlist()
{
	return _listObject;
}

std::unordered_map < size_t, GraphicComponent* > GameObjectFactory::getGraphicComponent()
{
	return _graphicComponents;
}

std::unordered_map < size_t, TransformComponent* > GameObjectFactory::getTransformComponent()
{
	return _transformComponents;
}

std::unordered_map < size_t, RigidBody2D* > GameObjectFactory::getRigidBodyComponent()
{
	return _rigidBody2dComponents;
}

std::unordered_map < size_t, Collider2D* > GameObjectFactory::getCollider2dComponent()
{
	return _collider2dComponents;
}

std::unordered_multimap<size_t, IScript*> GameObjectFactory::getScriptComponent()
{
	return _scriptComponets;
}

std::unordered_map < size_t, LogicComponent* > GameObjectFactory::getLogicComponent()
{
	return _logicComponents;
}

Map_ScriptList GameObjectFactory::getObjectScript(GameObject* object)
{
	LogicComponent* component = reinterpret_cast<LogicComponent*>(object->GetComponent(ComponentId::LOGIC_COMPONENT));

	if (component)
		return component->GetScriptMap();

	Map_ScriptList temp;
	return temp;
}


GameObject* GameObjectFactory::CreateNewGameObject(bool prefab)
{
	GameObject* newObject;

	if(prefab)
		newObject = new GameObject(_prefabId++);
	else
	{
		newObject = new GameObject(_uId++);

		PickingCollider* pickObject = new PickingCollider();
		pickObject->SetParentId(newObject->Get_uID());
		pickObject->SetParentPtr(newObject);

		_pickList.insert(std::pair< size_t, PickingCollider* >(pickObject->GetParentId(), pickObject));
		EngineSystems::GetInstance()._physicsSystem->_pickList.insert(std::pair< size_t, PickingCollider* >(pickObject->GetParentId(), pickObject));
	}
		
	_listObject.insert(std::pair< size_t, GameObject* >(newObject->Get_uID(), newObject));

	return newObject;
}
void GameObjectFactory::DestoryGameObject(GameObject* object)
{
	if (!object)
		return;

	size_t id = object->Get_uID();

	for (auto it : _listObject[id]->GetComponentList())
		RemoveComponent(_listObject[id], (ComponentId)it.first);

	{
		_pickList.erase(id);
		EngineSystems::GetInstance()._physicsSystem->_pickList.erase(id);
	}

	delete _listObject[id];
	_listObject.erase(id);
}

IComponentSystem* GameObjectFactory::AddComponent(GameObject* object, ComponentId type, ScriptId script)
{
	if (!object)
		return nullptr;

	bool prefab = object->Get_uID() < 1000 ? true : false;

	switch (type)
	{
	case ComponentId::IDENTITY_COMPONENT:
	{
		IdentityComponent* newComponent = new IdentityComponent();
		newComponent->SetParentId(object->Get_uID());
		newComponent->SetParentPtr(object);
		_IdentityComponents.insert(std::pair< size_t, IdentityComponent* >(object->Get_uID(), newComponent));

		return newComponent;
	}
	case ComponentId::TRANSFORM_COMPONENT:
	{
		TransformComponent* newComponent = new TransformComponent();
		newComponent->SetParentId(object->Get_uID());
		newComponent->SetParentPtr(object);
		_transformComponents.insert(std::pair< size_t, TransformComponent* >(object->Get_uID(), newComponent));

		if(!prefab)
			EngineSystems::GetInstance()._graphicsSystem->_transformList.insert(std::pair< size_t, TransformComponent* >(object->Get_uID(), newComponent));

		return newComponent;
	}
	case ComponentId::GRAPHICS_COMPONENT:
	{
		if (!object->CheckComponent(ComponentId::TRANSFORM_COMPONENT))
			object->AddComponent(ComponentId::TRANSFORM_COMPONENT);

		GraphicComponent* newComponent = new GraphicComponent(); // 
		newComponent->SetParentId(object->Get_uID());
		newComponent->SetParentPtr(object);
		_graphicComponents.insert(std::pair< size_t, GraphicComponent* >(object->Get_uID(), newComponent));
		newComponent->RenderLayerResolver();
		if (!prefab)
			EngineSystems::GetInstance()._graphicsSystem->_spriteList.insert(std::pair< size_t, GraphicComponent* >(object->Get_uID(), newComponent));

		return newComponent;
	}
	case ComponentId::ANIMATION_COMPONENT:
	{
		if (!object->CheckComponent(ComponentId::TRANSFORM_COMPONENT))
			object->AddComponent(ComponentId::TRANSFORM_COMPONENT);

		AnimationComponent* newComponent = new AnimationComponent();
		newComponent->SetParentId(object->Get_uID());
		newComponent->SetParentPtr(object);
		_AnimationComponents.insert(std::pair< size_t, AnimationComponent* >(object->Get_uID(), newComponent));

		return newComponent;
	}
	case ComponentId::CAMERA_COMPONENT:
	{
		if (!object->CheckComponent(ComponentId::TRANSFORM_COMPONENT))
			object->AddComponent(ComponentId::TRANSFORM_COMPONENT);

		CameraComponent* newComponent = new CameraComponent();
		newComponent->SetParentId(object->Get_uID());
		newComponent->SetParentPtr(object);
		_CameraComponents.insert(std::pair< size_t, CameraComponent* >(object->Get_uID(), newComponent));

		return newComponent;
	}
	case ComponentId::FONT_COMPONENT:
	{
		if (!object->CheckComponent(ComponentId::TRANSFORM_COMPONENT))
			object->AddComponent(ComponentId::TRANSFORM_COMPONENT);

		FontComponent* newComponent = new FontComponent();
		newComponent->SetParentId(object->Get_uID());
		newComponent->SetParentPtr(object);
		_FontComponent.insert(std::pair< size_t, FontComponent* >(object->Get_uID(), newComponent));

		return newComponent;
	}
	case ComponentId::RIGIDBODY_COMPONENT:
	{
		TransformComponent* transform;

		if (!object->CheckComponent(ComponentId::TRANSFORM_COMPONENT))
			transform = reinterpret_cast<TransformComponent*>(object->AddComponent(ComponentId::TRANSFORM_COMPONENT));
		else
			transform = reinterpret_cast<TransformComponent*>(object->GetComponent(ComponentId::TRANSFORM_COMPONENT));

		RigidBody2D* newComponent = new RigidBody2D(); // 
		newComponent->SetParentId(object->Get_uID());
		newComponent->SetParentPtr(object);
		newComponent->_transform = transform;
		_rigidBody2dComponents.insert(std::pair< size_t, RigidBody2D* >(object->Get_uID(), newComponent));
		
		Collider2D* collider = nullptr;

		if (object->CheckComponent(ComponentId::BOXCOLLIDER_COMPONENT))
			collider = reinterpret_cast<Collider2D*>(object->GetComponent(ComponentId::BOXCOLLIDER_COMPONENT));
		else if (object->CheckComponent(ComponentId::CIRCLECOLLIDER_COMPONENT))
			collider = reinterpret_cast<Collider2D*>(object->GetComponent(ComponentId::CIRCLECOLLIDER_COMPONENT));

		if (collider)
		{
			collider->_attachedRigidboy = true;
			collider->_rigidbody = newComponent;
		}

		if (!prefab)
			EngineSystems::GetInstance()._physicsSystem->_rigidBody2dList.insert(std::pair< size_t, RigidBody2D* >(object->Get_uID(), newComponent));

		return newComponent;
	}
	case ComponentId::CIRCLECOLLIDER_COMPONENT:
	{
		TransformComponent* transform;

		if (!object->CheckComponent(ComponentId::TRANSFORM_COMPONENT))
			transform = reinterpret_cast<TransformComponent*>(object->AddComponent(ComponentId::TRANSFORM_COMPONENT));
		else
			transform = reinterpret_cast<TransformComponent*>(object->GetComponent(ComponentId::TRANSFORM_COMPONENT));

		CircleCollider2D* newComponent = new CircleCollider2D(); // 
		newComponent->SetParentId(object->Get_uID());
		newComponent->SetParentPtr(object);
		newComponent->_transform = transform;
		_collider2dComponents.insert(std::pair< size_t, Collider2D* >(object->Get_uID(), newComponent));

		if (object->CheckComponent(ComponentId::RIGIDBODY_COMPONENT))
		{
			newComponent->_attachedRigidboy = true;
			newComponent->_rigidbody = reinterpret_cast<RigidBody2D*>(object->GetComponent(ComponentId::RIGIDBODY_COMPONENT));
		}

		if (!prefab)
			EngineSystems::GetInstance()._physicsSystem->_collider2dList.insert(std::pair< size_t, Collider2D* >(object->Get_uID(), newComponent));

		return newComponent;
	}
	case ComponentId::BOXCOLLIDER_COMPONENT:
	{
		TransformComponent* transform;

		if (!object->CheckComponent(ComponentId::TRANSFORM_COMPONENT))
			transform = reinterpret_cast<TransformComponent*>(object->AddComponent(ComponentId::TRANSFORM_COMPONENT));
		else
			transform = reinterpret_cast<TransformComponent*>(object->GetComponent(ComponentId::TRANSFORM_COMPONENT));

		BoxCollider2D* newComponent = new BoxCollider2D(); // 
		newComponent->SetParentId(object->Get_uID());
		newComponent->SetParentPtr(object);
		newComponent->_transform = transform;
		_collider2dComponents.insert(std::pair< size_t, Collider2D* >(object->Get_uID(), newComponent));

		if (object->CheckComponent(ComponentId::RIGIDBODY_COMPONENT))
		{
			newComponent->_attachedRigidboy = true;
			newComponent->_rigidbody = reinterpret_cast<RigidBody2D*>(object->GetComponent(ComponentId::RIGIDBODY_COMPONENT));
		}

		if (!prefab)
			EngineSystems::GetInstance()._physicsSystem->_collider2dList.insert(std::pair< size_t, Collider2D* >(object->Get_uID(), newComponent));

		return newComponent;
	}
	case ComponentId::EDGECOLLIDER_COMPONENT:
	{
		TransformComponent* transform;

		if (!object->CheckComponent(ComponentId::TRANSFORM_COMPONENT))
			transform = reinterpret_cast<TransformComponent*>(object->AddComponent(ComponentId::TRANSFORM_COMPONENT));
		else
			transform = reinterpret_cast<TransformComponent*>(object->GetComponent(ComponentId::TRANSFORM_COMPONENT));

		EdgeCollider2D* newComponent = new EdgeCollider2D(); // 
		newComponent->SetParentId(object->Get_uID());
		newComponent->SetParentPtr(object);
		newComponent->_transform = transform;
		_collider2dComponents.insert(std::pair< size_t, Collider2D* >(object->Get_uID(), newComponent));

		if (object->CheckComponent(ComponentId::RIGIDBODY_COMPONENT))
		{
			newComponent->_attachedRigidboy = true;
			newComponent->_rigidbody = reinterpret_cast<RigidBody2D*>(object->GetComponent(ComponentId::RIGIDBODY_COMPONENT));
		}

		if (!prefab)
			EngineSystems::GetInstance()._physicsSystem->_collider2dList.insert(std::pair< size_t, Collider2D* >(object->Get_uID(), newComponent));

		return newComponent;
	}
	case ComponentId::AUDIO_COMPONENT:
	{
		AudioComponent* newComponent = new AudioComponent(); // 
		newComponent->SetParentId(object->Get_uID());
		newComponent->SetParentPtr(object);
		_audioComponent.insert(std::pair< size_t, AudioComponent* >(object->Get_uID(), newComponent));

		return newComponent;
	}
	case ComponentId::LOGIC_COMPONENT:
	{
		LogicComponent* component;

		if (object->CheckComponent(ComponentId::LOGIC_COMPONENT))
		{
			component = reinterpret_cast<LogicComponent*>(object->GetComponent(ComponentId::LOGIC_COMPONENT));
		}
		else
		{
			component = new LogicComponent();
			component->SetParentId(object->Get_uID());
			component->SetParentPtr(object);
			_logicComponents.insert(std::pair< size_t, LogicComponent* >(object->Get_uID(), component));

			if (!prefab)
				EngineSystems::GetInstance()._logicSystem->_logicList.insert(std::pair< size_t, LogicComponent* >(object->Get_uID(), component));

		}

		if (script != ScriptId::EMPTY)
			component->AddScript(script);

		return component;
	}
	default:
		break;
	}

	return nullptr;
}

IComponentSystem* GameObjectFactory::CloneComponent(GameObject* object, IComponentSystem* component, ComponentId type)
{
	if (!component)
		return nullptr;

	switch (type)
	{
	case ComponentId::IDENTITY_COMPONENT:
	{
		IdentityComponent* newComponent = new IdentityComponent(*dynamic_cast<IdentityComponent*>(component));
		newComponent->SetParentId(object->Get_uID());
		newComponent->SetParentPtr(object);
		_IdentityComponents.insert(std::pair< size_t, IdentityComponent* >(object->Get_uID(), newComponent));

		return newComponent;
	}
	case ComponentId::TRANSFORM_COMPONENT:
	{
		TransformComponent* newComponent = new TransformComponent(*reinterpret_cast<TransformComponent*>(component));
		newComponent->SetParentId(object->Get_uID());
		newComponent->SetParentPtr(object);
		_transformComponents.insert(std::pair< size_t, TransformComponent* >(object->Get_uID(), newComponent));
		
		EngineSystems::GetInstance()._graphicsSystem->_transformList.insert(std::pair< size_t, TransformComponent* >(object->Get_uID(), newComponent));
		
		return newComponent;
	}
	case ComponentId::GRAPHICS_COMPONENT:
	{
		GraphicComponent* newComponent = new GraphicComponent(*reinterpret_cast<GraphicComponent*>(component));
		newComponent->SetParentId(object->Get_uID());
		newComponent->SetParentPtr(object);
		_graphicComponents.insert(std::pair< size_t, GraphicComponent* >(object->Get_uID(), newComponent));
		newComponent->RenderLayerResolver();
		EngineSystems::GetInstance()._graphicsSystem->_spriteList.insert(std::pair< size_t, GraphicComponent* >(object->Get_uID(), newComponent));
		
		return newComponent;
	}
	case ComponentId::ANIMATION_COMPONENT:
	{
		AnimationComponent* newComponent = new AnimationComponent(*reinterpret_cast<AnimationComponent*>(component));
		newComponent->SetParentId(object->Get_uID());
		newComponent->SetParentPtr(object);
		_AnimationComponents.insert(std::pair< size_t, AnimationComponent* >(object->Get_uID(), newComponent));

		return newComponent;
	}
	case ComponentId::CAMERA_COMPONENT:
	{
		CameraComponent* newComponent = new CameraComponent(*reinterpret_cast<CameraComponent*>(component));
		newComponent->SetParentId(object->Get_uID());
		newComponent->SetParentPtr(object);
		_CameraComponents.insert(std::pair< size_t, CameraComponent* >(object->Get_uID(), newComponent));

		return newComponent;
	}
	case ComponentId::FONT_COMPONENT:
	{
		FontComponent* newComponent = new FontComponent(*reinterpret_cast<FontComponent*>(component));
		newComponent->SetParentId(object->Get_uID());
		newComponent->SetParentPtr(object);
		_FontComponent.insert(std::pair< size_t, FontComponent* >(object->Get_uID(), newComponent));

		return newComponent;
	}
	case ComponentId::RIGIDBODY_COMPONENT:
	{
		TransformComponent* transform = reinterpret_cast<TransformComponent*>(object->GetComponent(ComponentId::TRANSFORM_COMPONENT));

		RigidBody2D* newComponent = new RigidBody2D(*reinterpret_cast<RigidBody2D*>(component));
		newComponent->SetParentId(object->Get_uID());
		newComponent->SetParentPtr(object);
		newComponent->_transform = transform;
		_rigidBody2dComponents.insert(std::pair< size_t, RigidBody2D* >(object->Get_uID(), newComponent));

		EngineSystems::GetInstance()._physicsSystem->_rigidBody2dList.insert(std::pair< size_t, RigidBody2D* >(object->Get_uID(), newComponent));

		return newComponent;
	}
	case ComponentId::CIRCLECOLLIDER_COMPONENT:
	{
		TransformComponent* transform = reinterpret_cast<TransformComponent*>(object->GetComponent(ComponentId::TRANSFORM_COMPONENT));

		CircleCollider2D* newComponent = new CircleCollider2D(*reinterpret_cast<CircleCollider2D*>(component));
		newComponent->SetParentId(object->Get_uID());
		newComponent->SetParentPtr(object);
		newComponent->_transform = transform;
		_collider2dComponents.insert(std::pair< size_t, Collider2D* >(object->Get_uID(), newComponent));

		if (object->CheckComponent(ComponentId::RIGIDBODY_COMPONENT))
		{
			newComponent->_attachedRigidboy = true;
			newComponent->_rigidbody = reinterpret_cast<RigidBody2D*>(object->GetComponent(ComponentId::RIGIDBODY_COMPONENT));
		}

		EngineSystems::GetInstance()._physicsSystem->_collider2dList.insert(std::pair< size_t, Collider2D* >(object->Get_uID(), newComponent));

		return newComponent;
	}
	case ComponentId::BOXCOLLIDER_COMPONENT:
	{
		TransformComponent* transform = reinterpret_cast<TransformComponent*>(object->GetComponent(ComponentId::TRANSFORM_COMPONENT));

		BoxCollider2D* newComponent = new BoxCollider2D(*reinterpret_cast<BoxCollider2D*>(component));
		newComponent->SetParentId(object->Get_uID());
		newComponent->SetParentPtr(object);
		newComponent->_transform = transform;
		_collider2dComponents.insert(std::pair< size_t, Collider2D* >(object->Get_uID(), newComponent));

		if (object->CheckComponent(ComponentId::RIGIDBODY_COMPONENT))
		{
			newComponent->_attachedRigidboy = true;
			newComponent->_rigidbody = reinterpret_cast<RigidBody2D*>(object->GetComponent(ComponentId::RIGIDBODY_COMPONENT));
		}

		EngineSystems::GetInstance()._physicsSystem->_collider2dList.insert(std::pair< size_t, Collider2D* >(object->Get_uID(), newComponent));

		return newComponent;
	}
	case ComponentId::EDGECOLLIDER_COMPONENT:
	{
		TransformComponent* transform = reinterpret_cast<TransformComponent*>(object->GetComponent(ComponentId::TRANSFORM_COMPONENT));

		EdgeCollider2D* newComponent = new EdgeCollider2D(*reinterpret_cast<EdgeCollider2D*>(component));
		newComponent->SetParentId(object->Get_uID());
		newComponent->SetParentPtr(object);
		newComponent->_transform = transform;
		_collider2dComponents.insert(std::pair< size_t, Collider2D* >(object->Get_uID(), newComponent));

		if (object->CheckComponent(ComponentId::RIGIDBODY_COMPONENT))
		{
			newComponent->_attachedRigidboy = true;
			newComponent->_rigidbody = reinterpret_cast<RigidBody2D*>(object->GetComponent(ComponentId::RIGIDBODY_COMPONENT));
		}

		EngineSystems::GetInstance()._physicsSystem->_collider2dList.insert(std::pair< size_t, Collider2D* >(object->Get_uID(), newComponent));

		return newComponent;
	}
	case ComponentId::AUDIO_COMPONENT:
	{
		AudioComponent* newComponent = new AudioComponent(*reinterpret_cast<AudioComponent*>(component));
		newComponent->SetParentId(object->Get_uID());
		newComponent->SetParentPtr(object);
		_audioComponent.insert(std::pair< size_t, AudioComponent* >(object->Get_uID(), newComponent));

		return newComponent;
	}
	case ComponentId::LOGIC_COMPONENT:
	{
		return CloneLogicComponent(object, reinterpret_cast<LogicComponent*>(component));;
	}
	default:
		break;
	}

	return nullptr;
}

void GameObjectFactory::RemoveComponent(GameObject* object, ComponentId tpye, ScriptId script)
{
	if (!object)
		return;
	switch (tpye)
	{
	case ComponentId::TRANSFORM_COMPONENT:
	{
		delete _transformComponents[object->Get_uID()];
		_transformComponents.erase(object->Get_uID());
		EngineSystems::GetInstance()._graphicsSystem->_transformList.erase(object->Get_uID());
		break;
	}
	case ComponentId::GRAPHICS_COMPONENT:
	{
		delete _graphicComponents[object->Get_uID()];
		_graphicComponents.erase(object->Get_uID());
		EngineSystems::GetInstance()._graphicsSystem->_spriteList.erase(object->Get_uID());
		break;
	}
	case ComponentId::RIGIDBODY_COMPONENT:
	{
		delete _rigidBody2dComponents[object->Get_uID()];
		_rigidBody2dComponents.erase(object->Get_uID());
		EngineSystems::GetInstance()._physicsSystem->_rigidBody2dList.erase(object->Get_uID());
		break;
	}
	case ComponentId::CIRCLECOLLIDER_COMPONENT:
	{
		delete _collider2dComponents[object->Get_uID()];
		_collider2dComponents.erase(object->Get_uID());
		EngineSystems::GetInstance()._physicsSystem->_collider2dList.erase(object->Get_uID());
		break;
	}
	case ComponentId::BOXCOLLIDER_COMPONENT:
	{
		delete _collider2dComponents[object->Get_uID()];
		_collider2dComponents.erase(object->Get_uID());
		EngineSystems::GetInstance()._physicsSystem->_collider2dList.erase(object->Get_uID());
		break;
	}
	case ComponentId::EDGECOLLIDER_COMPONENT:
	{
		delete _collider2dComponents[object->Get_uID()];
		_collider2dComponents.erase(object->Get_uID());
		EngineSystems::GetInstance()._physicsSystem->_collider2dList.erase(object->Get_uID());
		break;
	}
	case ComponentId::AUDIO_COMPONENT:
	{
		break;
	}
	case ComponentId::LOGIC_COMPONENT:
	{
		if (script == ScriptId::EMPTY)
		{
			for (auto it : _logicComponents[object->Get_uID()]->GetScriptMap())
			{
				RemoveScript(_logicComponents[object->Get_uID()], (ScriptId)it.first);
			}

			delete _logicComponents[object->Get_uID()];
			_logicComponents.erase(object->Get_uID());
			EngineSystems::GetInstance()._logicSystem->_logicList.erase(object->Get_uID());
			break;
		}

		RemoveScript(_logicComponents[object->Get_uID()], script);
		break;
	}
	default:
		break;
	}

}

GameObject* GameObjectFactory::CloneGameObject(GameObject* object)	//Create a gameObject type along with its Components
{
	GameObject* newObject = CreateNewGameObject();
	newObject->Set_typeId((TypeIdGO)object->Get_typeId());
	//Map_ComponentList& objectMap = newObject->GetComponentList();

	for (auto it : object->GetComponentList())
	{
		newObject->GetComponentList().insert(std::pair<unsigned, IComponentSystem*>(it.first, CloneComponent(newObject, it.second, (ComponentId)it.first)));
	}

	return newObject;
}

LogicComponent* GameObjectFactory::CloneLogicComponent(GameObject* object, LogicComponent* component)
{
	LogicComponent* newComponent = new LogicComponent();
	newComponent->SetParentId(object->Get_uID());
	newComponent->SetParentPtr(object);
	_logicComponents.insert(std::pair< size_t, LogicComponent* >(object->Get_uID(), newComponent));

	EngineSystems::GetInstance()._logicSystem->_logicList.insert(std::pair< size_t, LogicComponent* >(object->Get_uID(), newComponent));

	Map_ScriptList& scriptMap = newComponent->GetScriptMap();

	for (auto it : component->GetScriptMap())
		scriptMap.insert(std::pair<unsigned, IScript*>(it.first, CloneScript(newComponent, it.second, (ScriptId)it.first))); ;

	return newComponent;
}

IScript* GameObjectFactory::AddScript(LogicComponent* object, ScriptId scriptType)
{
	if (!object)
		return nullptr;

	switch (scriptType)
	{
	case ScriptId::EMPTY:
		break;
	case ScriptId::PLAYER:
	{
		Player* newScript = new Player();
		newScript->SetParentPtr(object->GetParentPtr());
		newScript->SetParentId(object->GetParentId());
		newScript->SetType(ScriptId::PLAYER);
		_scriptComponets.insert(std::pair<size_t, IScript*>(object->GetParentId(), newScript));
		return newScript;
	}
	case ScriptId::BULLET:
	{
		Bullet* newScript = new Bullet();
		newScript->SetParentPtr(object->GetParentPtr());
		newScript->SetParentId(object->GetParentId());
		newScript->SetType(ScriptId::BULLET);
		_scriptComponets.insert(std::pair<size_t, IScript*>(object->GetParentId(), newScript));
		return newScript;
	}
	case ScriptId::ENEMY:
	{
		Enemy* newScript = new Enemy();
		newScript->SetParentPtr(object->GetParentPtr());
		newScript->SetParentId(object->GetParentId());
		newScript->SetType(ScriptId::ENEMY);
		_scriptComponets.insert(std::pair<size_t, IScript*>(object->GetParentId(), newScript));
		return newScript;
	}
	case ScriptId::TURRET:
	{
		Turret* newScript = new Turret();
		newScript->SetParentPtr(object->GetParentPtr());
		newScript->SetParentId(object->GetParentId());
		newScript->SetType(ScriptId::TURRET);
		_scriptComponets.insert(std::pair<size_t, IScript*>(object->GetParentId(), newScript));
		return newScript;
	}
	case ScriptId::SPAWNER:
	{
		Spawner* newScript = new Spawner();
		newScript->SetParentPtr(object->GetParentPtr());
		newScript->SetParentId(object->GetParentId());
		newScript->SetType(ScriptId::SPAWNER);
		_scriptComponets.insert(std::pair<size_t, IScript*>(object->GetParentId(), newScript));
		return newScript;
	}
	case ScriptId::BULLET_E:
	{
		Bullet_E* newScript = new Bullet_E();
		newScript->SetParentPtr(object->GetParentPtr());
		newScript->SetParentId(object->GetParentId());
		newScript->SetType(ScriptId::BULLET_E);
		_scriptComponets.insert(std::pair<size_t, IScript*>(object->GetParentId(), newScript));
		return newScript;
	}
	case ScriptId::BULLET_T:
	{
		Bullet_T* newScript = new Bullet_T();
		newScript->SetParentPtr(object->GetParentPtr());
		newScript->SetParentId(object->GetParentId());
		newScript->SetType(ScriptId::BULLET_T);
		_scriptComponets.insert(std::pair<size_t, IScript*>(object->GetParentId(), newScript));
		return newScript;
	}
	case ScriptId::SPAWNERTWO:
	{
		SpawnerTwo* newScript = new SpawnerTwo();
		newScript->SetParentPtr(object->GetParentPtr());
		newScript->SetParentId(object->GetParentId());
		newScript->SetType(ScriptId::SPAWNERTWO);
		_scriptComponets.insert(std::pair<size_t, IScript*>(object->GetParentId(), newScript));
		return newScript;
	}
	case ScriptId::EXPLOSION:
	{
		Explosion* newScript = new Explosion();
		newScript->SetParentPtr(object->GetParentPtr());
		newScript->SetParentId(object->GetParentId());
		newScript->SetType(ScriptId::EXPLOSION);
		_scriptComponets.insert(std::pair<size_t, IScript*>(object->GetParentId(), newScript));
		return newScript;
	}
	case ScriptId::BUTTON_UI:
	{
		ButtonUI* newScript = new ButtonUI();
		newScript->SetParentPtr(object->GetParentPtr());
		newScript->SetParentId(object->GetParentId());
		newScript->SetType(ScriptId::BUTTON_UI);
		_scriptComponets.insert(std::pair<size_t, IScript*>(object->GetParentId(), newScript));
		return newScript;
	}
	default:
		break;
	}

	return nullptr;
}

IScript* GameObjectFactory::CloneScript(LogicComponent* object, IScript* script, ScriptId scriptType)
{
	if (!object)
		return nullptr;

	switch (scriptType)
	{
	case ScriptId::EMPTY:
		break;
	case ScriptId::PLAYER:
	{
		Player* newScript = new Player(* reinterpret_cast<Player*>(script));
		newScript->SetParentPtr(object->GetParentPtr());
		newScript->SetParentId(object->GetParentId());
		newScript->SetType(ScriptId::PLAYER);
		_scriptComponets.insert(std::pair<size_t, IScript*>(object->GetParentId(), newScript));
		return newScript;
	}
	case ScriptId::BULLET:
	{
		Bullet* newScript = new Bullet(*reinterpret_cast<Bullet*>(script));
		newScript->SetParentPtr(object->GetParentPtr());
		newScript->SetParentId(object->GetParentId());
		newScript->SetType(ScriptId::BULLET);
		_scriptComponets.insert(std::pair<size_t, IScript*>(object->GetParentId(), newScript));
		return newScript;
	}
	case ScriptId::ENEMY:
	{
		Enemy* newScript = new Enemy(*reinterpret_cast<Enemy*>(script));
		newScript->SetParentPtr(object->GetParentPtr());
		newScript->SetParentId(object->GetParentId());
		newScript->SetType(ScriptId::ENEMY);
		_scriptComponets.insert(std::pair<size_t, IScript*>(object->GetParentId(), newScript));
		return newScript;
	}
	case ScriptId::TURRET:
	{
		Turret* newScript = new Turret(*reinterpret_cast<Turret*>(script));
		newScript->SetParentPtr(object->GetParentPtr());
		newScript->SetParentId(object->GetParentId());
		newScript->SetType(ScriptId::TURRET);
		_scriptComponets.insert(std::pair<size_t, IScript*>(object->GetParentId(), newScript));
		return newScript;
	}
	case ScriptId::SPAWNER:
	{
		Spawner* newScript = new Spawner();
		newScript->SetParentPtr(object->GetParentPtr());
		newScript->SetParentId(object->GetParentId());
		newScript->SetType(ScriptId::SPAWNER);
		_scriptComponets.insert(std::pair<size_t, IScript*>(object->GetParentId(), newScript));
		return newScript;
	}
	case ScriptId::BULLET_E:
	{
		Bullet_E* newScript = new Bullet_E(*reinterpret_cast<Bullet_E*>(script));
		newScript->SetParentPtr(object->GetParentPtr());
		newScript->SetParentId(object->GetParentId());
		newScript->SetType(ScriptId::BULLET_E);
		_scriptComponets.insert(std::pair<size_t, IScript*>(object->GetParentId(), newScript));
		return newScript;
	}
	case ScriptId::BULLET_T:
	{
		Bullet_T* newScript = new Bullet_T(*reinterpret_cast<Bullet_T*>(script));
		newScript->SetParentPtr(object->GetParentPtr());
		newScript->SetParentId(object->GetParentId());
		newScript->SetType(ScriptId::BULLET_T);
		_scriptComponets.insert(std::pair<size_t, IScript*>(object->GetParentId(), newScript));
		return newScript;
	}
	case ScriptId::SPAWNERTWO:
	{
		SpawnerTwo* newScript = new SpawnerTwo(*reinterpret_cast<SpawnerTwo*>(script));
		newScript->SetParentPtr(object->GetParentPtr());
		newScript->SetParentId(object->GetParentId());
		newScript->SetType(ScriptId::SPAWNERTWO);
		_scriptComponets.insert(std::pair<size_t, IScript*>(object->GetParentId(), newScript));
		return newScript;
	}
	case ScriptId::EXPLOSION:
	{
		Explosion* newScript = new Explosion(*reinterpret_cast<Explosion*>(script));
		newScript->SetParentPtr(object->GetParentPtr());
		newScript->SetParentId(object->GetParentId());
		newScript->SetType(ScriptId::EXPLOSION);
		_scriptComponets.insert(std::pair<size_t, IScript*>(object->GetParentId(), newScript));
		return newScript;
	}
	case ScriptId::BUTTON_UI:
	{
		ButtonUI* newScript = new ButtonUI(*reinterpret_cast<ButtonUI*>(script));
		newScript->SetParentPtr(object->GetParentPtr());
		newScript->SetParentId(object->GetParentId());
		newScript->SetType(ScriptId::BUTTON_UI);
		_scriptComponets.insert(std::pair<size_t, IScript*>(object->GetParentId(), newScript));
		return newScript;
	}
	default:
		break;
	}

	return nullptr;
}

void GameObjectFactory::RemoveScript(LogicComponent* object, ScriptId scriptType)
{
	std::pair <std::unordered_multimap<size_t, IScript*>::iterator, std::unordered_multimap<size_t, IScript*>::iterator> ret;
	ret = _scriptComponets.equal_range(object->GetParentId());

	for (std::unordered_multimap<size_t, IScript*>::iterator it = ret.first; it != ret.second; ++it)
	{
		if (it->second->GetType() == scriptType)
		{
			delete it->second;
			_scriptComponets.erase(it);
			return;
		}
	}
}


//Read LevelText and Instantiate GObj - When Next Game State is In-Game, Create all level objects
void GameObjectFactory::FileRead_Level(const char* FileName)
{ // will move to ObjectFactory
	std::cout << "FileRead_Level( " << FileName << " )" << std::endl;
	std::fstream _file;
	_file.open(FileName, std::ios_base::in | std::ios_base::binary);
	if (!_file.is_open())
	{
		std::cout << "! WARNING !! File Cannot Open!!!" << std::endl
			<< FileName << std::endl;
		return;
	}
	char* strType = new char[20]; // for Type
	// for any input (max inputs)
	char* strNum1 = new char[10];
	char* strNum2 = new char[10];
	float num1, num2;
	GameObject* tempGO = nullptr;
	IComponentSystem* tempComp = nullptr;

	while (_file.good()) // each loop read 4 lines: Type, Pos, Scale, Rot
	{
	// Get Type
		//_file.getline(strType, 20, '\n\r');
		_file >> strType;
		if (std::strcmp(strType, "Player") == 0)
			tempGO = CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::PLAYER]);
		else if (std::strcmp(strType, "Enemy") == 0)
			tempGO = CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::ENEMY]);
		else if (std::strcmp(strType, "Wall") == 0)
			tempGO = CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::WALL]);
		else if (std::strcmp(strType, "Camera") == 0)
			tempGO = CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::CAMERA]);
		else
			ASSERT("Serialise-File Attempted to create UNKNOWN GO" && false);
	// TransformComponent from 'temp'
		tempComp = tempGO->GetComponentList()[(unsigned)ComponentId::TRANSFORM_COMPONENT];

	// get Position
		ASSERT(_file.getline(strNum1, 10, ','));
		ASSERT(_file.getline(strNum2, 10));
		num1 = std::stof(strNum1);
		num2 = std::stof(strNum2);
		((TransformComponent*)tempComp)->GetPos() = Vector3(num1, num2, 1);
	// get Scale
		ASSERT(_file.getline(strNum1, 10, ','));
		ASSERT(_file.getline(strNum2, 10));
		num1 = std::stof(strNum1);
		num2 = std::stof(strNum2);
		((TransformComponent*)tempComp)->GetScale() = Vector3(num1, num2, 1);

	// get Rotate
		ASSERT(_file.getline(strNum1, 10));
		num1 = std::stof(strNum1);
		((TransformComponent*)tempComp)->GetRotate() = num1;
	}

	_file.close();
	delete[] strType;
	delete[] strNum1;
	delete[] strNum2;
	return;
}

void GameObjectFactory::DeleteLevel()
{
	for (auto it : _listObject)
		delete it.second;
	_listObject.clear();

	for (auto it : _graphicComponents)
		delete it.second;
	_graphicComponents.clear();

	for (auto it : _transformComponents)
		delete it.second;
	_transformComponents.clear();

	for (auto it : _rigidBody2dComponents)
		delete it.second;
	_rigidBody2dComponents.clear();

	for (auto it : _collider2dComponents)
		delete it.second;
	_collider2dComponents.clear();

	for (auto it : _logicComponents)
		delete it.second;
	_logicComponents.clear();

	for (auto it : _scriptComponets)
		delete it.second;
	_scriptComponets.clear();

	for (auto it : _pickList)
		delete it.second;
	_pickList.clear();
}



 
