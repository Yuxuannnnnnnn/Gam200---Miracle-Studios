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


	for (auto& component : _ComponentList)
	{
		delete component.second;
	}
}


unsigned GameObject::GameObjectType() const
{
	return _typeId;
}
unsigned GameObject::Get_typeId() const
{
	return _typeId;
}
size_t GameObject::Get_uID() const
{
	return _uId;
}

// DEPRECIATED - Add a specific component to the GameObject
IComponentSystem* GameObject::addcomponent(TypeIdComponent componentType)
{
	switch (componentType)
	{
	case TypeIdComponent::TRANSFORMCOMPONENT:
		_ComponentList[(unsigned)TypeIdComponent::TRANSFORMCOMPONENT] = new TransformComponent();
		break;
	case TypeIdComponent::GRAPHICSCOMPONENT:
		_ComponentList[(unsigned)TypeIdComponent::GRAPHICSCOMPONENT] = new GraphicComponent();
		break;
	case TypeIdComponent::RIGIDBODYCOMPONENT:
		_ComponentList[(unsigned)TypeIdComponent::RIGIDBODYCOMPONENT] = new RigidBody2D();
		break;
	case TypeIdComponent::COLLIDERCOMPONENT:
		_ComponentList[(unsigned)TypeIdComponent::COLLIDERCOMPONENT] = new Collider2D();
		break;
	case TypeIdComponent::LOGICCOMPONENT:
		_ComponentList[(unsigned)TypeIdComponent::LOGICCOMPONENT] = new LogicComponent();
		break;

	}

	return  _ComponentList[(unsigned)componentType];
}


// AddComponent for during Serialisation
void GameObject::SerialAddComponent
	(TypeIdComponent componentType, rapidjson::Value& s, rapidjson::Document& d)
{
	std::cout << "- GameObject::SerialAddComponent(" << (unsigned)componentType << ") : ";

	IComponentSystem* temp;
	switch (componentType)
	{

	case TypeIdComponent::TRANSFORMCOMPONENT:	std::cout << "Transform";

		_ComponentList.insert(std::pair<unsigned, IComponentSystem*>((unsigned)TypeIdComponent::TRANSFORMCOMPONENT, new TransformComponent()));
		//_ComponentList[(unsigned)TypeIdComponent::TRANSFORMCOMPONENT] = new TransformComponent(); 	// create new component
		temp = _ComponentList[(unsigned)TypeIdComponent::TRANSFORMCOMPONENT];		// 'temp' to access new component
		s = d["Position"];												// store values needed
		JsonDynamicStore(((TransformComponent*)temp)->GetPos(), s);
		s = d["Scale"];
		JsonDynamicStore(((TransformComponent*)temp)->GetScale(), s);
		s = d["Rotate"];
		JsonDynamicStore(((TransformComponent*)temp)->GetRotate(), s);
		break;

	case TypeIdComponent::GRAPHICSCOMPONENT:	std::cout << "Graphics";
		_ComponentList.insert(std::pair<unsigned, IComponentSystem*>((unsigned)TypeIdComponent::GRAPHICSCOMPONENT, new GraphicComponent()));
		//_ComponentList[(unsigned)TypeIdComponent::GRAPHICSCOMPONENT] = new GraphicComponent();
		temp = _ComponentList[(unsigned)TypeIdComponent::GRAPHICSCOMPONENT];
		s = d["G.TypeId"];
		JsonDynamicStore(((GraphicComponent*)temp)->GetTypeId(), s);
		s = d["G.FileName"];
		JsonDynamicStore(((GraphicComponent*)temp)->GetFileName(), s);
		break;

	case TypeIdComponent::RIGIDBODYCOMPONENT:	std::cout << "R. Body";
		_ComponentList.insert(std::pair<unsigned, IComponentSystem*>((unsigned)TypeIdComponent::RIGIDBODYCOMPONENT, new RigidBody2D()));
		//_ComponentList[(unsigned)TypeIdComponent::RIGIDBODYCOMPONENT] = new RigidBody2D();
		temp = _ComponentList[(unsigned)TypeIdComponent::RIGIDBODYCOMPONENT];
		s = d["Mass"];
		JsonDynamicStore(((RigidBody2D*)temp)->_mass, s);
		s = d["Friction"];
		JsonDynamicStore(((RigidBody2D*)temp)->_fictionVal, s);
		s = d["Static"];
		JsonDynamicStore(((RigidBody2D*)temp)->_static, s);
		break;

	case TypeIdComponent::COLLIDERCOMPONENT:	{ std::cout << "Collider";
		unsigned type;

		s = d["ColliderTypeId"];
		JsonDynamicStore(type, s);

		if (type == (int)ColliderType::BOX_COLLIDER)
		{
			temp = new BoxCollider2D();
		}
		else if (type == (int)ColliderType::CIRCLE_COLLIDER)
		{
			temp = new CircleCollider2D();
		}
		else if (type == (int)ColliderType::LINE_COLLIDER)
		{
			temp = new EdgeCollider2D();
		}
		else
			temp = nullptr;

		reinterpret_cast<Collider2D*>(temp)->_type = type;

		_ComponentList.insert(std::pair<unsigned, IComponentSystem*>((unsigned)TypeIdComponent::COLLIDERCOMPONENT, temp));
		break;
	}
	case TypeIdComponent::LOGICCOMPONENT:		std::cout << "Logic";
		_ComponentList.insert(std::pair<unsigned, IComponentSystem*>((unsigned)TypeIdComponent::LOGICCOMPONENT, new LogicComponent()));
		//_ComponentList[(unsigned)TypeIdComponent::LOGICCOMPONENT] = new LogicComponent();
		temp = _ComponentList[(unsigned)TypeIdComponent::LOGICCOMPONENT];
		s = d["ScriptId"];
		JsonDynamicStore(((LogicComponent*)temp)->GetScriptId(), s);
		s = d["Health"];
		JsonDynamicStore(((LogicComponent*)temp)->GetHealth(), s);
		s = d["Speed"];
		JsonDynamicStore(((LogicComponent*)temp)->GetSpeed(), s);
		s = d["Lifetime"];
		JsonDynamicStore(((LogicComponent*)temp)->GetLifetime(), s);
		break;

	case TypeIdComponent::AUDIOCOMPONENT:		std::cout << "Audio";
		_ComponentList.insert(std::pair<unsigned, IComponentSystem*>((unsigned)TypeIdComponent::AUDIOCOMPONENT, new AudioComponent()));
		//_ComponentList[(unsigned)TypeIdComponent::AUDIOCOMPONENT] = new AudioComponent();
		temp = _ComponentList[(unsigned)TypeIdComponent::AUDIOCOMPONENT];
		s = d["A.TypeId"];
		JsonDynamicStore(((AudioComponent*)temp)->GetTypeId(), s);
		s = d["A.FileName"];
		JsonDynamicStore(((AudioComponent*)temp)->GetFileName(), s);
		break;

	default:
		temp = nullptr;
		break;
	}
	temp->SetParentPtr(this); // set ParentPtr
	std::cout << std::endl;
}


