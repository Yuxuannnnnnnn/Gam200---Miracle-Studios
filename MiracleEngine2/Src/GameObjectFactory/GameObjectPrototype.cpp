#include "PrecompiledHeaders.h"
#include "GameObjectPrototype.h"
#include "Engine/EngineSystems.h"


GameObjectPrototype::GameObjectPrototype()
{
	SerialPrefabObject(TypeIdGO::PLAYER);
}


GameObjectPrototype::~GameObjectPrototype()
{
	_listObjectPrototype.clear();
}

// Get _listObjectProrotype
std::unordered_map<TypeIdGO, GameObject*>& GameObjectPrototype::GetPrototypeList()
{
	return _listObjectPrototype;
}

GameObject* GameObjectPrototype::SerialPrefabObject(TypeIdGO type)
{
	GameObject* temp = nullptr;

	switch (type)
	{
	case TypeIdGO::NONE:
		break;
	case TypeIdGO::WALL:
		break;
	case TypeIdGO::FLOOR:
		break;
	case TypeIdGO::OBSTACLE:
		break;
	case TypeIdGO::PLAYER:
		temp = SerialInPrefab_Player();
		break;
	case TypeIdGO::ENEMY:
		break;
	case TypeIdGO::BULLET:
		break;
	case TypeIdGO::WEAPON:
		break;
	case TypeIdGO::PISTOL:
		break;
	case TypeIdGO::SHOTGUN:
		break;
	case TypeIdGO::SNIPER:
		break;
	case TypeIdGO::RPG:
		break;
	default:
		break;
	}

	_listObjectPrototype.insert(std::pair <TypeIdGO, GameObject*>(type, temp));

	return temp;
}

// AddComponent for during Serialisation
void GameObjectPrototype::SerialAddComponent(GameObject* object, SerialTypeId componentType, rapidjson::Value& s, rapidjson::Document& d)
{
	IComponentSystem* temp;

	switch (componentType)
	{
	case SerialTypeId::TRANSFORM_DATA:
	{
		temp = object->AddComponent(ComponentId::TRANSFORM_COMPONENT);
		s = d["Position"];												
		JsonDynamicStore(((TransformComponent*)temp)->GetPos(), s);
		s = d["Scale"];
		JsonDynamicStore(((TransformComponent*)temp)->GetScale(), s);
		s = d["Rotate"];
		JsonDynamicStore(((TransformComponent*)temp)->GetRotate(), s);
		break;
	}
	case SerialTypeId::GRAPHICS_DATA:
	{
		temp = object->AddComponent(ComponentId::GRAPHICS_COMPONENT);
		s = d["G.TypeId"];
		JsonDynamicStore(((GraphicComponent*)temp)->GetTypeId(), s);
		s = d["G.FileName"];
		JsonDynamicStore(((GraphicComponent*)temp)->GetFileName(), s);
		break;
	}
	case SerialTypeId::RIGIDBODY_DATA:
	{
		temp = object->AddComponent(ComponentId::RIGIDBODY_COMPONENT);
		s = d["Mass"];
		JsonDynamicStore(((RigidBody2D*)temp)->_mass, s);
		s = d["Friction"];
		JsonDynamicStore(((RigidBody2D*)temp)->_fictionVal, s);
		s = d["Static"];
		JsonDynamicStore(((RigidBody2D*)temp)->_static, s);
		break;
	}
	case SerialTypeId::COLLIDER_DATA:
	{
		unsigned type;

		s = d["ColliderTypeId"];
		JsonDynamicStore(type, s);

		if (type == (int)ColliderType::BOX_COLLIDER)
		{
			temp = object->AddComponent(ComponentId::RIGIDBODY_COMPONENT);
		}
		else if (type == (int)ColliderType::CIRCLE_COLLIDER)
		{
			temp = object->AddComponent(ComponentId::RIGIDBODY_COMPONENT);
		}
		else if (type == (int)ColliderType::LINE_COLLIDER)
		{
			temp = object->AddComponent(ComponentId::RIGIDBODY_COMPONENT);
		}
		break;
	}
	case SerialTypeId::AUDIO_DATA:
	{
		break;
	}
	case SerialTypeId::LOGIC_DATA:
	{
		std::vector<int> types;
		s = d["ScriptId"];
		JsonDynamicStore(types, s);

		if (types[0] == (int)ScriptId::PLAYER)
		{
			temp = object->AddComponent(ComponentId::LOGIC_COMPONENT, ScriptId::PLAYER);
		}
		break;
	}
	default:
		break;
	}
}

GameObject* GameObjectPrototype::SerialInPrefab_Player()
{
	GameObject* object = EngineSystems::GetInstance()._gameObjectFactory->CreateNewGameObject(true);
	object->Set_typeId(TypeIdGO::PLAYER);

	rapidjson::Document d;
	char* iBuffer = FileRead_FileToCharPtr("./Resources/TextFiles/GameObjects/Player.json"); //Read in whole file as char pointer
	ASSERT(iBuffer != nullptr);			//std::cout << iBuffer << std::endl; //Show buffer, use to check
	d.Parse<rapidjson::kParseStopWhenDoneFlag>(iBuffer);					 //Read whole file in RapidJson format

// Component List
	rapidjson::Value& s = d["ComponentList"];			//Get Numberlist of Component Data in RapidJson Format	
	std::vector<int> compList;
	JsonDynamicStore(compList, s);						//Convert Numberlist of Component Data to stl dynamic list format
	std::vector<int>::iterator itr = compList.begin();
	while (itr != compList.end())
		SerialAddComponent(object, (SerialTypeId)* itr++, s, d);

	// Other Values
			//s = d["Weapons"];
			//JsonDynamicStore(_WeaponListId, s);
			// ConvertWeaponIdToWeapon(); // MAY BE CAUSING MEM LEAK
	std::cout << "-------------------------------------" << std::endl;
	delete[] iBuffer;
	//Serialisation Check
		//PrintStats_Player();

	return object;
}



