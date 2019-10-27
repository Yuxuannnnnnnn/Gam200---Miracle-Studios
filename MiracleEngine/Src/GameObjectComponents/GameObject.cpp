#include "PrecompiledHeaders.h"
#include "GameObject.h"


GameObject::GameObject(size_t uId, unsigned typeId)
	:_uId{ uId }, _typeId{ typeId }
{
	//std::cout << "GameObject::GameObject()" << std::endl;
}

GameObject::~GameObject()
{
	//std::cout << "GameObject::~GameObject()" << std::endl;

	//std::unordered_map< TypeIdComponent, IComponentSystem* >::iterator iterator = _ComponentList.begin();
	//while (iterator != _ComponentList.end())
	//{
	//	delete iterator->second;
	//	iterator++;
	//}


	for (auto component : _ComponentList)
	{
		delete component.second;
	}
}


unsigned GameObject::GameObjectType() const
{
	return _typeId;
}

// DEPRECIATED - Add a specific component to the GameObject
IComponentSystem* GameObject::addcomponent(TypeIdComponent componentType)
{
	switch (componentType)
	{
	case TypeIdComponent::TRANSFORMCOMPONENT:
		_ComponentList[TypeIdComponent::TRANSFORMCOMPONENT] = new TransformComponent();
		break;
	case TypeIdComponent::GRAPHICSCOMPONENT:
		_ComponentList[TypeIdComponent::GRAPHICSCOMPONENT] = new GraphicComponent();
		break;
	case TypeIdComponent::RIGIDBODYCOMPONENT:
		_ComponentList[TypeIdComponent::RIGIDBODYCOMPONENT] = new RigidBody2D();
		break;
	case TypeIdComponent::COLLIDERCOMPONENT:
		_ComponentList[TypeIdComponent::COLLIDERCOMPONENT] = new Collider2D();
		break;
	case TypeIdComponent::LOGICCOMPONENT:
		_ComponentList[TypeIdComponent::LOGICCOMPONENT] = new LogicComponent();
		break;

	}

	return  _ComponentList[componentType];
}