void GameObject::CopyComponent	// Copy all components from 'original'(Prototype/Prefab/whateverYouCallIt)
	(Map_ComponentList& original)
{
	std::cout << "\t GameObject::CopyComponent() : ";

	Map_ComponentList::iterator itr = original.begin();

	while (itr != original.end())
	{
		IComponentSystem* temp; // temp ptr, will assign in the switch below
		switch (itr->first)
		{
		case (unsigned)TypeIdComponent::TRANSFORMCOMPONENT:	std::cout << "Transform, ";

			temp = new TransformComponent(
				*((TransformComponent*)itr->second)
			); // using copyCtor to copy var, idk if it works
			_ComponentList[(unsigned)TypeIdComponent::TRANSFORMCOMPONENT] =  temp;
			break;

		case (unsigned)TypeIdComponent::GRAPHICSCOMPONENT:	std::cout << "Graphics, ";

			temp = new GraphicComponent(
				*((GraphicComponent*)itr->second)
			);
			_ComponentList[(unsigned)TypeIdComponent::GRAPHICSCOMPONENT] = temp;
			break;

		case (unsigned)TypeIdComponent::RIGIDBODYCOMPONENT:	std::cout << "R. Body, ";

			temp = new RigidBody2D(
				*((RigidBody2D*)itr->second)
			);
			_ComponentList[(unsigned)TypeIdComponent::RIGIDBODYCOMPONENT] = temp;
			break;

		case (unsigned)TypeIdComponent::COLLIDERCOMPONENT: { std::cout << "Collider, ";

			int type = reinterpret_cast<Collider2D*>(itr->second)->_type;

			if (type == (int)ColliderType::BOX_COLLIDER)
			{
				temp = new BoxCollider2D(
					*((BoxCollider2D*)itr->second)
				);
			}
			else if (type == (int)ColliderType::CIRCLE_COLLIDER)
			{
				temp = new CircleCollider2D(
					*((CircleCollider2D*)itr->second)
				);
			}
			else if (type == (int)ColliderType::LINE_COLLIDER)
			{
				temp = new EdgeCollider2D(
					*((EdgeCollider2D*)itr->second)
				);
			}
			else
				temp = nullptr;

			_ComponentList[(unsigned)TypeIdComponent::COLLIDERCOMPONENT] = temp;
			break;
		}
		case (unsigned)TypeIdComponent::LOGICCOMPONENT:		std::cout << "Logic, ";

			temp = new LogicComponent(
				*((LogicComponent*)itr->second)
			);
			_ComponentList[(unsigned)TypeIdComponent::LOGICCOMPONENT] = temp;
			break;

		case (unsigned)TypeIdComponent::AUDIOCOMPONENT:		std::cout << "Audio, ";

			temp = new AudioComponent(
				*((AudioComponent*)itr->second)
			);
			_ComponentList[(unsigned)TypeIdComponent::AUDIOCOMPONENT] = temp;
			break;

		default:
			temp = nullptr;
			break;
		}
		temp->SetParentPtr(this); // reset ParentPtr
		++itr;
	}
	std::cout << std::endl;
}

