#include "PrecompiledHeaders.h"


//Constructor - Same as Initialisation
//Prototypes initialised - Prototypes Used for during entire Game, Only when Quit Game State then delete Prototypes
GameObjectFactory::GameObjectFactory()
	: _uId{ 1000 },
	_prefabId{ 0 },
	_listObject{}
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
			if (!it.second->GetAlive())
				DestoryGameObject(it.second);

			it.second->SetAlive(false);
		}
	}
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

	if (prefab)
	{
		newObject = new GameObject(_prefabId++);
		//By Default should add a Identity component when new ProtoType is created
		IComponent* component = newObject->AddComponent(ComponentId::IDENTITY_COMPONENT);
		component->SetParentId(newObject->Get_uID());
		component->SetParentPtr(newObject);
	}
	else
		newObject = new GameObject(_uId++);

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

	delete _listObject[id];
	_listObject.erase(id);
}

IComponent* GameObjectFactory::AddComponent(GameObject* object, ComponentId type, ScriptId script)
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
		MyComponentManger._IdentityComponents.insert(std::pair< size_t, IdentityComponent* >(object->Get_uID(), newComponent));

		return newComponent;
	}
	case ComponentId::TRANSFORM_COMPONENT:
	{
		TransformComponent* newComponent = new TransformComponent();
		newComponent->SetParentId(object->Get_uID());
		newComponent->SetParentPtr(object);
		MyComponentManger._transformComponents.insert(std::pair< size_t, TransformComponent* >(object->Get_uID(), newComponent));

		return newComponent;
	}
	case ComponentId::GRAPHICS_COMPONENT:
	{
		if (!object->CheckComponent(ComponentId::TRANSFORM_COMPONENT))
			object->AddComponent(ComponentId::TRANSFORM_COMPONENT);

		GraphicComponent* newComponent = new GraphicComponent(); // 
		newComponent->SetParentId(object->Get_uID());
		newComponent->SetParentPtr(object);
		MyComponentManger._graphicComponents.insert(std::pair< size_t, GraphicComponent* >(object->Get_uID(), newComponent));
		newComponent->RenderLayerResolver();
		if (!prefab)
		{

#ifdef LEVELEDITOR

			PickingCollider* pickObject = new PickingCollider();
			pickObject->SetParentId(object->Get_uID());
			pickObject->SetParentPtr(object);

			MyComponentManger._imGuizmoComponent.insert(std::pair< size_t, PickingCollider* >(pickObject->GetParentId(), pickObject));
#endif
		}

		return newComponent;
	}
	case ComponentId::ANIMATION_COMPONENT:
	{
		if (!object->CheckComponent(ComponentId::TRANSFORM_COMPONENT))
			object->AddComponent(ComponentId::TRANSFORM_COMPONENT);

		AnimationComponent* newComponent = new AnimationComponent();
		newComponent->SetParentId(object->Get_uID());
		newComponent->SetParentPtr(object);
		MyComponentManger._AnimationComponents.insert(std::pair< size_t, AnimationComponent* >(object->Get_uID(), newComponent));
		return newComponent;
	}
	case ComponentId::CAMERA_COMPONENT:
	{
		if (!object->CheckComponent(ComponentId::TRANSFORM_COMPONENT))
			object->AddComponent(ComponentId::TRANSFORM_COMPONENT);

		CameraComponent* newComponent = new CameraComponent();
		newComponent->SetParentId(object->Get_uID());
		newComponent->SetParentPtr(object);
		MyComponentManger._CameraComponents.insert(std::pair< size_t, CameraComponent* >(object->Get_uID(), newComponent));

		return newComponent;
	}
	case ComponentId::FONT_COMPONENT:
	{
		if (!object->CheckComponent(ComponentId::TRANSFORM_COMPONENT))
			object->AddComponent(ComponentId::TRANSFORM_COMPONENT);

		FontComponent* newComponent = new FontComponent();
		newComponent->SetParentId(object->Get_uID());
		newComponent->SetParentPtr(object);
		MyComponentManger._FontComponent.insert(std::pair< size_t, FontComponent* >(object->Get_uID(), newComponent));

		return newComponent;
	}
	case ComponentId::BUTTON_COMPONENT:
	{
		ButtonComponent* newComponent = new ButtonComponent();
		newComponent->SetParentId(object->Get_uID());
		newComponent->SetParentPtr(object);
		MyComponentManger._buttonComponent.insert(std::pair< size_t, ButtonComponent* >(object->Get_uID(), newComponent));

		return newComponent;
	}
	case ComponentId::RIGIDBODY_COMPONENT:
	{
		//TransformComponent* transform;

		if (!object->CheckComponent(ComponentId::TRANSFORM_COMPONENT))
			object->AddComponent(ComponentId::TRANSFORM_COMPONENT);

		RigidBody2D* newComponent = new RigidBody2D(); // 
		newComponent->SetParentId(object->Get_uID());
		newComponent->SetParentPtr(object);
		MyComponentManger._rigidbody2DComponent.insert(std::pair< size_t, RigidBody2D* >(object->Get_uID(), newComponent));

		Collider2D* collider = nullptr;

		if (object->CheckComponent(ComponentId::BOXCOLLIDER_COMPONENT))
			collider = reinterpret_cast<Collider2D*>(object->GetComponent(ComponentId::BOXCOLLIDER_COMPONENT));
		else if (object->CheckComponent(ComponentId::CIRCLECOLLIDER_COMPONENT))
			collider = reinterpret_cast<Collider2D*>(object->GetComponent(ComponentId::CIRCLECOLLIDER_COMPONENT));

		if (collider)
			collider->_attachedRigidboy = true;

		return newComponent;
	}
	case ComponentId::CIRCLECOLLIDER_COMPONENT:
	{
		//TransformComponent* transform;

		if (!object->CheckComponent(ComponentId::TRANSFORM_COMPONENT))
			object->AddComponent(ComponentId::TRANSFORM_COMPONENT);

		CircleCollider2D* newComponent = new CircleCollider2D(); // 
		newComponent->SetParentId(object->Get_uID());
		newComponent->SetParentPtr(object);
		MyComponentManger._collider2dComponents.insert(std::pair< size_t, Collider2D* >(object->Get_uID(), newComponent));

		if (object->CheckComponent(ComponentId::RIGIDBODY_COMPONENT))
			newComponent->_attachedRigidboy = true;


		return newComponent;
	}
	case ComponentId::BOXCOLLIDER_COMPONENT:
	{
		//TransformComponent* transform;

		if (!object->CheckComponent(ComponentId::TRANSFORM_COMPONENT))
			object->AddComponent(ComponentId::TRANSFORM_COMPONENT);

		BoxCollider2D* newComponent = new BoxCollider2D(); // 
		newComponent->SetParentId(object->Get_uID());
		newComponent->SetParentPtr(object);
		MyComponentManger._collider2dComponents.insert(std::pair< size_t, Collider2D* >(object->Get_uID(), newComponent));

		if (object->CheckComponent(ComponentId::RIGIDBODY_COMPONENT))
			newComponent->_attachedRigidboy = true;

		return newComponent;
	}
	case ComponentId::EDGECOLLIDER_COMPONENT:
	{
		//TransformComponent* transform;

		if (!object->CheckComponent(ComponentId::TRANSFORM_COMPONENT))
			object->AddComponent(ComponentId::TRANSFORM_COMPONENT);

		EdgeCollider2D* newComponent = new EdgeCollider2D(); // 
		newComponent->SetParentId(object->Get_uID());
		newComponent->SetParentPtr(object);
		MyComponentManger._collider2dComponents.insert(std::pair< size_t, Collider2D* >(object->Get_uID(), newComponent));

		if (object->CheckComponent(ComponentId::RIGIDBODY_COMPONENT))
			newComponent->_attachedRigidboy = true;

		return newComponent;
	}
	case ComponentId::AUDIO_COMPONENT:
	{
		AudioComponent* newComponent = new AudioComponent(); // 
		newComponent->SetParentId(object->Get_uID());
		newComponent->SetParentPtr(object);
		MyComponentManger._audioComponent.insert(std::pair< size_t, AudioComponent* >(object->Get_uID(), newComponent));

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
			MyComponentManger._logicComponents.insert(std::pair< size_t, LogicComponent* >(object->Get_uID(), component));

		}

		if (script != ScriptId::EMPTY)
			component->AddScript(script);

		return component;
	}
	case ComponentId::TILEMAP_COMPONENT:
	{
		TileMapComponent* newComponent = new TileMapComponent();
		newComponent->SetParentId(object->Get_uID());
		newComponent->SetParentPtr(object);
		MyComponentManger._TileMapComponents.insert(std::pair< size_t, TileMapComponent* >(object->Get_uID(), newComponent));

		return newComponent;
	}
	default:
		break;
	}

	return nullptr;
}