// AddComponent for during Serialisation
void GameObject::SerialAddComponent
	(TypeIdComponent componentType, rapidjson::Value& s, rapidjson::Document& d)
{
	std::cout << "- GameObject::SerialAddComponent(" << (unsigned)componentType << ") : ";

	switch (componentType)
	{
		IComponentSystem* temp;

	case TypeIdComponent::TRANSFORMCOMPONENT:	std::cout << "Transform";	

		_ComponentList[TypeIdComponent::TRANSFORMCOMPONENT] = new TransformComponent(); 	// create new component
		temp = _ComponentList[TypeIdComponent::TRANSFORMCOMPONENT];		// 'temp' to access new component
		s = d["Position"];												// store values needed
		JsonDynamicStore(((TransformComponent*)temp)->GetPos(), s);
		s = d["Scale"];
		JsonDynamicStore(((TransformComponent*)temp)->GetScale(), s);
		s = d["Rotate"];
		JsonDynamicStore(((TransformComponent*)temp)->GetRotate(), s);
		break;

	case TypeIdComponent::GRAPHICSCOMPONENT:	std::cout << "Graphics";

		_ComponentList[TypeIdComponent::GRAPHICSCOMPONENT] = new GraphicComponent();
		temp = _ComponentList[TypeIdComponent::GRAPHICSCOMPONENT];
		s = d["G.TypeId"];
		JsonDynamicStore(((GraphicComponent*)temp)->GetTypeId(), s);
		s = d["G.FileName"];
		JsonDynamicStore(((GraphicComponent*)temp)->GetFileName(), s);
		break;

	case TypeIdComponent::RIGIDBODYCOMPONENT:	std::cout << "R. Body";

		_ComponentList[TypeIdComponent::RIGIDBODYCOMPONENT] = new RigidBody2D();
		temp = _ComponentList[TypeIdComponent::RIGIDBODYCOMPONENT];
		s = d["Mass"];
		JsonDynamicStore(((RigidBody2D*)temp)->_mass, s);
		s = d["Friction"];
		JsonDynamicStore(((RigidBody2D*)temp)->_fictionVal, s);
		s = d["Static"];
		JsonDynamicStore(((RigidBody2D*)temp)->_static, s);
		break;

	case TypeIdComponent::COLLIDERCOMPONENT:	std::cout << "Collider";

		_ComponentList[TypeIdComponent::COLLIDERCOMPONENT] = new Collider2D();
		temp = _ComponentList[TypeIdComponent::COLLIDERCOMPONENT];
		s = d["ColliderTypeId"];
		JsonDynamicStore(((Collider2D*)temp)->_type, s);
		break;

	case TypeIdComponent::LOGICCOMPONENT:		std::cout << "Logic";

		_ComponentList[TypeIdComponent::LOGICCOMPONENT] = new LogicComponent();
		temp = _ComponentList[TypeIdComponent::LOGICCOMPONENT];
		s = d["ScriptId"];
		JsonDynamicStore(((LogicComponent*)temp)->GetScriptId(), s);
		s = d["Health"];
		JsonDynamicStore(((LogicComponent*)temp)->GetHealth(), s);
		s = d["Speed"];
		JsonDynamicStore(((LogicComponent*)temp)->GetSpeed(), s);
		break;

	case TypeIdComponent::AUDIOCOMPONENT:		std::cout << "Audio";

		_ComponentList[TypeIdComponent::AUDIOCOMPONENT] = new AudioComponent();
		temp = _ComponentList[TypeIdComponent::AUDIOCOMPONENT];
		s = d["A.TypeId"];
		JsonDynamicStore(((AudioComponent*)temp)->GetTypeId(), s);
		s = d["A.FileName"];
		JsonDynamicStore(((AudioComponent*)temp)->GetFileName(), s);
		break;

	default:
		temp = nullptr;
		break;
	}
	std::cout << std::endl;
}


void GameObject::CopyComponent	// Copy all components from 'original'(Prototype/Prefab/whateverYouCallIt)
	(std::unordered_map< TypeIdComponent, IComponentSystem* >& original) 
{
	std::cout << "\t GameObject::CopyComponent() : ";

	std::unordered_map< TypeIdComponent, IComponentSystem* >::iterator itr = original.begin();

	while (itr != original.end())
	{
		IComponentSystem* temp;
		switch (itr->first)
		{
		case TypeIdComponent::TRANSFORMCOMPONENT:	std::cout << "Transform, ";

			temp = new TransformComponent(
				*((TransformComponent*)itr->second)
			); // using copyCtor to copy var, idk if it works
			_ComponentList[TypeIdComponent::TRANSFORMCOMPONENT] =  temp;
			break;

		case TypeIdComponent::GRAPHICSCOMPONENT:	std::cout << "Graphics, ";

			temp = new GraphicComponent(
				*((GraphicComponent*)itr->second)
			);
			_ComponentList[TypeIdComponent::GRAPHICSCOMPONENT] = temp;
			break;

		case TypeIdComponent::RIGIDBODYCOMPONENT:	std::cout << "R. Body, ";

			temp = new RigidBodyComponent(
				*((RigidBodyComponent*)itr->second)
			);
			_ComponentList[TypeIdComponent::RIGIDBODYCOMPONENT] = temp;
			break;

		case TypeIdComponent::COLLIDERCOMPONENT:	std::cout << "Collider, ";

			temp = new Collider2D(
				*((Collider2D*)itr->second)
			);
			_ComponentList[TypeIdComponent::COLLIDERCOMPONENT] = temp;
			break;

		case TypeIdComponent::LOGICCOMPONENT:		std::cout << "Logic, ";

			temp = new LogicComponent(
				*((LogicComponent*)itr->second)
			);
			_ComponentList[TypeIdComponent::LOGICCOMPONENT] = temp;
			break;

		case TypeIdComponent::AUDIOCOMPONENT:		std::cout << "Audio, ";

			temp = new AudioComponent(
				*((AudioComponent*)itr->second)
			);
			_ComponentList[TypeIdComponent::AUDIOCOMPONENT] = temp;
			break;

		default:
			temp = nullptr;
			break;
		}
		++itr;
	}
	std::cout << std::endl;
}

