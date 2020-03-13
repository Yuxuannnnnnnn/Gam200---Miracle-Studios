#include "PrecompiledHeaders.h"
#include "Factory.h"

Factory::Factory() : 
	_lastGameObjectId{0}
{
}

void Factory::Init()
{
#ifdef LEVELEDITOR
	MyResourceSystem.AddNewScene({ "BackUp", "./Resources/TextFiles/Window/BackUp.json" });
#endif
}

Factory::~Factory()
{
	ClearLevel();

	//Delete all component creators
	for (auto& itr : _componentMap)
		delete itr.second;
	_componentMap.clear();
}


GameObject* Factory::CloneGameObject(GameObject* gameobject)
{
	if (!gameobject)
		return nullptr;

	GameObject* clonedObject = gameobject->Clone(++_lastGameObjectId);
	_gameObjectIdMap.insert({ clonedObject->Get_uID(),clonedObject });
	_allExistGameObjectList.insert(clonedObject->Get_uID());

	return clonedObject;
}


//Called by GameObject Clone() function
GameObject* Factory::CloneChildGameObject(GameObject* gameobject)
{
	if (!gameobject)
		return nullptr;

	GameObject* clonedObject = gameobject->Clone(++_lastGameObjectId);
	_childGameObjectIdMap.insert({ clonedObject->Get_uID(),clonedObject });
	_allExistGameObjectList.insert(clonedObject->Get_uID());

	return clonedObject;
}

GameObject* Factory::CloneChildGameObjectPrototype(GameObject* gameobject)
{
	if (!gameobject)
		return nullptr;

	GameObject* clonedObject = gameobject->CloneChildPrototype();

	return clonedObject;
}

void Factory::RemoveChildGameObject(size_t UId)
{
	_childGameObjectIdMap.erase(UId);
	_allExistGameObjectList.erase(UId);
}

void Factory::Destroy(GameObject* gameObject)
{
	//Add the object to the to be deleted list they will be delete
	//when the factory is updated
	_objectsToBeDeleted.insert(gameObject);
}

void Factory::Update(float dt)
{
	//Delete all objects in the _objectsToBeDeleted list 

	for (auto& it : _objectsToBeDeleted)
	{
		size_t UId = it->Get_uID();
		
		if (_gameObjectIdMap.find(UId) != _gameObjectIdMap.end())
		{
			delete it;
			_gameObjectIdMap.erase(UId);
			_allExistGameObjectList.erase(UId);
		}
		else if (_childGameObjectIdMap.find(UId) != _childGameObjectIdMap.end())
		{
			if (_allExistGameObjectList.find(it->GetParent()->Get_uID()) != _allExistGameObjectList.end())
				it->GetParent()->RemoveChildObject(it);

			delete it;
			_childGameObjectIdMap.erase(UId);
			_allExistGameObjectList.erase(UId);
		}

	}
	//All objects to be delete have been deleted
	_objectsToBeDeleted.clear();
}

void Factory::DestroyAll()
{
	for (auto& it : _gameObjectIdMap)
		_objectsToBeDeleted.insert(it.second);

	for (auto& it : _childGameObjectIdMap)
		_objectsToBeDeleted.insert(it.second);
}

GameObject* Factory::CreateEmptyGameObject()
{
	GameObject* gameObject = new GameObject(++_lastGameObjectId);
	_gameObjectIdMap.insert({ gameObject->Get_uID(),gameObject });
	_allExistGameObjectList.insert(gameObject->Get_uID());

	return gameObject;
}

GameObject* Factory::CreateEmptyChildGameObject()
{
	GameObject* gameObject = new GameObject(++_lastGameObjectId);
	_childGameObjectIdMap.insert({ gameObject->Get_uID(),gameObject });
	_allExistGameObjectList.insert(gameObject->Get_uID());

	return gameObject;
}

size_t Factory::GetNextGameObjectUId()
{
	return ++_lastGameObjectId;
}

IComponent* Factory::CreateEmptyComponent(const std::string& name)
{
	ComponentMapType::iterator iter = _componentMap.find(name);

	if (iter != _componentMap.end())
		return iter->second->Create();

	return nullptr;
}

void Factory::AddComponentCreator(const std::string& name, ComponentCreator* creator)
{
	_componentMap[name] = creator;
	MyComponentManger.AddNewComponentContainer(creator->TypeId);
}

GameObject* Factory::GetObjectWithId(size_t id)
{
	return _gameObjectIdMap[id];
}