IComponent* GameObjectFactory::CloneComponent(GameObject* object, IComponent* component, ComponentId type)
{
	if (!component)
		return nullptr;

	switch (type)
	{
	case ComponentId::IDENTITY_COMPONENT:
	{
		IdentityComponent* newComponent = new IdentityComponent(*reinterpret_cast<IdentityComponent*>(component));
		newComponent->SetParentId(object->Get_uID());
		newComponent->SetParentPtr(object);
		MyComponentManger._IdentityComponents.insert(std::pair< size_t, IdentityComponent* >(object->Get_uID(), newComponent));

		return newComponent;
	}
	case ComponentId::TRANSFORM_COMPONENT:
	{
		TransformComponent* newComponent = new TransformComponent(*reinterpret_cast<TransformComponent*>(component));
		newComponent->SetParentId(object->Get_uID());
		newComponent->SetParentPtr(object);
		MyComponentManger._transformComponents.insert(std::pair< size_t, TransformComponent* >(object->Get_uID(), newComponent));

		return newComponent;
	}
	case ComponentId::GRAPHICS_COMPONENT:
	{
		GraphicComponent* newComponent = new GraphicComponent(*reinterpret_cast<GraphicComponent*>(component));
		newComponent->SetParentId(object->Get_uID());
		newComponent->SetParentPtr(object);
		MyComponentManger._graphicComponents.insert(std::pair< size_t, GraphicComponent* >(object->Get_uID(), newComponent));
		newComponent->RenderLayerResolver();


#ifdef LEVELEDITOR

		PickingCollider* pickObject = new PickingCollider();
		pickObject->SetParentId(object->Get_uID());
		pickObject->SetParentPtr(object);

		MyComponentManger._imGuizmoComponent.insert(std::pair< size_t, PickingCollider* >(pickObject->GetParentId(), pickObject));
#endif

		return newComponent;
	}
	case ComponentId::ANIMATION_COMPONENT:
	{
		AnimationComponent* newComponent = new AnimationComponent(*reinterpret_cast<AnimationComponent*>(component));
		newComponent->SetParentId(object->Get_uID());
		newComponent->SetParentPtr(object);
		MyComponentManger._AnimationComponents.insert(std::pair< size_t, AnimationComponent* >(object->Get_uID(), newComponent));

		return newComponent;
	}
	case ComponentId::CAMERA_COMPONENT:
	{
		CameraComponent* newComponent = new CameraComponent(*reinterpret_cast<CameraComponent*>(component));
		newComponent->SetParentId(object->Get_uID());
		newComponent->SetParentPtr(object);
		MyComponentManger._CameraComponents.insert(std::pair< size_t, CameraComponent* >(object->Get_uID(), newComponent));

		return newComponent;
	}
	case ComponentId::FONT_COMPONENT:
	{
		FontComponent* newComponent = new FontComponent(*reinterpret_cast<FontComponent*>(component));
		newComponent->SetParentId(object->Get_uID());
		newComponent->SetParentPtr(object);
		MyComponentManger._FontComponent.insert(std::pair< size_t, FontComponent* >(object->Get_uID(), newComponent));

		return newComponent;
	}
	case ComponentId::BUTTON_COMPONENT:
	{
		ButtonComponent* newComponent = new ButtonComponent(*reinterpret_cast<ButtonComponent*>(component));
		newComponent->SetParentId(object->Get_uID());
		newComponent->SetParentPtr(object);
		MyComponentManger._buttonComponent.insert(std::pair< size_t, ButtonComponent* >(object->Get_uID(), newComponent));

		return newComponent;
	}
	case ComponentId::RIGIDBODY_COMPONENT:
	{
		TransformComponent* transform = reinterpret_cast<TransformComponent*>(object->GetComponent(ComponentId::TRANSFORM_COMPONENT));

		RigidBody2D* newComponent = new RigidBody2D(*reinterpret_cast<RigidBody2D*>(component));
		newComponent->SetParentId(object->Get_uID());
		newComponent->SetParentPtr(object);
		MyComponentManger._rigidbody2DComponent.insert(std::pair< size_t, RigidBody2D* >(object->Get_uID(), newComponent));

		return newComponent;
	}
	case ComponentId::CIRCLECOLLIDER_COMPONENT:
	{
		TransformComponent* transform = reinterpret_cast<TransformComponent*>(object->GetComponent(ComponentId::TRANSFORM_COMPONENT));

		CircleCollider2D* newComponent = new CircleCollider2D(*reinterpret_cast<CircleCollider2D*>(component));
		newComponent->SetParentId(object->Get_uID());
		newComponent->SetParentPtr(object);
		MyComponentManger._collider2dComponents.insert(std::pair< size_t, Collider2D* >(object->Get_uID(), newComponent));

		return newComponent;
	}
	case ComponentId::BOXCOLLIDER_COMPONENT:
	{
		TransformComponent* transform = reinterpret_cast<TransformComponent*>(object->GetComponent(ComponentId::TRANSFORM_COMPONENT));

		BoxCollider2D* newComponent = new BoxCollider2D(*reinterpret_cast<BoxCollider2D*>(component));
		newComponent->SetParentId(object->Get_uID());
		newComponent->SetParentPtr(object);
		MyComponentManger._collider2dComponents.insert(std::pair< size_t, Collider2D* >(object->Get_uID(), newComponent));

		return newComponent;
	}
	case ComponentId::EDGECOLLIDER_COMPONENT:
	{
		TransformComponent* transform = reinterpret_cast<TransformComponent*>(object->GetComponent(ComponentId::TRANSFORM_COMPONENT));

		EdgeCollider2D* newComponent = new EdgeCollider2D(*reinterpret_cast<EdgeCollider2D*>(component));
		newComponent->SetParentId(object->Get_uID());
		newComponent->SetParentPtr(object);
		MyComponentManger._collider2dComponents.insert(std::pair< size_t, Collider2D* >(object->Get_uID(), newComponent));

		return newComponent;
	}
	case ComponentId::AUDIO_COMPONENT:
	{
		AudioComponent* newComponent = new AudioComponent(*reinterpret_cast<AudioComponent*>(component));
		newComponent->SetParentId(object->Get_uID());
		newComponent->SetParentPtr(object);
		MyComponentManger._audioComponent.insert(std::pair< size_t, AudioComponent* >(object->Get_uID(), newComponent));

		return newComponent;
	}
	case ComponentId::LOGIC_COMPONENT:
	{
		return CloneLogicComponent(object, reinterpret_cast<LogicComponent*>(component));
	}

	case ComponentId::TILEMAP_COMPONENT:
	{
		TileMapComponent* newComponent = dynamic_cast<TileMapComponent*>(component)->CloneComponent();
		newComponent->SetParentId(object->Get_uID());
		newComponent->SetParentPtr(object);
		MyComponentManger._TileMapComponents.insert(std::pair< size_t, TileMapComponent* >(object->Get_uID(), newComponent));

		return newComponent;
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
		delete MyComponentManger._transformComponents[object->Get_uID()];
		MyComponentManger._transformComponents.erase(object->Get_uID());
		break;
	}
	case ComponentId::GRAPHICS_COMPONENT:
	{
		delete MyComponentManger._graphicComponents[object->Get_uID()];
		MyComponentManger._graphicComponents.erase(object->Get_uID());

#ifdef LEVELEDITOR

		delete MyComponentManger._imGuizmoComponent[object->Get_uID()];
		MyComponentManger._imGuizmoComponent.erase(object->Get_uID());
#endif
		break;
	}
	case ComponentId::RIGIDBODY_COMPONENT:
	{
		delete MyComponentManger._rigidbody2DComponent[object->Get_uID()];
		MyComponentManger._rigidbody2DComponent.erase(object->Get_uID());
		break;
	}
	case ComponentId::CIRCLECOLLIDER_COMPONENT:
	{
		delete MyComponentManger._collider2dComponents[object->Get_uID()];
		MyComponentManger._collider2dComponents.erase(object->Get_uID());
		break;
	}
	case ComponentId::BOXCOLLIDER_COMPONENT:
	{
		delete MyComponentManger._collider2dComponents[object->Get_uID()];
		MyComponentManger._collider2dComponents.erase(object->Get_uID());
		break;
	}
	case ComponentId::EDGECOLLIDER_COMPONENT:
	{
		delete MyComponentManger._collider2dComponents[object->Get_uID()];
		MyComponentManger._collider2dComponents.erase(object->Get_uID());
		break;
	}
	case ComponentId::AUDIO_COMPONENT:
	{
		delete MyComponentManger._audioComponent[object->Get_uID()];
		MyComponentManger._audioComponent.erase(object->Get_uID());
		break;
	}
	case ComponentId::LOGIC_COMPONENT:
	{
		if (script == ScriptId::EMPTY)
		{
			for (auto it : MyComponentManger._logicComponents[object->Get_uID()]->GetScriptMap())
			{
				EngineSystems::GetInstance()._logicSystem->RemoveScript(MyComponentManger._logicComponents[object->Get_uID()], (ScriptId)it.first);
			}

			delete MyComponentManger._logicComponents[object->Get_uID()];
			MyComponentManger._logicComponents.erase(object->Get_uID());
			break;
		}

		EngineSystems::GetInstance()._logicSystem->RemoveScript(MyComponentManger._logicComponents[object->Get_uID()], script);
		break;
	}
	default:
		break;
	}

}