// Cloning GO
GameObject* GameObject::Clone()
{
	//std::cout << "GameObject::Clone()" << std::endl;
	GameObject* temp = new GameObject(_uId, _typeId);
	// copy _ComponentList;
	temp->CopyComponent(_ComponentList);
	// return GO so that can put into GOFac's _listObj
	return temp;
}

void GameObject::SerialInPrefab_Player()
{
// Get & Parse File
	std::cout
		<< std::endl
		<< "-------------------------------------" << std::endl
		<< "FileRead_PlayerInfo -----------------" << std::endl;
	rapidjson::Document d;
	char* iBuffer = FileRead_FileToCharPtr("./Resources/TextFiles/Player.json");
	ASSERT(iBuffer != nullptr);
		//std::cout << iBuffer << std::endl; // show buffer, use to check
	d.Parse<rapidjson::kParseStopWhenDoneFlag>(iBuffer);
// Component List
	rapidjson::Value& s = d["ComponentList"];
	std::vector<int> compList;
	JsonDynamicStore(compList, s);
	std::vector<int>::iterator itr = compList.begin();
	while (itr != compList.end())
		SerialAddComponent((TypeIdComponent)* itr++, s, d);
// Other Values
		//s = d["Weapons"];
		//JsonDynamicStore(_WeaponListId, s);
		// ConvertWeaponIdToWeapon(); // MAY BE CAUSING MEM LEAK
	std::cout << "-------------------------------------" << std::endl;
	delete[] iBuffer;
//Serialisation Check
	PrintStats_Player();
}
void GameObject::PrintStats_Player() {
	IComponentSystem* temp = nullptr;
	std::string a;
	temp = _ComponentList[TypeIdComponent::TRANSFORMCOMPONENT];
	std::cout
		<< "FilePrint_PlayerInfo ----------------" << std::endl
		<< "- Trans.Pos         : " << ((TransformComponent*)temp)->GetPos() << std::endl
		<< "- Trans.Sca         : " << ((TransformComponent*)temp)->GetScale() << std::endl
		<< "- Trans.Rot         : " << ((TransformComponent*)temp)->GetRotate() << std::endl;
	temp = _ComponentList[TypeIdComponent::GRAPHICSCOMPONENT];
	std::cout
		<< "- Graphics.typeId   : " << ((GraphicComponent*)temp)->GetTypeId() << std::endl
		<< "- Graphics.filename : " << ((GraphicComponent*)temp)->GetFileName() << std::endl;
	temp = _ComponentList[TypeIdComponent::RIGIDBODYCOMPONENT];
	std::cout
		<< "- RBod.Mass         : " << ((RigidBody2D*)temp)->_mass << std::endl
		<< "- RBod.Friction     : " << ((RigidBody2D*)temp)->_fictionVal << std::endl
		<< "- RBod.Static       : " << ((RigidBody2D*)temp)->_static << std::endl;
	temp = _ComponentList[TypeIdComponent::COLLIDERCOMPONENT];
	std::cout
		<< "- Collider.TypId    : " << ((Collider2D*)temp)->_type << std::endl;
	temp = _ComponentList[TypeIdComponent::LOGICCOMPONENT];
	std::cout
		<< "- Logic.Health      : " << ((LogicComponent*)temp)->GetHealth() << std::endl
		<< "- Logic.Speed       : " << ((LogicComponent*)temp)->GetSpeed() << std::endl
		<< "- Logic.Lifetime    : " << ((LogicComponent*)temp)->GetLifetime() << std::endl
		<< "- Logic.ScriptIds   : ";
	std::vector<int> tempScriptList = ((LogicComponent*)temp)->GetScriptId();
	std::vector<int>::iterator itr = tempScriptList.begin();
	while (itr != tempScriptList.end())
		std::cout << *itr++ << " ";
	std::cout << std::endl;
					//	<< "Weapons :   ";
				//std::vector<int>::iterator itr = _WeaponListId.begin();
				//while (itr != _WeaponListId.end())
				//	std::cout << *itr++;
	temp = _ComponentList[TypeIdComponent::AUDIOCOMPONENT];
	std::cout
		<< "- Audio.typeId      : " << ((AudioComponent*)temp)->GetTypeId() << std::endl
		<< "- Audio.filename    : " << ((AudioComponent*)temp)->GetFileName() << std::endl;
	std::cout
		<< "-------------------------------------" << std::endl
		<< "-------------------------------------" << std::endl;
}

