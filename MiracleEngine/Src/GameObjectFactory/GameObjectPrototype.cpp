#include "PrecompiledHeaders.h"
#include "GameObjectPrototype.h"



GameObjectPrototype::GameObjectPrototype()
{
	GameObject* temp = nullptr;

	// Prototype_Player
	temp = new GameObject(0, (unsigned)TypeIdGO::PLAYER);
	temp->SerialInPrefab_Player();
	_listObjectPrototype.insert(std::pair < TypeIdGO, GameObject*>(TypeIdGO::PLAYER, temp)); //Insert Object into Prototype List

	// Prototype_Enemy
	temp = new GameObject(0, (unsigned)TypeIdGO::ENEMY);
	temp->SerialInPrefab_Enemy();
	_listObjectPrototype.insert(std::pair < TypeIdGO, GameObject*>(TypeIdGO::ENEMY, temp));

	// Prototype_Wall
	temp = new GameObject(0, (unsigned)TypeIdGO::WALL);
	temp->SerialInPrefab_Wall();
	_listObjectPrototype.insert(std::pair < TypeIdGO, GameObject*>(TypeIdGO::WALL, temp));
}


GameObjectPrototype::~GameObjectPrototype()
{
	for (auto& gameObject : _listObjectPrototype)
		delete gameObject.second;
	_listObjectPrototype.clear();
}

// Get _listObjectProrotype
std::unordered_map<TypeIdGO, GameObject*>& GameObjectPrototype::GetPrototypeList()
{
	return _listObjectPrototype;
}


GameObject* GameObjectPrototype::PrefabGameObject(TypeIdGO typeId)	 //Create a gameObject type along with its Components
{
	size_t uId = 0;
	GameObject* gameObject = nullptr;

	switch (typeId)
	{
	case TypeIdGO::PLAYER:
		gameObject = new GameObject(uId, (unsigned)TypeIdGO::PLAYER);
		gameObject->SerialInPrefab_Player();
		break;
	case TypeIdGO::WALL:
		gameObject = new GameObject(uId, (unsigned)TypeIdGO::WALL);
		gameObject->SerialInPrefab_Wall();
		break;
		//Other Objects
	}
	return gameObject;
}