GameObject* GameObjectFactory::CloneGameObject(GameObject* object)	//Create a gameObject type along with its Components
{
	GameObject* newObject = CreateNewGameObject();
	//newObject->Set_typeId((TypeIdGO)object->Get_typeId());
	//Map_ComponentList& objectMap = newObject->GetComponentList();

	for (auto it : object->GetComponentList())
	{
		newObject->GetComponentList().insert(std::pair<ComponentId, IComponent*>(it.first, CloneComponent(newObject, it.second, (ComponentId)it.first)));
	}

	return newObject;
}

LogicComponent* GameObjectFactory::CloneLogicComponent(GameObject* object, LogicComponent* component)
{
	LogicComponent* newComponent = new LogicComponent();
	newComponent->SetParentId(object->Get_uID());
	newComponent->SetParentPtr(object);
	MyComponentManger._logicComponents.insert(std::pair< size_t, LogicComponent* >(object->Get_uID(), newComponent));

	Map_ScriptList& scriptMap = newComponent->GetScriptMap();

	for (auto it : component->GetScriptMap())
		scriptMap.insert(std::pair<unsigned, IScript*>(it.first, EngineSystems::GetInstance()._logicSystem->CloneScript(newComponent, it.second, (ScriptId)it.first))); ;

	return newComponent;
}