IComponentSystem* GameObject::GetComponent(TypeIdComponent typeId) // GetChildComponent
{
	return _ComponentList[(unsigned)typeId];
}

// Cloning GO
GameObject* GameObject::Clone(size_t uId)
{
	//std::cout << "GameObject::Clone()" << std::endl;
	GameObject* temp = new GameObject(uId, _typeId);
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
	char* iBuffer = FileRead_FileToCharPtr("./Resources/TextFiles/GameObjects/Player.json"); //Read in whole file as char pointer
	ASSERT(iBuffer != nullptr);			//std::cout << iBuffer << std::endl; //Show buffer, use to check
	d.Parse<rapidjson::kParseStopWhenDoneFlag>(iBuffer);					 //Read whole file in RapidJson format

// Component List
	rapidjson::Value& s = d["ComponentList"];			//Get Numberlist of Component Data in RapidJson Format	
	std::vector<int> compList;				
	JsonDynamicStore(compList, s);						//Convert Numberlist of Component Data to stl dynamic list format
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
	temp = _ComponentList[(unsigned)TypeIdComponent::TRANSFORMCOMPONENT];
	std::cout
		<< "FilePrint_PlayerInfo ----------------" << std::endl
		<< "- Trans.Pos         : " << ((TransformComponent*)temp)->GetPos() << std::endl
		<< "- Trans.Sca         : " << ((TransformComponent*)temp)->GetScale() << std::endl
		<< "- Trans.Rot         : " << ((TransformComponent*)temp)->GetRotate() << std::endl;
	temp = _ComponentList[(unsigned)TypeIdComponent::GRAPHICSCOMPONENT];
	std::cout
		<< "- Graphics.typeId   : " << ((GraphicComponent*)temp)->GetTypeId() << std::endl
		<< "- Graphics.filename : " << ((GraphicComponent*)temp)->GetFileName() << std::endl;
	temp = _ComponentList[(unsigned)TypeIdComponent::RIGIDBODYCOMPONENT];
	std::cout
		<< "- RBod.Mass         : " << ((RigidBody2D*)temp)->_mass << std::endl
		<< "- RBod.Friction     : " << ((RigidBody2D*)temp)->_fictionVal << std::endl
		<< "- RBod.Static       : " << ((RigidBody2D*)temp)->_static << std::endl;
	temp = _ComponentList[(unsigned)TypeIdComponent::COLLIDERCOMPONENT];
	std::cout
		<< "- Collider.TypId    : " << ((Collider2D*)temp)->_type << std::endl;
	temp = _ComponentList[(unsigned)TypeIdComponent::LOGICCOMPONENT];
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
	temp = _ComponentList[(unsigned)TypeIdComponent::AUDIOCOMPONENT];
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
	std::cout << std::endl 
		<< "-------------------------------------" << std::endl 
		<< "FileRead_EnemyInfo ------------------" << std::endl;

	rapidjson::Document d;
	char* iBuffer = FileRead_FileToCharPtr("./Resources/TextFiles/GameObjects/Enemy.json");
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
	temp = _ComponentList[(unsigned)TypeIdComponent::TRANSFORMCOMPONENT];
	std::cout
		<< "FilePrint_EnemyInfo ----------------" << std::endl
		<< "- Trans.Pos         : " << ((TransformComponent*)temp)->GetPos() << std::endl
		<< "- Trans.Sca         : " << ((TransformComponent*)temp)->GetScale() << std::endl
		<< "- Trans.Rot         : " << ((TransformComponent*)temp)->GetRotate() << std::endl;
	temp = _ComponentList[(unsigned)TypeIdComponent::GRAPHICSCOMPONENT];
	std::cout
		<< "- Graphics.typeId   : " << ((GraphicComponent*)temp)->GetTypeId() << std::endl
		<< "- Graphics.filename : " << ((GraphicComponent*)temp)->GetFileName() << std::endl;
	temp = _ComponentList[(unsigned)TypeIdComponent::RIGIDBODYCOMPONENT];
	std::cout
		<< "- RBod.Mass         : " << ((RigidBody2D*)temp)->_mass << std::endl
		<< "- RBod.Friction     : " << ((RigidBody2D*)temp)->_fictionVal << std::endl
		<< "- RBod.Static       : " << ((RigidBody2D*)temp)->_static << std::endl;
	temp = _ComponentList[(unsigned)TypeIdComponent::COLLIDERCOMPONENT];
	std::cout
		<< "- Collider.TypId    : " << ((Collider2D*)temp)->_type << std::endl;
	temp = _ComponentList[(unsigned)TypeIdComponent::LOGICCOMPONENT];
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
	temp = _ComponentList[(unsigned)TypeIdComponent::AUDIOCOMPONENT];
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
	char* iBuffer = FileRead_FileToCharPtr("./Resources/TextFiles/GameObjects/Wall.json");
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
	temp = _ComponentList[(unsigned)TypeIdComponent::TRANSFORMCOMPONENT];
	std::cout
		<< "FilePrint_WallInfo ------------------" << std::endl
		<< "- Trans.Pos      :  " << ((TransformComponent*)temp)->GetPos() << std::endl
		<< "- Trans.Sca      :  " << ((TransformComponent*)temp)->GetScale() << std::endl
		<< "- Trans.Rot      :  " << ((TransformComponent*)temp)->GetRotate() << std::endl;
	temp = _ComponentList[(unsigned)TypeIdComponent::GRAPHICSCOMPONENT];
	std::cout
		<< "- Graphics       :  " << "[placeHolder] " << std::endl;
	temp = _ComponentList[(unsigned)TypeIdComponent::RIGIDBODYCOMPONENT];
	std::cout
		<< "- RBod.Mass      :  " << ((RigidBody2D*)temp)->_mass << std::endl
		<< "- RBod.Friction  :  " << ((RigidBody2D*)temp)->_fictionVal << std::endl
		<< "- RBod.Static    :  " << ((RigidBody2D*)temp)->_static << std::endl;
	temp = _ComponentList[(unsigned)TypeIdComponent::COLLIDERCOMPONENT];
	std::cout
		<< "- Collider.TypId :  " << ((Collider2D*)temp)->_type << std::endl;
	std::cout
		<< "-------------------------------------" << std::endl
		<< "-------------------------------------" << std::endl
		<< std::endl;
}