void GameObject::SerialInPrefab_Enemy()
{
// Get & Parse File
	std::cout
		<< std::endl
		<< "-------------------------------------" << std::endl
		<< "FileRead_EnemyInfo ------------------" << std::endl;
	rapidjson::Document d;
	char* iBuffer = FileRead_FileToCharPtr("./Resources/TextFiles/Enemy.json");
	ASSERT(iBuffer != nullptr);
//std::cout << iBuffer << std::endl; // show buffer, use to check
	d.Parse<rapidjson::kParseStopWhenDoneFlag>(iBuffer);
// Component List
	rapidjson::Value& s = d["ComponentList"];
	std::vector<int> compList;
	JsonDynamicStore(compList, s);
	std::vector<int>::iterator itr = compList.begin();
	while (itr != compList.end())
		SerialAddComponent((TypeIdComponent)* itr++, s, d);
// Other Values
			//s = d["Weapons"];
			//JsonDynamicStore(_WeaponListId, s);
			// ConvertWeaponIdToWeapon(); // MAY BE CAUSING MEM LEAK
	std::cout << "-------------------------------------" << std::endl;
	delete[] iBuffer;
//Serialisation Check
	PrintStats_Enemy();
}
void GameObject::PrintStats_Enemy() {
	IComponentSystem* temp = nullptr;
	std::string a;
	temp = _ComponentList[TypeIdComponent::TRANSFORMCOMPONENT];
	std::cout
		<< "FilePrint_EnemyInfo ----------------" << std::endl
		<< "- Trans.Pos         : " << ((TransformComponent*)temp)->GetPos() << std::endl
		<< "- Trans.Sca         : " << ((TransformComponent*)temp)->GetScale() << std::endl
		<< "- Trans.Rot         : " << ((TransformComponent*)temp)->GetRotate() << std::endl;
	temp = _ComponentList[TypeIdComponent::GRAPHICSCOMPONENT];
	std::cout
		<< "- Graphics.typeId   : " << ((GraphicComponent*)temp)->GetTypeId() << std::endl
		<< "- Graphics.filename : " << ((GraphicComponent*)temp)->GetFileName() << std::endl;
	temp = _ComponentList[TypeIdComponent::RIGIDBODYCOMPONENT];
	std::cout
		<< "- RBod.Mass         : " << ((RigidBody2D*)temp)->_mass << std::endl
		<< "- RBod.Friction     : " << ((RigidBody2D*)temp)->_fictionVal << std::endl
		<< "- RBod.Static       : " << ((RigidBody2D*)temp)->_static << std::endl;
	temp = _ComponentList[TypeIdComponent::COLLIDERCOMPONENT];
	std::cout
		<< "- Collider.TypId    : " << ((Collider2D*)temp)->_type << std::endl;
	temp = _ComponentList[TypeIdComponent::LOGICCOMPONENT];
	std::cout
		<< "- Logic.Health      : " << ((LogicComponent*)temp)->GetHealth() << std::endl
		<< "- Logic.Speed       : " << ((LogicComponent*)temp)->GetSpeed() << std::endl
		<< "- Logic.Lifetime    : " << ((LogicComponent*)temp)->GetLifetime() << std::endl
		<< "- Logic.ScriptIds   : ";
	std::vector<int> tempScriptList = ((LogicComponent*)temp)->GetScriptId();
	std::vector<int>::iterator itr = tempScriptList.begin();
	while (itr != tempScriptList.end())
		std::cout << *itr++ << " ";
	std::cout << std::endl;
	temp = _ComponentList[TypeIdComponent::AUDIOCOMPONENT];
	std::cout
		<< "- Audio.typeId      : " << ((AudioComponent*)temp)->GetTypeId() << std::endl
		<< "- Audio.filename    : " << ((AudioComponent*)temp)->GetFileName() << std::endl;
	std::cout
		<< "-------------------------------------" << std::endl
		<< "-------------------------------------" << std::endl;
}