void GameObjectFactory::SerialiseLevel(std::string filePath)
{
	Serialiser Level(filePath);


	//Serialise BinaryMap - Used creating Static gameobjects on screen & collision data & AI node Map
	//Serialise Mobile GameObjects with components 
		//Player components

#ifndef LEVELEDITOR 
//Serialise Prototypes
	//EngineSystems::GetInstance()._prefabFactory->SerialPrefabObjects(Level);

	typedef std::map<std::string, std::string> NamePath;
	NamePath ResourceList;

	typedef std::unordered_map<std::string, std::string> unNamePath;
	unNamePath ResourceList1;

	if (Level.HasMember("PrototypesFilePaths"))
	{
		for (unsigned i = 0; i < Level["PrototypesFilePaths"].Size(); i++)	//Loop through the Serialisation Array
		{
			std::string filePath = Level["PrototypesFilePaths"][i].GetString();
			//size_t namesize = filePath.find_last_of(".png") - 4 - filePath.find_last_of("\\/");
			std::string fileName = filePath.substr(filePath.find_last_of("\\/") + 1);
			ResourceList1.insert(std::pair<std::string, std::string>(fileName, filePath));
		}
		EngineSystems::GetInstance()._prefabFactory->SerialiseAllPrefabAssets(ResourceList1);
		ResourceList1.clear();
	}


	//Serialise Resources
	if (Level.HasMember("TexturesFilesPaths"))
	{
		for (unsigned i = 0; i < Level["TexturesFilesPaths"].Size(); i++)	//Loop through the Serialisation Array
		{
			std::string filePath = Level["TexturesFilesPaths"][i].GetString();
			//size_t namesize = filePath.find_last_of(".png") - 4 - filePath.find_last_of("\\/");
			std::string fileName = filePath.substr(filePath.find_last_of("\\/") + 1);
			ResourceList.insert(std::pair<std::string, std::string>(fileName, filePath));
		}
		ResourceManager::GetInstance().AddTexture2DResourceList(ResourceList);
		ResourceList.clear();
	}
	if (Level.HasMember("AnimationDataFilesPaths"))
	{
		for (unsigned i = 0; i < Level["AnimationDataFilesPaths"].Size(); i++)	//Loop through the Serialisation Array
		{
			std::string filePath = Level["AnimationDataFilesPaths"][i].GetString();
			//size_t namesize = filePath.find_last_of(".json") - 5 - filePath.find_last_of("\\/");
			std::string fileName = filePath.substr(filePath.find_last_of("\\/") + 1);
			ResourceList.insert(std::pair<std::string, std::string>(fileName, filePath));
		}
		ResourceManager::GetInstance().AddAnimationResourceList(ResourceList);
		ResourceList.clear();
	}
	if (Level.HasMember("AudioFilesPaths"))
	{
		for (unsigned i = 0; i < Level["AudioFilesPaths"].Size(); i++)	//Loop through the Serialisation Array
		{
			std::string filePath = Level["AudioFilesPaths"][i].GetString();
			//size_t namesize = filePath.find_last_of(".ogg") - 4 - filePath.find_last_of("\\/");
			std::string fileName = filePath.substr(filePath.find_last_of("\\/") + 1);
			//std::cout << "FileName" << fileName << std::endl;
			ResourceList.insert(std::pair<std::string, std::string>(fileName, filePath));
		}
		ResourceManager::GetInstance().AddAudioResourceList(ResourceList);
		ResourceList.clear();
	}
	if (Level.HasMember("ShaderFilesPaths"))
	{
		for (unsigned i = 0; i < Level["ShaderFilesPaths"].Size(); i++)	//Loop through the Serialisation Array
		{
			std::string filePath = Level["ShaderFilesPaths"][i].GetString();
			std::string fileName = "";
			if (filePath.find(".vert") != std::string::npos)
			{
				//size_t namesize = filePath.find_last_of(".vert") - 5 - filePath.find_last_of("\\/");
				fileName = filePath.substr(filePath.find_last_of("\\/") + 1);
				ResourceList.insert(std::pair<std::string, std::string>(fileName, filePath));
			}
			else if (filePath.find(".frag") != std::string::npos)
			{
				//size_t namesize = filePath.find_last_of(".frag") - 5 - filePath.find_last_of("\\/");
				fileName = filePath.substr(filePath.find_last_of("\\/") + 1);
				ResourceList.insert(std::pair<std::string, std::string>(fileName, filePath));
			}
		}
		//ResourceManager::GetInstance().AddShaderResourceList(ResourceList);
		ResourceList.clear();
	}
	if (Level.HasMember("FontFilesPath"))
	{
		for (unsigned i = 0; i < Level["FontFilesPath"].Size(); i++)	//Loop through the Serialisation Array
		{
			std::string filePath = Level["FontFilesPath"][i].GetString();
			//size_t namesize = filePath.find_last_of(".ttf") - 4 - filePath.find_last_of("\\/");
			std::string fileName = filePath.substr(filePath.find_last_of("\\/") + 1);
			ResourceList.insert(std::pair<std::string, std::string>(fileName, filePath));
		}
		ResourceManager::GetInstance().AddFontResourceList(ResourceList);
		ResourceList.clear();
	}
#endif

	//Create and Serialise TileMaps
	if (Level.HasMember("AllTileMaps"))
	{
		for (rapidjson::SizeType i = 0; i < Level["AllTileMaps"].Size(); i++)
		{
			Serialiser tileMapInfo(Level["AllTileMaps"][i]);

			//rapidjson::Document tileMapDoc;
			//tileMapDoc.SetObject();
			//tileMapDoc.CopyFrom(Level["AllTileMaps"][i], tileMapDoc.GetAllocator());

			//rapidjson::StringBuffer buf;							//buffer -  to output from the Json Document	
			//rapidjson::Writer<rapidjson::StringBuffer> writer(buf);	//Writer handler - that contains the stringbuffer
			//tileMapDoc.Accept(writer);									//Output as json text into stringbuffer via Writer
			//std::string json(buf.GetString(), buf.GetSize());		//convert stringbuffer to std::string
			//std::ofstream file("./Resources/TextFiles/States/test.json"); //open a file with the param name
			//file << json;							//Write std::string type into the file

			GameObject* tileMap = CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()["TileMap"]);
			//TileMapComponent* tmCom = dynamic_cast<TileMapComponent*>(tileMap->GetComponent(ComponentId::TILEMAP_COMPONENT));
			//tmCom->SerialiseComponent(tileMapInfo);
			//TransformComponent* tfCom = dynamic_cast<TransformComponent*>(tileMap->GetComponent(ComponentId::TRANSFORM_COMPONENT));
			//tfCom->SerialiseComponent(tileMapInfo);
			tileMap->Serialise(tileMapInfo);
		}
	}

	//Create dynamic clonables
	if (Level.HasMember("ClonableObjects"))
	{
		for (unsigned i = 0; i < Level["ClonableObjects"].Size(); i++)
		{
			Serialiser datafile(Level["ClonableObjects"][i]);

			std::string name = datafile["Object"].GetString();
			GameObject* tmp2 = EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[name];
			GameObject* tmp = CloneGameObject(tmp2);

			tmp->Serialise(datafile);
		}
	}

	//Create dynamic non-clonables
	//if (Level.HasMember("NonClonableObjects"))
	//{
	//	for (unsigned i = 0; i < Level["NonClonableObjects"].Size(); i++)
	//	{
	//		Serialiser datafile(Level["NonClonableObjects"][i]);
	//
	//		tmp->Serialise(datafile);
	//	}
	//}

}