void GameObject::SerialInPrefab_Bullet()
{
	// Get & Parse File
	std::cout << std::endl
		<< "-------------------------------------" << std::endl
		<< "FilePrint_BulletInfo ----------------" << std::endl;

	rapidjson::Document d;
	char* iBuffer = FileRead_FileToCharPtr("./Resources/TextFiles/GameObjects/Bullet.json");
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
	PrintStats_Bullet();
}
void GameObject::PrintStats_Bullet() {
	IComponentSystem* temp = nullptr;
	std::string a;
	temp = _ComponentList[(unsigned)TypeIdComponent::TRANSFORMCOMPONENT];
	std::cout
		<< "FilePrint_BulletInfo ---------------" << std::endl
		<< "- Trans.Pos         : " << ((TransformComponent*)temp)->GetPos() << std::endl
		<< "- Trans.Sca         : " << ((TransformComponent*)temp)->GetScale() << std::endl
		<< "- Trans.Rot         : " << ((TransformComponent*)temp)->GetRotate() << std::endl;
	temp = _ComponentList[(unsigned)TypeIdComponent::GRAPHICSCOMPONENT];
	std::cout
		<< "- Graphics.typeId   : " << ((GraphicComponent*)temp)->GetTypeId() << std::endl
		<< "- Graphics.filename : " << ((GraphicComponent*)temp)->GetFileName() << std::endl;
	temp = _ComponentList[(unsigned)TypeIdComponent::RIGIDBODYCOMPONENT];
	std::cout
		<< "- RBod.Mass         : " << ((RigidBody2D*)temp)->_mass << std::endl
		<< "- RBod.Friction     : " << ((RigidBody2D*)temp)->_fictionVal << std::endl
		<< "- RBod.Static       : " << ((RigidBody2D*)temp)->_static << std::endl;
	temp = _ComponentList[(unsigned)TypeIdComponent::COLLIDERCOMPONENT];
	std::cout
		<< "- Collider.TypId    : " << ((Collider2D*)temp)->_type << std::endl;
	temp = _ComponentList[(unsigned)TypeIdComponent::LOGICCOMPONENT];
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
	std::cout
		<< "-------------------------------------" << std::endl
		<< "-------------------------------------" << std::endl;
}