int Factory::CheckObjOrignialPointer(GameObject* obj)
{
	for (auto& pair : _gameObjectIdMap)
	{
		if (pair.second == obj)
			return 1;

		if (CheckObjOrignialChildPointer(pair.second, obj))
		{
			return 3;
		}

	}


	auto& prototypeList = MyResourceSystem.GetPrototypeMap();
	for (auto& pair : prototypeList)
	{
		if (pair.second == obj)
			return 2;

		if (CheckObjOrignialChildPointer(pair.second, obj))
		{
			return 2;
		}
	}
	
	return 0;
}

int Factory::CheckObjOrignialChildPointer(GameObject* obj, GameObject * original)
{
	std::unordered_map<size_t, GameObject*>& childlist = obj->GetChildList();
	for (auto& child: childlist)
	{
		if (child.second == original)
			return 3;

		if (CheckObjOrignialChildPointer(child.second, original))
		{
			return 3;
		}
	}
	return 0;
}

GameObject* Factory::GetObjOrignialPointer(size_t obj)
{
	for (auto& pair : _gameObjectIdMap)
	{
		if (pair.first == obj)
			return pair.second;

		if (GetObjOrignialChildPointer(pair.second, obj))
		{
			return GetObjOrignialChildPointer(pair.second, obj);
		}

	}

	return nullptr;
}

GameObject* Factory::GetObjOrignialChildPointer(GameObject * obj, size_t original)
{
	std::unordered_map<size_t, GameObject*>& childlist = obj->GetChildList();
	for (auto& child : childlist)
	{
		if (child.first == original)
			return child.second;

		if (GetObjOrignialChildPointer(child.second, original))
		{
			return GetObjOrignialChildPointer(child.second, original);
		}
	}

	return nullptr;
}



std::unordered_map<size_t, GameObject*>& Factory::getObjectlist()
{
	return _gameObjectIdMap;
}