//For Level Editor Only
void GameObjectFactory::De_SerialiseLevel(std::string filePath)
{

	//1. Deserialise the Resources first
		//Deserialise Prototypes Resource 
			//- Check through the Identity Components of all Objects
			//- The ObjectType in the IdentityComponent will be used to save a Prototype
			//= Get the Prototype file Path from the PrototypeList 
		//Deserialise Texture Resource
			//- Check through all the graphic Component for the texture File Name
			//- Get the File path of the textures from the Resource Manager
		//Deserialise AnimationDataFile
			//- Check through all the animation components for the animationdatafile names
			//- Get file Path of the animationDataFile from the Resource Manager
		//Deserialise AudioFiles
			//- Check throught the AudioComponents to get audio file name
			//- Get the File path of the audiofile from the Resource Manager
		//Deserialise ShaderTypes
			//- check through the Graphic Component for the Shader Name used
			//- Get File Path of both the vertex and fragment Shader Used
		//Deserialise Font Used
			//- Check throught the Font Component for the font type used
			//- Get the File path of the Fontfile from the Resource Manager

	//2. Deserialise GameObjects in Scene //Clonable Game Objects & Non-Clonable Game Objects
				//If Prototype list cannot find the Object, then save GameObject as NonClonableObjects array and save every single component data of the object as well
				//else If Prototype list can find the Object, save objecttype under ClonableObjects array 
					//Search through the Component list of the Clonable Object and compare with the prototype
						//Check if the prototype has the component that the clonable object has. 
							//If prototype has the component, then check if the component data is the same as the Object.
								//If component data is same then, do not need to list the component in the scene file.
								//else if there is a component data that is different, list the component name and the data in the component in the scene file
							//else If prototype does not have the component, then save every single data in the specific component into the scene file


	DeSerialiser SceneFile(filePath);

	//Deserialise Prototypes Resource 
	//- Check through the Identity Components of all Objects
	//- The ObjectType in the IdentityComponent will be used to save a Prototype
	//= Get the Prototype file Path from the PrototypeList 

	std::vector<std::string> PrototypeResourcePathList;
	rapidjson::Value PrototypesFilePaths;
	PrototypesFilePaths.SetArray();

	for (auto& IdComPair : MyComponentManger._IdentityComponents)
	{
		if (IdComPair.first < 1000)
		{
			continue;
		}

		std::string ObjType = IdComPair.second->ObjectType();

		//Object exists in PrototypeAssetList - Save in ClonableObjects list
		if (MyPrototypeFactory.GetPrototypeObj(ObjType))
		{
			// PrototypeResourceList does not have the prototype yet
			if ((std::find(PrototypeResourcePathList.begin(), PrototypeResourcePathList.end(), ObjType) == PrototypeResourcePathList.end()))
			{
				std::string FilePath = MyPrototypeFactory.GetPrototypeFile(ObjType);
				PrototypeResourcePathList.push_back(FilePath);
			}

		}
	}

	for (auto& prototypeName : PrototypeResourcePathList)
	{
		PrototypesFilePaths.PushBack(rapidjson::StringRef(prototypeName.c_str()), SceneFile.Allocator());
	}
	//After Going thru the GameObjects list, the PrototypesFilePaths list is finalised 
	SceneFile.AddMember("PrototypesFilePaths", PrototypesFilePaths);



	//Deserialise ShaderTypes
	//- check through the Graphic Component for the Shader Name used
	//- Get File Path of both the vertex and fragment Shader Used

	//Deserialise Texture Resource
	//- Check through all the graphic Component for the texture File Name
	//- Get the File path of the textures from the Resource Manager

	std::vector<std::string> TextureResourcePathList;
	rapidjson::Value TextureFilePaths;
	TextureFilePaths.SetArray();

	std::vector<std::string> ShaderResourcePathList;
	rapidjson::Value ShaderFilePaths;
	ShaderFilePaths.SetArray();

	for (auto& IdGrapPair : MyComponentManger._graphicComponents)
	{
		if (IdGrapPair.first < 1000)
		{
			continue;
		}

		std::string TextureFile = IdGrapPair.second->GetFileName();

		if (MyResourceManager.GetTexture2DResource(TextureFile))
		{
			if ((std::find(TextureResourcePathList.begin(), TextureResourcePathList.end(), TextureFile) == TextureResourcePathList.end()))
			{
				std::string FilePath = MyResourceManager.GetTexture2DResourcePath(TextureFile);
				TextureResourcePathList.push_back(FilePath);
			}
		}

		std::string ShaderFile = IdGrapPair.second->GetShaderType();

		if (MyResourceManager.GetShaderResource(ShaderFile))
		{
			if ((std::find(ShaderResourcePathList.begin(), ShaderResourcePathList.end(), ShaderFile) == ShaderResourcePathList.end()))
			{
				ResourceManager::VertFrag vertfrag= MyResourceManager.GetShaderResourcePath(TextureFile);
				ShaderResourcePathList.push_back(vertfrag.first);
				ShaderResourcePathList.push_back(vertfrag.second);
			}
		}
	}

	for (auto& TextureName : TextureResourcePathList)
	{
		TextureFilePaths.PushBack(rapidjson::StringRef(TextureName.c_str()), SceneFile.Allocator());
	}
	SceneFile.AddMember("TexturesFilesPaths", TextureFilePaths);

	for (auto& ShaderName : ShaderResourcePathList)
	{
		ShaderFilePaths.PushBack(rapidjson::StringRef(ShaderName.c_str()), SceneFile.Allocator());
	}
	SceneFile.AddMember("ShaderFilesPaths", ShaderFilePaths);



	//Deserialise AnimationDataFile
	//- Check through all the animation components for the animationdatafile names
	//- Get file Path of the animationDataFile from the Resource Manager

	std::vector<std::string> AnimationResourcePathList;
	rapidjson::Value AnimationFilePaths;
	AnimationFilePaths.SetArray();

	for (auto& IdAnimPair : MyComponentManger._AnimationComponents)
	{
		if (IdAnimPair.first < 1000)
		{
			continue;
		}

		const std::vector<std::string>& AnimFileList = IdAnimPair.second->GetAnimationDataFileList();

		for (auto& animFile : AnimFileList)
		{
			if (MyResourceManager.GetAnimationResource(animFile))
			{
				if ((std::find(AnimationResourcePathList.begin(), AnimationResourcePathList.end(), animFile) == AnimationResourcePathList.end()))
				{
					std::string FilePath = MyResourceManager.GetAnimationResourcePath(animFile);
					AnimationResourcePathList.push_back(FilePath);
				}
			}
		}
	}

	for (auto& AnimName : AnimationResourcePathList)
	{
		AnimationFilePaths.PushBack(rapidjson::StringRef(AnimName.c_str()), SceneFile.Allocator());
	}
	SceneFile.AddMember("AnimationDataFilesPaths", AnimationFilePaths);



	//Deserialise AudioFiles
	//- Check throught the AudioComponents to get audio file name
	//- Get the File path of the audiofile from the Resource Manager
	std::vector<std::string> AudioResourcePathList;
	rapidjson::Value AudioFilePaths;
	AudioFilePaths.SetArray();

	for (auto& IdAudioPair : MyComponentManger._audioComponent)
	{
		if (IdAudioPair.first < 1000)
		{
			continue;
		}

		std::string audioFile = IdAudioPair.second->GetFileName();


		if (MyResourceManager.GetSoundResource(audioFile))
		{
			// PrototypeResourceList does not have the prototype yet
			if ((std::find(AudioResourcePathList.begin(), AudioResourcePathList.end(), audioFile) == AudioResourcePathList.end()))
			{
				std::string FilePath = MyResourceManager.GetSoundResourcePath(audioFile);
				AudioResourcePathList.push_back(FilePath);
			}
		}
	}

	for (auto& AudioName : AudioResourcePathList)
	{
		AudioFilePaths.PushBack(rapidjson::StringRef(AudioName.c_str()), SceneFile.Allocator());
	}
	SceneFile.AddMember("AudioFilesPaths", AudioFilePaths);



	//Deserialise Font Used
	//- Check throught the Font Component for the font type used
	//- Get the File path of the Fontfile from the Resource Manager
	std::vector<std::string> FontResourcePathList;
	rapidjson::Value FontFilePaths;
	FontFilePaths.SetArray();

	for (auto& IdFontPair : MyComponentManger._FontComponent)
	{
		if (IdFontPair.first < 1000)
		{
			continue;
		}

		std::string fontFile = IdFontPair.second->GetFontType();

		if (MyResourceManager.GetFontResource(fontFile))
		{
			// PrototypeResourceList does not have the prototype yet
			if ((std::find(FontResourcePathList.begin(), FontResourcePathList.end(), fontFile) == FontResourcePathList.end()))
			{
				std::string FilePath = MyResourceManager.GetFontResourcePath(fontFile);
				FontResourcePathList.push_back(FilePath);
			}
		}
	}

	for (auto& FontName : FontResourcePathList)
	{
		FontFilePaths.PushBack(rapidjson::StringRef(FontName.c_str()), SceneFile.Allocator());
	}
	SceneFile.AddMember("FontFilesPath", FontFilePaths);



	rapidjson::Value clonableObjects;
	clonableObjects.SetArray();

	rapidjson::Value nonClonableObjects;
	nonClonableObjects.SetArray();

	for (auto& IdIdcomPair : MyComponentManger._IdentityComponents)
	{
		const size_t id = IdIdcomPair.first;
		if (id < 1000)
		{
			continue;
		}

		std::string ObjType = IdIdcomPair.second->ObjectType();

		DeSerialiser obj;
		GameObject* proObj = nullptr;
		//Object exists in PrototypeAssetList - Save in ClonableObjects list
		if (proObj = MyPrototypeFactory.GetPrototypeObj(ObjType))
		{
			std::unordered_map <ComponentId, IComponent* >& comList = _listObject[id]->GetComponentList();

			for (auto& IdComPair : comList)
			{
				IComponent* protoCom = proObj->GetComponent(IdComPair.first);
				IdComPair.second->DeserialiseComponentSceneFile(protoCom, obj);
			}

			clonableObjects.PushBack(obj.GetDocument(), SceneFile.Allocator());

		}
		else  //Object does not exists in PrototypeAssetList - Save in NonClonableObjects list
		{
			std::unordered_map <ComponentId, IComponent* >& comList = _listObject[id]->GetComponentList();

			for (auto& IdComPair : comList)
			{
				IComponent* protoCom = proObj->GetComponent(IdComPair.first);
				IdComPair.second->DeSerialiseComponent(obj);
			}

			nonClonableObjects.PushBack(obj.GetDocument(), SceneFile.Allocator());

		}
	}

}