void GameObject::SerialInPrefab_Wall()
{
// Get & Parse File
	std::cout
		<< std::endl
		<< "-------------------------------------" << std::endl
		<< "FileRead_WallInfo -------------------" << std::endl;
	rapidjson::Document d;
	char* iBuffer = FileRead_FileToCharPtr("./Resources/TextFiles/Wall.json");
	ASSERT(iBuffer != nullptr);
		//std::cout << iBuffer << std::endl; // show buffer, use to check
	d.Parse<rapidjson::kParseStopWhenDoneFlag>(iBuffer);
// Component List
	rapidjson::Value& s = d["ComponentList"];
	std::vector<int> compList;
	JsonDynamicStore(compList, s);
	std::vector<int>::iterator itr = compList.begin();
	while (itr != compList.end())
		SerialAddComponent((TypeIdComponent)* itr++, s, d);
// Other Values
			//s = d["Weapons"];
			//JsonDynamicStore(_WeaponListId, s);
			// ConvertWeaponIdToWeapon(); // MAY BE CAUSING MEM LEAK
	std::cout << "-------------------------------------" << std::endl;
	delete[] iBuffer;
//Serialisation Check
	PrintStats_Wall();
}
void GameObject::PrintStats_Wall() {
	IComponentSystem* temp = nullptr;
	temp = _ComponentList[TypeIdComponent::TRANSFORMCOMPONENT];
	std::cout
		<< "FilePrint_WallInfo ------------------" << std::endl
		<< "- Trans.Pos      :  " << ((TransformComponent*)temp)->GetPos() << std::endl
		<< "- Trans.Sca      :  " << ((TransformComponent*)temp)->GetScale() << std::endl
		<< "- Trans.Rot      :  " << ((TransformComponent*)temp)->GetRotate() << std::endl;
	temp = _ComponentList[TypeIdComponent::GRAPHICSCOMPONENT];
	std::cout
		<< "- Graphics       :  " << "[placeHolder] " << std::endl;
	temp = _ComponentList[TypeIdComponent::RIGIDBODYCOMPONENT];
	std::cout
		<< "- RBod.Mass      :  " << ((RigidBody2D*)temp)->_mass << std::endl
		<< "- RBod.Friction  :  " << ((RigidBody2D*)temp)->_fictionVal << std::endl
		<< "- RBod.Static    :  " << ((RigidBody2D*)temp)->_static << std::endl;
	temp = _ComponentList[TypeIdComponent::COLLIDERCOMPONENT];
	std::cout
		<< "- Collider.TypId :  " << ((Collider2D*)temp)->_type << std::endl;
	std::cout
		<< "-------------------------------------" << std::endl
		<< "-------------------------------------" << std::endl
		<< std::endl;
}