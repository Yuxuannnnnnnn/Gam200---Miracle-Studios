#pragma once





class GameObjectPrototype final
{
	std::unordered_map<TypeIdGO, GameObject*> _listObjectPrototype;		//Dynamic array of GameObject Prototypes

public:
	GameObjectPrototype(const GameObjectPrototype& rhs) = delete;
	GameObjectPrototype& operator=(const GameObjectPrototype& rhs) = delete;


	GameObjectPrototype();
	~GameObjectPrototype();	//Destructed when GameStateQuit

	std::unordered_map<TypeIdGO, GameObject*>& GetPrototypeList();	// Get _listObjectProrotype

	GameObject* PrefabGameObject(TypeIdGO typeId);	// Create a gameObject type along with its Components



};