void GameObjectFactory::DeleteLevel()
{
	EngineSystems::GetInstance()._prefabFactory->GetPrototypeList().clear();

#ifdef LEVELEDITOR
	EngineSystems::GetInstance()._imGuizmoManager->_pickList.clear();
#endif

	for (auto it : _listObject)
		delete it.second;
	_listObject.clear();

	for (auto it : MyComponentManger._IdentityComponents)
		delete it.second;
	MyComponentManger._IdentityComponents.clear();

	for (auto it : MyComponentManger._graphicComponents)
		delete it.second;
	MyComponentManger._graphicComponents.clear();

	for (auto it : MyComponentManger._transformComponents)
		delete it.second;
	MyComponentManger._transformComponents.clear();

	for (auto it : MyComponentManger._AnimationComponents)
		delete it.second;
	MyComponentManger._AnimationComponents.clear();

	for (auto it : MyComponentManger._CameraComponents)
		delete it.second;
	MyComponentManger._CameraComponents.clear();

	for (auto it : MyComponentManger._rigidbody2DComponent)
		delete it.second;
	MyComponentManger._rigidbody2DComponent.clear();

	for (auto it : MyComponentManger._collider2dComponents)
		delete it.second;
	MyComponentManger._collider2dComponents.clear();

	for (auto it : MyComponentManger._logicComponents)
		delete it.second;
	MyComponentManger._logicComponents.clear();

	EngineSystems::GetInstance()._logicSystem->DeleteLevelScripts();

	for (auto it : MyComponentManger._imGuizmoComponent)
		delete it.second;
	MyComponentManger._imGuizmoComponent.clear();

	for (auto it : MyComponentManger._audioComponent)
		delete it.second;
	MyComponentManger._audioComponent.clear();

	for (auto it : MyComponentManger._FontComponent)
		delete it.second;
	MyComponentManger._FontComponent.clear();

	for (auto it : MyComponentManger._buttonComponent)
		delete it.second;
	MyComponentManger._buttonComponent.clear();
}

