#include "PrecompiledHeaders.h"
#include "GameObject.h"

GameObject::GameObject(size_t uId, unsigned typeId)
	:_uId{ uId }, _typeId{ typeId }
{
	std::cout << "GameObject::GameObject()" << std::endl;
}

GameObject::~GameObject()
{
	std::cout << "GameObject::~GameObject()" << std::endl;
	std::unordered_map< TypeIdComponent, IComponentSystem* >::iterator iterator = _ComponentList.begin();
	while (iterator != _ComponentList.end())
	{
		delete iterator->second;
		iterator++;
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
	std::cout << "\t GameObject::SerialAddComponent(" << (unsigned)componentType << ") : ";
	switch (componentType)
	{
		IComponentSystem* temp;
	case TypeIdComponent::TRANSFORMCOMPONENT:
		std::cout << "Transform";
		_ComponentList[TypeIdComponent::TRANSFORMCOMPONENT] = new TransformComponent();
		temp = _ComponentList[TypeIdComponent::TRANSFORMCOMPONENT];
		s = d["Position"];
		JsonDynamicStore(((TransformComponent*)temp)->GetPos(), s);
		s = d["Scale"];
		JsonDynamicStore(((TransformComponent*)temp)->GetScale(), s);
		s = d["Rotate"];
		JsonDynamicStore(((TransformComponent*)temp)->GetRotate(), s);
		break;
	case TypeIdComponent::GRAPHICSCOMPONENT:
		std::cout << "Graphics";
		_ComponentList[TypeIdComponent::GRAPHICSCOMPONENT] = new GraphicComponent();
		break;
	case TypeIdComponent::RIGIDBODYCOMPONENT:
		std::cout << "R. Body";
		_ComponentList[TypeIdComponent::RIGIDBODYCOMPONENT] = new RigidBody2D();
		temp = _ComponentList[TypeIdComponent::RIGIDBODYCOMPONENT];
		s = d["Mass"];
		JsonDynamicStore(((RigidBody2D*)temp)->_mass, s);
		s = d["Friction"];
		JsonDynamicStore(((RigidBody2D*)temp)->_fictionVal, s);
		s = d["Static"];
		JsonDynamicStore(((RigidBody2D*)temp)->_static, s);
		break;
	case TypeIdComponent::COLLIDERCOMPONENT:
		std::cout << "Collider";
		_ComponentList[TypeIdComponent::COLLIDERCOMPONENT] = new Collider2D();
		temp = _ComponentList[TypeIdComponent::COLLIDERCOMPONENT];
		s = d["ColliderTypeId"];
		JsonDynamicStore(((Collider2D*)temp)->_type, s);
		break;
	case TypeIdComponent::LOGICCOMPONENT:
		std::cout << "Logic";
		_ComponentList[TypeIdComponent::LOGICCOMPONENT] = new LogicComponent();
		temp = _ComponentList[TypeIdComponent::LOGICCOMPONENT];
		s = d["ScriptId"];
		JsonDynamicStore(((LogicComponent*)temp)->GetScriptId(), s);
		s = d["Health"];
		JsonDynamicStore(((LogicComponent*)temp)->GetHealth(), s);
		s = d["Speed"];
		JsonDynamicStore(((LogicComponent*)temp)->GetSpeed(), s);
		break;
	default:
		temp = nullptr;
		break;
	}
	std::cout << std::endl;
}

// Copy all components from 'original'(Prototype/Prefab/whateverYouCallIt)
void GameObject::CopyComponent
	(std::unordered_map< TypeIdComponent, IComponentSystem* >& original)
{
	std::cout << "\t\t GameObject::CopyComponent() : ";
	std::unordered_map< TypeIdComponent, IComponentSystem* >::iterator itr = original.begin();
	while (itr != original.end())
	{
		IComponentSystem* temp;
		switch (itr->first)
		{
		case TypeIdComponent::TRANSFORMCOMPONENT:
			std::cout << "Transform, ";
			temp = new TransformComponent(
				*((TransformComponent*)itr->second)
			); // using copyCtor to copy var, idk if it works
			_ComponentList[TypeIdComponent::TRANSFORMCOMPONENT] =  temp;
			break;
		case TypeIdComponent::GRAPHICSCOMPONENT:
			std::cout << "Graphics, ";
			_ComponentList[TypeIdComponent::GRAPHICSCOMPONENT] = new GraphicComponent();
			break;
		case TypeIdComponent::RIGIDBODYCOMPONENT:
			std::cout << "R. Body, ";
			temp = new RigidBodyComponent(
				*((RigidBodyComponent*)itr->second)
			);
			_ComponentList[TypeIdComponent::RIGIDBODYCOMPONENT] = temp;
			break;
		case TypeIdComponent::COLLIDERCOMPONENT:
			std::cout << "Collider, ";
			temp = new Collider2D(
				*((Collider2D*)itr->second)
			);
			_ComponentList[TypeIdComponent::COLLIDERCOMPONENT] = temp;
			break;
		case TypeIdComponent::LOGICCOMPONENT:
			std::cout << "Logic, ";
			temp = new LogicComponent(
				*((LogicComponent*)itr->second)
			);
			_ComponentList[TypeIdComponent::LOGICCOMPONENT] = temp;

			//_ComponentList[LOGICCOMPONENT] = new LogicComponent();
			//temp = _ComponentList[LOGICCOMPONENT];
			//s = d["ScriptId"];
			//JsonDynamicStore(((LogicComponent*)temp)->GetScriptId(), s);
			//s = d["Health"];
			//JsonDynamicStore(((LogicComponent*)temp)->GetHealth(), s);
			//s = d["Speed"];
			//JsonDynamicStore(((LogicComponent*)temp)->GetSpeed(), s);
			break;
		default:
			temp = nullptr;
			break;
		}
		++itr;
	}
	std::cout << std::endl;
}

// Cloning IGO
GameObject* GameObject::Clone()
{
	std::cout << "GameObject::Clone()" << std::endl;
	GameObject* temp = new GameObject(_uId, _typeId);
	// copy _ComponentList;
	temp->CopyComponent(_ComponentList);
	// return GO so that can put into GOFac's _listObj
	return temp;
}

void GameObject::SerialInPrefab_Player()
{
// Get & Parse File
	std::cout << std::endl << "FileRead_PlayerInfo -----------------" << std::endl;
	rapidjson::Document d;
	char* iBuffer = FileRead_FileToCharPtr("./Resources/TextFiles/playerNew.json");
	ASSERT(iBuffer != nullptr);
	std::cout << iBuffer << std::endl;
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
	temp = _ComponentList[TypeIdComponent::TRANSFORMCOMPONENT];
	std::cout
		<< "FilePrint_PlayerInfo ----------------" << std::endl
		<< "\tTrans.Pos      :  " << ((TransformComponent*)temp)->GetPos() << std::endl
		<< "\tTrans.Sca      :  " << ((TransformComponent*)temp)->GetScale() << std::endl
		<< "\tTrans.Rot      :  " << ((TransformComponent*)temp)->GetRotate() << std::endl;
	temp = _ComponentList[TypeIdComponent::GRAPHICSCOMPONENT];
	std::cout
		<< "\tGraphics       :  " << "[placeHolder] " << std::endl;
	temp = _ComponentList[TypeIdComponent::RIGIDBODYCOMPONENT];
	std::cout
		<< "\tRBod.Mass      :  " << ((RigidBody2D*)temp)->_mass << std::endl
		<< "\tRBod.Friction  :  " << ((RigidBody2D*)temp)->_fictionVal << std::endl
		<< "\tRBod.Static    :  " << ((RigidBody2D*)temp)->_static << std::endl;
	temp = _ComponentList[TypeIdComponent::COLLIDERCOMPONENT];
	std::cout
		<< "\tCollider.TypId :  " << ((Collider2D*)temp)->_type << std::endl;
	temp = _ComponentList[TypeIdComponent::LOGICCOMPONENT];
	std::cout
		<< "\tLogic.Health   :  " << ((LogicComponent*)temp)->GetHealth() << std::endl
		<< "\tLogic.Speed    :  " << ((LogicComponent*)temp)->GetSpeed() << std::endl
		<< "\tLogic.Lifetime :  " << ((LogicComponent*)temp)->GetLifetime() << std::endl
		<< "\tLogic.ScriptIds:  ";
	std::vector<int> tempScriptList = ((LogicComponent*)temp)->GetScriptId();
	std::vector<int>::iterator itr = tempScriptList.begin();
	while (itr != tempScriptList.end())
		std::cout << *itr++ << " ";
	//	<< "Weapons :   ";
//std::vector<int>::iterator itr = _WeaponListId.begin();
//while (itr != _WeaponListId.end())
//	std::cout << *itr++;
	std::cout << std::endl
		<< "-------------------------------------"
		<< std::endl << std::endl;
}