void Factory::SerialiseLevel(std::string FileName)
{
	Serialiser Level(FileName);


	//Serialise BinaryMap - Used creating Static gameobjects on screen & collision data & AI node Map
	//Serialise Mobile GameObjects with components
		//Player components

#ifndef LEVELEDITOR
	
	typedef std::map<std::string, std::string> NamePath;
	typedef std::unordered_map<std::string, std::string> unNamePath;
	typedef std::unordered_map<std::string, std::pair<std::string, std::string>> NamePairMap;

	//Serialise Prototypes
	if (Level.HasMember("PrototypesFilePaths"))
	{
		unNamePath PrototypesResourceList;

		for (unsigned i = 0; i < Level["PrototypesFilePaths"].Size(); i++)	//Loop through the Serialisation Array
		{
			std::string filePath = Level["PrototypesFilePaths"][i].GetString();
			size_t namesize = filePath.find_last_of(".json") - 5 - filePath.find_last_of("\\/");
			std::string fileName = filePath.substr(filePath.find_last_of("\\/") + 1, namesize);
			PrototypesResourceList.insert(std::pair<std::string, std::string>(fileName, filePath));
		}
		MyResourceManager.AddPrototypeResourceList(PrototypesResourceList);
	}


	//Serialise Texture
	if (Level.HasMember("TexturesFilesPaths"))
	{
		NamePath TextureResourceList;

		for (unsigned i = 0; i < Level["TexturesFilesPaths"].Size(); i++)	//Loop through the Serialisation Array
		{
			std::string filePath = Level["TexturesFilesPaths"][i].GetString();
			//size_t namesize = filePath.find_last_of(".png") - 4 - filePath.find_last_of("\\/");
			std::string fileName = filePath.substr(filePath.find_last_of("\\/") + 1);
			TextureResourceList.insert(std::pair<std::string, std::string>(fileName, filePath));
		}
		MyResourceManager.AddTexture2DResourceList(TextureResourceList);
	}

	//Serialise Shader
	if (Level.HasMember("ShaderFilesPaths"))
	{
		NamePairMap ShaderResourceList;

		for (unsigned i = 0; i < Level["ShaderFilesPaths"].Size(); i++)	//Loop through the Serialisation Array
		{
			std::string fileName = Level["ShaderFilesPaths"][i][0].GetString();
			std::string fileVert = Level["ShaderFilesPaths"][i][1].GetString();
			std::string fileFrag = Level["ShaderFilesPaths"][i][2].GetString();

			ShaderResourceList.insert({ fileName , {fileVert, fileFrag} });
		}
		MyResourceManager.AddShaderResourceList(ShaderResourceList);
	}

	//Serialise Animation
	if (Level.HasMember("AnimationDataFilesPaths"))
	{
		NamePath AnimationResourceList;

		for (unsigned i = 0; i < Level["AnimationDataFilesPaths"].Size(); i++)	//Loop through the Serialisation Array
		{
			std::string filePath = Level["AnimationDataFilesPaths"][i].GetString();
			//size_t namesize = filePath.find_last_of(".json") - 5 - filePath.find_last_of("\\/");
			std::string fileName = filePath.substr(filePath.find_last_of("\\/") + 1);
			AnimationResourceList.insert(std::pair<std::string, std::string>(fileName, filePath));
		}
		MyResourceManager.AddAnimationResourceList(AnimationResourceList);
	}

	//Serialise Audio - SFX
	if (Level.HasMember("AudioSFXFilesPaths"))
	{
		NamePath AudioResourceList;

		for (unsigned i = 0; i < Level["AudioSFXFilesPaths"].Size(); i++)	//Loop through the Serialisation Array
		{
			std::string filePath = Level["AudioSFXFilesPaths"][i].GetString();
			//size_t namesize = filePath.find_last_of(".ogg") - 4 - filePath.find_last_of("\\/");
			std::string fileName = filePath.substr(filePath.find_last_of("\\/") + 1);
			//std::cout << "FileName" << fileName << std::endl;
			AudioResourceList.insert(std::pair<std::string, std::string>(fileName, filePath));
		}
		MyResourceManager.AddAudioResourceList(AudioResourceList);
	}

	//Serialise Audio - BGM
	if (Level.HasMember("AudioBGMFilesPaths"))
	{
		NamePath AudioResourceList;

		for (unsigned i = 0; i < Level["AudioBGMFilesPaths"].Size(); i++)	//Loop through the Serialisation Array
		{
			std::string filePath = Level["AudioBGMFilesPaths"][i].GetString();
			//size_t namesize = filePath.find_last_of(".ogg") - 4 - filePath.find_last_of("\\/");
			std::string fileName = filePath.substr(filePath.find_last_of("\\/") + 1);
			//std::cout << "FileName" << fileName << std::endl;
			AudioResourceList.insert(std::pair<std::string, std::string>(fileName, filePath));
		}
		MyResourceManager.AddLoopAudioResourceList(AudioResourceList);
	}

	//Serialise Font
	if (Level.HasMember("FontFilesPath"))
	{
		NamePath FontResourceList;

		for (unsigned i = 0; i < Level["FontFilesPath"].Size(); i++)	//Loop through the Serialisation Array
		{
			std::string filePath = Level["FontFilesPath"][i].GetString();
			//size_t namesize = filePath.find_last_of(".ttf") - 4 - filePath.find_last_of("\\/");
			std::string fileName = filePath.substr(filePath.find_last_of("\\/") + 1);
			FontResourceList.insert(std::pair<std::string, std::string>(fileName, filePath));
		}
		MyResourceManager.AddFontResourceList(FontResourceList);
	}
#endif

	//Create and Serialise TileMaps
	//if (Level.HasMember("AllTileMaps"))
	//{
	//	for (rapidjson::SizeType i = 0; i < Level["AllTileMaps"].Size(); i++)
	//	{
	//		Serialiser tileMapInfo(Level["AllTileMaps"][i]);

	//		//rapidjson::Document tileMapDoc;
	//		//tileMapDoc.SetObject();
	//		//tileMapDoc.CopyFrom(Level["AllTileMaps"][i], tileMapDoc.GetAllocator());

	//		//rapidjson::StringBuffer buf;							//buffer -  to output from the Json Document
	//		//rapidjson::Writer<rapidjson::StringBuffer> writer(buf);	//Writer handler - that contains the stringbuffer
	//		//tileMapDoc.Accept(writer);									//Output as json text into stringbuffer via Writer
	//		//std::string json(buf.GetString(), buf.GetSize());		//convert stringbuffer to std::string
	//		//std::ofstream file("./Resources/TextFiles/States/test.json"); //open a file with the param name
	//		//file << json;							//Write std::string type into the file

	//		GameObject* tileMap = CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()["TileMap"]);
	//
	//		//TileMapComponent* tmCom = dynamic_cast<TileMapComponent*>(tileMap->GetComponent(ComponentId::TILEMAP_COMPONENT));
	//		//tmCom->SerialiseComponent(tileMapInfo);
	//		//TransformComponent* tfCom = dynamic_cast<TransformComponent*>(tileMap->GetComponent(ComponentId::CT_Transform));
	//		//tfCom->SerialiseComponent(tileMapInfo);
	//		tileMap->Serialise(tileMapInfo);
	//	}
	//}

	//Create dynamic clonables
	if (Level.HasMember("Objects"))
	{
		for (unsigned i = 0; i < Level["Objects"].Size(); i++)
		{
			Serialiser datafile(Level["Objects"][i]);

			std::string name = datafile["ObjectType"].GetString();
			//name += ".json";

			GameObject* tmp;
			if (GameObject* tmp2 = MyResourceManager.GetPrototypeResource(name))
			{
				tmp = CloneGameObject(tmp2);
			}
			else
			{
				tmp = CreateEmptyGameObject();
				//tmp->Serialise(datafile);
			}

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
	//		GameObject* tmp = CreateEmptyGameObject();
	//		tmp->Serialise(datafile);
	//	}
	//}


	for (auto& idcom : GetComponentMap(Identity))
	{
		IdentityComponent* com = (IdentityComponent*)idcom.second;
		if (!(com->ObjectType().compare("BackgroundMusic")))
		{
			AudioComponent * audcom = (AudioComponent*)(com->GetSibilingComponent(ComponentId::CT_Audio));
			//audcom->PlayBGM();
			if (!_currentScene.compare("MainMenu"))
			{
				audcom->PlayBGM("mainmenu");
			}
			else if (!_currentScene.compare("truelevel1"))
			{
				audcom->PlayBGM("level1");
			}
			else if (!_currentScene.compare("truelevel2"))
			{
				audcom->PlayBGM("level2");

			}
		}
	}
}


//For Level Editor Only
//!!!!!Should return bool to let Level editor know if the scene is successfully saved
void Factory::De_SerialiseLevel(std::string filename)
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

	//if (filename.find("Resources"))
	//{
	/*std::string fileName = filename.substr(filename.find_last_of("\\") + 1);
	filename = "./Resources/TextFiles/Scenes/Scenes\\" + fileName;*/
	//}


	DeSerialiser SceneFile(filename);



//------------------------------------------------------------------------------------------------------

	MyResourceManager.ClearAllResources();
	LoadSceneResource(); // reload all resource into resource manager


	typedef std::map<std::string, std::string> NamePath;
	typedef std::unordered_map<std::string, std::pair<std::string, std::string>> NamePairMap;

	//Deserialise Prototypes Resource
	{
		NamePath PrototypeResourcePathList = MyResourceManager.GetPrototypeList();
		rapidjson::Value PrototypesFilePaths;
		PrototypesFilePaths.SetArray();

		for (auto& prototypeName : PrototypeResourcePathList)
		{
			rapidjson::Value strVal;
			strVal.SetString(prototypeName.second.c_str(), prototypeName.second.length(), SceneFile.Allocator());
			PrototypesFilePaths.PushBack(strVal, SceneFile.Allocator());
		}
		//After Going thru the GameObjects list, the PrototypesFilePaths list is finalised
		SceneFile.AddMember("PrototypesFilePaths", PrototypesFilePaths);
	}

	//Deserialise Textures
	{
		NamePath TextureResourcePathList = MyResourceManager.GetTexture2DList();
		rapidjson::Value TextureFilePaths;
		TextureFilePaths.SetArray();

		for (auto& TextureName : TextureResourcePathList)
		{
			rapidjson::Value strVal;
			strVal.SetString(TextureName.second.c_str(), TextureName.second.length(), SceneFile.Allocator());
			TextureFilePaths.PushBack(strVal, SceneFile.Allocator());
		}
		SceneFile.AddMember("TexturesFilesPaths", TextureFilePaths);
	}

	//Deserialise ShaderTypes
	{
		NamePairMap ShaderResourcePathList = MyResourceManager.GetShaderList();
		rapidjson::Value ShaderFilePaths;
		ShaderFilePaths.SetArray();

		for (auto& ShaderName : ShaderResourcePathList)
		{
			rapidjson::Value shader;
			shader.SetArray();
			rapidjson::Value strVal;

			strVal.SetString(ShaderName.first.c_str(), ShaderName.first.length(), SceneFile.Allocator());
			shader.PushBack(strVal, SceneFile.Allocator());
			strVal.SetString(ShaderName.second.first.c_str(), ShaderName.second.first.length(), SceneFile.Allocator());
			shader.PushBack(strVal, SceneFile.Allocator());
			strVal.SetString(ShaderName.second.second.c_str(), ShaderName.second.second.length(), SceneFile.Allocator());
			shader.PushBack(strVal, SceneFile.Allocator());

			ShaderFilePaths.PushBack(shader, SceneFile.Allocator());
		}
		SceneFile.AddMember("ShaderFilesPaths", ShaderFilePaths);
	}

	//Deserialise AnimationDataFile
	{
		NamePath AnimationResourcePathList = MyResourceManager.GetAnimationList();
		rapidjson::Value AnimationFilePaths;
		AnimationFilePaths.SetArray();

		for (auto& AnimName : AnimationResourcePathList)
		{
			rapidjson::Value strVal;
			strVal.SetString(AnimName.second.c_str(), AnimName.second.length(), SceneFile.Allocator());
			AnimationFilePaths.PushBack(strVal, SceneFile.Allocator());
		}
		SceneFile.AddMember("AnimationDataFilesPaths", AnimationFilePaths);
	}


	//Deserialise AudioFiles - SFX
	{
		NamePath AudioResourcePathList = MyResourceManager.GetSoundList();
		rapidjson::Value AudioFilePaths;
		AudioFilePaths.SetArray();

		for (auto& AudioName : AudioResourcePathList)
		{
			rapidjson::Value strVal;
			strVal.SetString(AudioName.second.c_str(), AudioName.second.length(), SceneFile.Allocator());
			AudioFilePaths.PushBack(strVal, SceneFile.Allocator());
		}
		SceneFile.AddMember("AudioSFXFilesPaths", AudioFilePaths);
	}

	//Deserialise AudioFiles - BGM
	{
		NamePath AudioResourcePathList = MyResourceManager.GetLoopSoundList();
		rapidjson::Value AudioFilePaths;
		AudioFilePaths.SetArray();

		for (auto& AudioName : AudioResourcePathList)
		{
			rapidjson::Value strVal;
			strVal.SetString(AudioName.second.c_str(), AudioName.second.length(), SceneFile.Allocator());
			AudioFilePaths.PushBack(strVal, SceneFile.Allocator());
		}
		SceneFile.AddMember("AudioBGMFilesPaths", AudioFilePaths);
	}


	//Deserialise Font Used
	{
		NamePath FontResourcePathList = MyResourceManager.GetFontList();
		rapidjson::Value FontFilePaths;
		FontFilePaths.SetArray();

		for (auto& FontName : FontResourcePathList)
		{
			rapidjson::Value strVal;
			strVal.SetString(FontName.second.c_str(), FontName.second.length(), SceneFile.Allocator());
			FontFilePaths.PushBack(strVal, SceneFile.Allocator());
		}
		SceneFile.AddMember("FontFilesPath", FontFilePaths);
	}
//-------------------------------------------------------------------------------------------------------------------------

	//rapidjson::Value clonableObjects;
	//clonableObjects.SetArray();

	rapidjson::Value nonClonableObjects;
	nonClonableObjects.SetArray();

	for (auto& objects : _gameObjectIdMap)
	{
		//IdentityComponent* comp = dynamic_cast<IdentityComponent*>(IdIdcomPair.second);

		//GameObject* GameObj = comp->GetParentPtr();
		//std::unordered_map <ComponentId, IComponent* > comList; //list of componenets

		//if (comp->GetParentPtr()->GetIndependent()) //Dont have any Parent
			//comList = _gameObjectIdMap[IdIdcomPair.first]->GetComponentList();
		//else
		//	comList = _childGameObjectIdMap[IdIdcomPair.first]->GetComponentList();

		rapidjson::Value obj;
		obj.SetObject();


		objects.second->DeSerialise(obj, SceneFile.Allocator());


		nonClonableObjects.PushBack(obj, SceneFile.Allocator());
	}


	//SceneFile.AddMember("ClonableObjects", clonableObjects);
	SceneFile.AddMember("Objects", nonClonableObjects);


	size_t namesize = filename.find_last_of(".json") - 5 - filename.find_last_of("\\/");
	std::string file = filename.substr(filename.find_last_of("\\/") + 1, namesize);


	//Returns false if scene already exists
	MyResourceSystem.AddNewScene(std::pair < std::string, std::string>(file, filename));
	SceneFile.ProduceJsonFile();
	_currentScene = file;


	//rapidjson::Value gameobjects;
	//gameobjects.SetArray();
	//
	//for (auto& obj : _gameObjectIdMap)
	//{
	// rapidjson::Value gameobject;
	// gameobject.SetObject();
	//
	// DeSerialiseGameObject(obj.second, gameobject, SceneFile.GetAllocator());
	//
	// gameobjects.PushBack(gameobject, SceneFile.Allocator());
	//}
	//
	//SceneFile.AddMember("GameObjects", gameobjects);
	//
	//size_t namesize = filename.find_last_of(".json") - 5 - filename.find_last_of("\\/");
	//std::string file = filename.substr(filename.find_last_of("\\/") + 1, namesize);
	//
	//
	////Returns false if scene already exists
	//MyResourceSystem.AddNewScene(std::pair < std::string, std::string>(file, filename));
	//SceneFile.ProduceJsonFile();
	//_currentScene = file;


}


//void Factory::DeSerialiseGameObject(GameObject* parent, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
//{
//	IdentityComponent* comp = GetComponentObject(parent, Identity);
//	GameObject* proObj = MyResourceSystem.GetPrototypeResource(comp->ObjectType());
//
//	std::unordered_map <ComponentId, IComponent* >& comList = parent->GetComponentList();
//
//	if (proObj)
//	{
//		value.AddMember("ClonableObjects", true, allocator);
//
//		std::unordered_map <ComponentId, IComponent* >& protoComList = proObj->GetComponentList();
//
//		for (auto& protoComPair : protoComList)
//		{
//			//If the clonable object does not have a certain component from the Prototype.
//			if (comList.find(protoComPair.first) == comList.end())
//			{
//				rapidjson::Value obj;
//				obj.SetNull();
//				value.AddMember(rapidjson::StringRef(ToString(protoComPair.first)), obj, allocator);
//			}
//		}
//
//		for (auto& IdComPair : comList)
//		{
//			IComponent* protoCom = proObj->GetComponent(IdComPair.first);
//			IdComPair.second->DeserialiseComponentSceneFile(protoCom, value, allocator);
//		}
//	}
//	else  //Object does not exists in PrototypeAssetList - Save in NonClonableObjects list
//	{
//
//		for (auto& IdComPair : comList)
//		{
//			//IComponent* protoCom = proObj->GetComponent(IdComPair.first);
//			IdComPair.second->DeSerialiseComponent(value, allocator);
//		}
//	}
//
//	if (parent->GetChild())
//	{
//		rapidjson::Value childData;
//		childData.SetArray();
//
//		std::unordered_map <size_t, GameObject* >& childList = parent->GetChildList();
//
//		for (auto& child : childList)
//		{
//			rapidjson::Value obj;
//			obj.SetObject();
//
//			DeSerialiseGameObject(child.second, obj, allocator);
//
//			childData.PushBack(obj, allocator);
//		}
//
//		value.AddMember("ObjectHasChilds", childData, allocator);
//	}
//}

void Factory::WindowsDialogSaveLevel()
{
	OPENFILENAME ofn = { sizeof ofn };
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = _engineSystems._windowSystem->getWindow().Get_hwnd();

	char file[1024] = "\0";
	ofn.lpstrFile = file;
	ofn.nMaxFile = 1024;
	ofn.Flags = OFN_ALLOWMULTISELECT | OFN_EXPLORER | OFN_NOCHANGEDIR;

	ofn.lpstrFilter = ".json\0.json";
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = "./Resources/TextFiles/Scenes/Scenes";
	ofn.nFilterIndex = 1;
	ofn.lpstrTitle = TEXT("Save Scene File");
	ofn.lpstrDefExt = "rle";

	if (GetSaveFileName(&ofn)) //If the user specifies a file nameand clicks the OK buttonand the function is successful, the return value is nonzero.
	{
		std::cout << ofn.lpstrFile;

		std::string fileName = ofn.lpstrFile;	
		fileName = fileName.substr(fileName.find_last_of("\\") + 1);
		fileName = "./Resources/TextFiles/Scenes/Scenes\\" + fileName;
		De_SerialiseLevel(fileName);
	}
}

void Factory::ClearLevel()
{
	for (auto it : _gameObjectIdMap)
		delete it.second;
	_gameObjectIdMap.clear();

	for (auto it : _childGameObjectIdMap)
		delete it.second;
	_childGameObjectIdMap.clear();

	_allExistGameObjectList.clear();

	_objectsToBeDeleted.clear();

	_objectLinkMap.clear();

	MyComponentManger.ClearAllComponents();

	MyResourceManager.ClearAllResources();
}

void Factory::AddNewPrototypeAsset(GameObject* NewPrototype, std::string filePath)
{
	//if (filePath.find("Resources"))
	//{
		//std::string fileName = filePath.substr(filePath.find("Resources") + 9);
		//filePath = "./Resources" + fileName;
		//
		std::string fileName = filePath.substr(filePath.find_last_of("\\") + 1);
		filePath = "./Resources/TextFiles/GameObjects\\" + fileName;
	//}

	DeSerialiser document(filePath); //Create a deserialiser file

	NewPrototype->DeSerialise(document);	//Deserialise prototype into a .json File

	//Add Prototype Resource to editor Prototype List 
	IdentityComponent* IdCom = dynamic_cast<IdentityComponent*>(NewPrototype->GetComponent(ComponentId::CT_Identity));
	MyResourceSystem.GetPrototypeMap().insert(std::pair <std::string, GameObject*>(IdCom->ObjectType(), NewPrototype));
	MyResourceSystem.GetPrototypeList().insert(std::pair<std::string, std::string>(IdCom->ObjectType(), filePath));

	document.ProduceJsonFile(); //Produce Prototype Json file
}


///////////////////////////////////////////////////////////////////////////

void Factory::UpdateScene()
{
	if (_currentScene.compare(_prevScene) == 0 || 
		_currentScene.compare("Quit") == 0 || _currentScene.compare("quit") == 0 || _currentScene.compare("") == 0)
		return;

	if (_currentScene.compare("Restart") == 0 || _currentScene.compare("restart") == 0)
		_currentScene = _prevScene;

	_prevScene = _currentScene;
	_lastGameObjectId = 0;


	MyFactory.ClearLevel();
	MyFactory.SerialiseLevel(MyResourceSystem.GetSceneList()[_currentScene]);

	InitScene();
}

void Factory::InitScene()
{
	for (auto& it : GetComponentMap(Identity))
		if(it.first != 0)
			it.second->Init();

	for (auto& it : _gameObjectIdMap)
	{
		TransformComponent* obj = GetComponentObject(it.second, Transform);

		if (obj)
			obj->Init();
	}

	for (auto& it : GetComponentMap(Graphic))
		if (it.first != 0)
			it.second->Init();

	for (auto& it : GetComponentMap(Animation))
		if (it.first != 0)
			it.second->Init();

	for (auto& it : GetComponentMap(Camera))
		if (it.first != 0)
			it.second->Init();

	for (auto& it : GetComponentMap(Font)) // not done
		if (it.first != 0)
			it.second->Init();

	/*for (auto& it : GetComponentMap(RigidBody2D))
		it.second->Init();

	for (auto& it : GetComponentMap(CircleCollider2D))
		it.second->Init();

	for (auto& it : GetComponentMap(BoxCollider2D))
		it.second->Init();

	for (auto& it : GetComponentMap(EdgeCollider2D))
		it.second->Init();*/

	for (auto& it : GetComponentMap(Audio))
		if (it.first != 0)
			it.second->Init();

	for (auto& it : GetComponentMap(Button))
		if (it.first != 0)
			it.second->Init();

	for (auto& it : GetComponentMap(UI))
		if (it.first != 0)
			it.second->Init();

	for (auto& it : GetComponentMap(TileMap))
		if (it.first != 0)
			it.second->Init();


	MyCameraSystem.Init();
	MyGraphicsSystem.Init();
	MyLogicSystem.Init();
}

void Factory::LoadSceneResource()
{
	for (auto& it : GetComponentMap(Identity))
		if (it.first != 0)
			it.second->LoadResource();

	/*for (auto& it : GetComponentMap(Transform))
		if (it.first != 0)
			it.second->Init();*/

	for (auto& it : GetComponentMap(Graphic))
		if (it.first != 0)
			it.second->LoadResource();

	for (auto& it : GetComponentMap(Animation))
		if (it.first != 0)
			it.second->LoadResource();

	/*for (auto& it : GetComponentMap(Camera))
		if (it.first != 0)
			it.second->LoadResource();*/

	for (auto& it : GetComponentMap(Font)) // not done
		if (it.first != 0)
			it.second->LoadResource();

	/*for (auto& it : GetComponentMap(RigidBody2D))
		it.second->LoadResource();

	for (auto& it : GetComponentMap(CircleCollider2D))
		it.second->LoadResource();

	for (auto& it : GetComponentMap(BoxCollider2D))
		it.second->LoadResource();

	for (auto& it : GetComponentMap(EdgeCollider2D))
		it.second->LoadResource();*/

	for (auto& it : GetComponentMap(Audio))
		if (it.first != 0)
			it.second->LoadResource();

	for (auto& it : GetComponentMap(Button))
		if (it.first != 0)
			it.second->LoadResource();

	for (auto& it : GetComponentMap(UI))
		if (it.first != 0)
			it.second->LoadResource();

	//for (auto& it : GetComponentMap(TileMap))
	//	if (it.first != 0)
	//		it.second->LoadResource();

	MyGraphicsSystem.LoadResource();
	MyLogicSystem.LoadResource();

	for (auto& it : MyResourceManager.GetPrototypeMap())
		it.second->LoadResource();
}



void Factory::ChangeScene(const std::string& scene)
{
	if (_currentScene.compare(scene) == 0)
		return;

	_prevScene = _currentScene;

	if (scene.compare("Quit") == 0 || scene.compare("quit") == 0 ||
		scene.compare("Restart") == 0 || scene.compare("restart") == 0)
	{
		_currentScene = scene;
		return;
	}

	if (MyResourceSystem.GetSceneList().find(scene) != MyResourceSystem.GetSceneList().end())
	{
		_currentScene = scene;
		return;
	}
	else
	{
		throw(0);
	}
	//if (scene.compare("Level1") == 0)
	//	EngineSystems::GetInstance()._aiSystem->CreateNodeMapFromTileComp();
}

void Factory::SaveBackUpScene()
{
	_currEditerScene = _currentScene;
	_currentScene = "BackUp";
	_prevScene = _currentScene;

	MyFactory.De_SerialiseLevel(MyResourceSystem.GeScenePath(_currentScene));
}

void Factory::LoadBackUpScene()
{
	if (!_currentScene.compare("BackUp"))
		_currentScene = "Restart";
	else
		_currentScene = "BackUp";

	UpdateScene();
	_currentScene = _currEditerScene;
	_prevScene = _currentScene;
}

//For GamePlay 
std::string Factory::SerialiseScenes(Serialiser& GameSceneFile)
{
	if (GameSceneFile.HasMember("GameScenes"))
	{
		for (unsigned i = 0; i < GameSceneFile["GameScenes"].Size(); i++)
		{
			std::string filePath = GameSceneFile["GameScenes"][i].GetString();
			size_t namesize = filePath.find_last_of(".json") - 5 - filePath.find_last_of("\\/");
			std::string fileName = filePath.substr(filePath.find_last_of("\\/") + 1, namesize);
			MyResourceManager.AddNewScene(std::pair<std::string, std::string>(fileName, filePath));
		}
	}

	if (GameSceneFile.HasMember("StartingScenes") && GameSceneFile["StartingScenes"].IsString())
		return GameSceneFile["StartingScenes"].GetString();

	return "Quit";
}

//For Level Editor
void Factory::LoadAllSceneAssets(std::unordered_map<std::string, std::string>& GameSceneFile)
{
	MyResourceSystem.AddSceneList(GameSceneFile);
}

const std::string& Factory::GetCurrentScene()
{
	return _currentScene;
}

void Factory::SetNewScene() 
{
	_lastGameObjectId = 0;
	_currentScene = "";
	MyFactory.ClearLevel();
}

std::unordered_map<std::string, ComponentCreator*>& Factory::GetComponentList()
{
	return _componentMap;
}

void Factory::SaveNewLinkID(int Id, size_t objectUId)
{
	_objectLinkMap.insert({ Id,objectUId });
}

GameObject* Factory::GetLinkIDObject(int Id)
{
	if (!Id)
		return nullptr;

	if (_objectLinkMap.find(Id) != _objectLinkMap.end())
	{
		if (_gameObjectIdMap.find(_objectLinkMap[Id]) != _gameObjectIdMap.end())
			return _gameObjectIdMap[_objectLinkMap[Id]];
		else if (_childGameObjectIdMap.find(_objectLinkMap[Id]) != _childGameObjectIdMap.end())
			return _childGameObjectIdMap[_objectLinkMap[Id]];
	}

	return nullptr;
}

GameObject* Factory::CloneAndInitPrototype(std::string name)
{
	GameObject* prototypeObj = MyResourceSystem.GetPrototypeMap()[name];

	if (!prototypeObj)
		return nullptr;

	GameObject* obj = CloneGameObject(prototypeObj);

	if (obj)
		obj->Init();

	return obj;
}

void Factory::SwapChildToParent(size_t UId)
{
	if (_childGameObjectIdMap.find(UId) == _childGameObjectIdMap.end())
		return;

	_gameObjectIdMap.insert({ UId, _childGameObjectIdMap[UId] });
	_childGameObjectIdMap.erase(UId);
}

void Factory::SwapParentToChild(size_t UId)
{
	if (_gameObjectIdMap.find(UId) == _gameObjectIdMap.end())
		return;

	_childGameObjectIdMap.insert({ UId, _gameObjectIdMap[UId] });
	_gameObjectIdMap.erase(UId);
}