void GameObjectFactory::DeleteLevelNotPrefab()
{
	for (auto it : _listObject)
		if (it.first >= 1000)
			it.second->SetDestory();
}

std::unordered_map < size_t, GameObject*>& GameObjectFactory::getObjectlist()
{
	return _listObject;
}




//Read LevelText and Instantiate GObj - When Next Game State is In-Game, Create all level objects
//void GameObjectFactory::SerialiseLevel(const char* FileName)
//{ // will move to ObjectFactory
//	std::cout << "FileRead_Level( " << FileName << " )" << std::endl;
//	std::fstream _file;
//	_file.open(FileName, std::ios_base::in | std::ios_base::binary);
//	if (!_file.is_open())
//	{
//		std::cout << "! WARNING !! File Cannot Open!!!" << std::endl
//			<< FileName << std::endl;
//		return;
//	}
//	char* strType = new char[20]; // for Type
//	// for any input (max inputs)
//	char* strNum1 = new char[10];
//	char* strNum2 = new char[10];
//	float num1, num2;
//	GameObject* tempGO = nullptr;
//	IComponent* tempComp = nullptr;
//
//	while (_file.good()) // each loop read 4 lines: Type, Pos, Scale, Rot
//	{
//	// Get Type
//		//_file.getline(strType, 20, '\n\r');
//		_file >> strType;
//		if (std::strcmp(strType, "Player") == 0)
//			tempGO = CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::PLAYER]);
//		else if (std::strcmp(strType, "Enemy") == 0)
//			tempGO = CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::ENEMY]);
//		else if (std::strcmp(strType, "Wall") == 0)
//			tempGO = CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::WALL]);
//		else if (std::strcmp(strType, "Camera") == 0)
//			tempGO = CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::CAMERA]);
//		else if (std::strcmp(strType, "Button") == 0)
//			tempGO = CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[TypeIdGO::BUTTON_UI]);
//		else
//			ASSERT("Serialise-File Attempted to create UNKNOWN GO" && false);
//	// TransformComponent from 'temp'
//		tempComp = tempGO->GetComponentList()[(unsigned)ComponentId::TRANSFORM_COMPONENT];
//
//	// get Position
//		ASSERT(_file.getline(strNum1, 10, ','));
//		ASSERT(_file.getline(strNum2, 10));
//		num1 = std::stof(strNum1);
//		num2 = std::stof(strNum2);
//		((TransformComponent*)tempComp)->GetPos() = Vector3(num1, num2, 1);
//	// get Scale
//		ASSERT(_file.getline(strNum1, 10, ','));
//		ASSERT(_file.getline(strNum2, 10));
//		num1 = std::stof(strNum1);
//		num2 = std::stof(strNum2);
//		((TransformComponent*)tempComp)->GetScale() = Vector3(num1, num2, 1);
//
//	// get Rotate
//		ASSERT(_file.getline(strNum1, 10));
//		num1 = std::stof(strNum1);
//		((TransformComponent*)tempComp)->GetRotate() = num1;
//	}
//
//
//	_file.close();
//	delete[] strType;
//	delete[] strNum1;
//	delete[] strNum2;
//	return;
//}
