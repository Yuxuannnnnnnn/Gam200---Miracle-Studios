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
	GameObject* temp = EngineSystems::GetInstance()._gameObjectFactory->CreateNewGameObject(true);
	temp->Set_typeId(type);

	switch (type)
	{
	case TypeIdGO::NONE:
		break;
	case TypeIdGO::WALL:
		temp->Serialise("./Resources/TextFiles/GameObjects/Wall.json");
		break;
	case TypeIdGO::FLOOR:
		break;
	case TypeIdGO::OBSTACLE:
		break;
	case TypeIdGO::PLAYER:
		temp->Serialise("./Resources/TextFiles/GameObjects/Player.json");
		break;
	case TypeIdGO::ENEMY:
		temp->Serialise("./Resources/TextFiles/GameObjects/Enemy.json");
		break;
	case TypeIdGO::BULLET:
		temp->Serialise("./Resources/TextFiles/GameObjects/Bullet.json");
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
		delete temp;
		break;
	}

	_listObjectPrototype.insert(std::pair <TypeIdGO, GameObject*>(type, temp));

	return temp;
}





