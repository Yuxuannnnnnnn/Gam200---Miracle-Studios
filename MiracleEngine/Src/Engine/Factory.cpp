#include "PrecompiledHeaders.h"
#include "Factory.h"

Factory::Factory() : 
	_lastGameObjectId{0}
{
}

Factory::~Factory()
{
	//Delete all component creators
	for (auto& itr : _componentMap)
		delete itr.second;

	_componentMap.clear();
}

GameObject* Factory::BuildAndSerialize(const std::string& filename)
{
	(void)filename;
	return nullptr;
}

GameObject* Factory::CloneGameObject(GameObject* gameobject)
{
	GameObject* clonedObject = gameobject->Clone(++_lastGameObjectId);
	_gameObjectIdMap.insert({ clonedObject->Get_uID(),clonedObject });

	return clonedObject;
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

	std::unordered_set<GameObject*>::iterator it = _objectsToBeDeleted.begin();
	for (; it != _objectsToBeDeleted.end(); ++it)
	{
		GameObject* gameObject = *it;
		GameObjectIdMapType::iterator idItr = _gameObjectIdMap.find(gameObject->Get_uID());
		//ErrorIf(idItr == _gameObjectIdMap.end(), "Object %d was double deleted or is bad memory.", gameObject->ObjectId);
		if (idItr != _gameObjectIdMap.end())
		{
			//Delete it and remove its entry in the Id map
			delete gameObject;
			_gameObjectIdMap.erase(idItr);
		}
	}
	//All objects to be delete have been deleted
	_objectsToBeDeleted.clear();
}

void Factory::DestroyAll()
{
	for (auto& it : _gameObjectIdMap)
		_objectsToBeDeleted.insert(it.second);
}

GameObject* Factory::CreateEmptyGameObject()
{
	GameObject* gameObject = new GameObject(++_lastGameObjectId);

	_gameObjectIdMap.insert({ gameObject->Get_uID(),gameObject });

	return gameObject;
}

GameObject* Factory::CreateEmptyChildGameObject()
{
	GameObject* gameObject = new GameObject(++_lastGameObjectId);

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

bool Factory::CheckObjOrignialPointer(GameObject* obj)
{
	for (auto& pair : _gameObjectIdMap)
	{
		if (pair.second == obj)
			return true;
	}


	auto& prototypeList = MyResourceSystem.GetPrototypeMap();
	for (auto& pair : prototypeList)
	{
		if (pair.second == obj)
			return true;
	}
	
	return false;
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
			size_t namesize = filePath.find_last_of(".json") - 4 - filePath.find_last_of("\\/");
			std::string fileName = filePath.substr(filePath.find_last_of("\\/") + 1, namesize);
			ResourceList1.insert(std::pair<std::string, std::string>(fileName, filePath));
		}
		MyFactory.SerialiseAllPrefabAssets(ResourceList1);
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
		MyResourceSystem.AddTexture2DResourceList(ResourceList);
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
		MyResourceSystem.AddAnimationResourceList(ResourceList);
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
		MyResourceSystem.AddAudioResourceList(ResourceList);
		ResourceList.clear();
	}

	typedef std::pair<std::string, std::string> VertFrag;
	std::unordered_map<std::string, VertFrag> ShaderResource;

	VertFrag vertFrag;

	if (Level.HasMember("ShaderFilesPaths"))
	{
		for (unsigned i = 0; i < Level["ShaderFilesPaths"].Size(); i++)	//Loop through the Serialisation Array
		{
			std::string filePath = Level["ShaderFilesPaths"][i].GetString();
			std::string fileName = "";
			if (filePath.find(".vert") != std::string::npos)
			{
				size_t namesize = filePath.find_last_of(".vert") - 5 - filePath.find_last_of("\\/");
				fileName = filePath.substr(filePath.find_last_of("\\/") + 1, namesize);
				vertFrag.first = filePath;
				ShaderResource.insert(std::pair<std::string, VertFrag>(fileName, vertFrag));
			}
			else if (filePath.find(".frag") != std::string::npos)
			{
				//size_t namesize = filePath.find_last_of(".frag") - 5 - filePath.find_last_of("\\/");
				//fileName = filePath.substr(filePath.find_last_of("\\/") + 1);
				vertFrag.second = filePath;
			}
		}
		MyResourceSystem.AddShaderResourceList(ShaderResource);
		ShaderResource.clear();
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
		MyResourceSystem.AddFontResourceList(ResourceList);
		ResourceList.clear();
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
	if (Level.HasMember("ClonableObjects"))
	{
		for (unsigned i = 0; i < Level["ClonableObjects"].Size(); i++)
		{
			Serialiser datafile(Level["ClonableObjects"][i]);

			std::string name = datafile["ObjectType"].GetString();
			//name += ".json";
			GameObject* tmp2 = MyResourceSystem.GetPrototypeResource(name);
			GameObject* tmp = CloneGameObject(tmp2);

			tmp->Serialise(datafile);
		}
	}

	//Create dynamic non-clonables
	if (Level.HasMember("NonClonableObjects"))
	{
		for (unsigned i = 0; i < Level["NonClonableObjects"].Size(); i++)
		{
			Serialiser datafile(Level["NonClonableObjects"][i]);

			GameObject* tmp = CreateEmptyGameObject();
			tmp->Serialise(datafile);
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
	std::string fileName = filename.substr(filename.find_last_of("\\") + 1);
	filename = "./Resources/TextFiles/Scenes/Scenes\\" + fileName;
	//}


	DeSerialiser SceneFile(filename);

	//Deserialise Prototypes Resource
	//- Check through the Identity Components of all Objects
	//- The ObjectType in the IdentityComponent will be used to save a Prototype
	//= Get the Prototype file Path from the PrototypeList

	typedef std::map<std::string, std::string> NamePath;
	NamePath PrototypeResourcePathList;
	rapidjson::Value PrototypesFilePaths;
	PrototypesFilePaths.SetArray();


	for (auto& IdComPair : GetComponentMap(Identity))
	{
		std::string ObjType = ((IdentityComponent*)IdComPair.second)->ObjectType();
		//ObjType += ".json";
		//Object exists in PrototypeAssetList - Save in ClonableObjects list
		bool add = true;

		if (MyResourceSystem.GetPrototypeResource(ObjType))
		{
			// PrototypeResourceList does not have the prototype yet 
			for(auto& string: PrototypeResourcePathList)
			{
				if (!string.first.compare(ObjType))
				{
					add = false;
					break;
				}
			}

			if (add)
			{
				std::string FilePath = MyResourceSystem.GetPrototypeResourcePath(ObjType);
				if (!FilePath.empty())
				{
					PrototypeResourcePathList.insert(std::pair<std::string, std::string>(ObjType, FilePath));
				}
			}

		}
	}

	for (auto& prototypeName : PrototypeResourcePathList)
	{
		rapidjson::Value strVal;
		strVal.SetString(prototypeName.second.c_str(), prototypeName.second.length(), SceneFile.Allocator());
		PrototypesFilePaths.PushBack(strVal, SceneFile.Allocator());
	}
	//After Going thru the GameObjects list, the PrototypesFilePaths list is finalised
	SceneFile.AddMember("PrototypesFilePaths", PrototypesFilePaths);



	//Deserialise ShaderTypes
	//- check through the Graphic Component for the Shader Name used
	//- Get File Path of both the vertex and fragment Shader Used

	//Deserialise Texture Resource
	//- Check through all the graphic Component for the texture File Name
	//- Get the File path of the textures from the Resource Manager

	NamePath TextureResourcePathList;
	rapidjson::Value TextureFilePaths;
	TextureFilePaths.SetArray();

	NamePath ShaderResourcePathList;
	rapidjson::Value ShaderFilePaths;
	ShaderFilePaths.SetArray();

	for (auto& IdGrapPair : GetComponentMap(Graphic))
	{

		bool add = true;

		std::string TextureFile = ((GraphicComponent*)IdGrapPair.second)->GetFileName();

		if (MyResourceSystem.GetTexture2DResource(TextureFile))
		{
			// TextureResourcePathList does not have the texture yet 
			for (auto& string : TextureResourcePathList)
			{
				if (!string.first.compare(TextureFile))
				{
					add = false;
					break;
				}
			}

			if (add)
			{
				std::string FilePath = MyResourceSystem.GetTexture2DResourcePath(TextureFile);
				if (!FilePath.empty())
				{
					TextureResourcePathList.insert(std::pair<std::string, std::string>(TextureFile, FilePath));
				}
			}
		}

		add = true;

		std::string ShaderFile = ((GraphicComponent*)IdGrapPair.second)->GetShaderType();

		if (MyResourceSystem.GetShaderResource(ShaderFile))
		{
			// ShaderResourcePathList does not have the shader yet 
			for (auto& string : ShaderResourcePathList)
			{
				if (!string.first.compare(ShaderFile))
				{
					add = false;
					break;
				}
			}

			if (add)
			{
				VertFrag vertfrag = MyResourceSystem.GetShaderResourcePath(ShaderFile);
				if (!vertfrag.first.empty())
				{
					ShaderResourcePathList.insert(std::pair<std::string, std::string>(ShaderFile, vertfrag.second));
					ShaderResourcePathList.insert(std::pair<std::string, std::string>(ShaderFile, vertfrag.first));
				}
			}
		}
	}

	for (auto& TextureName : TextureResourcePathList)
	{
		rapidjson::Value strVal;
		strVal.SetString(TextureName.second.c_str(), TextureName.second.length(), SceneFile.Allocator());
		TextureFilePaths.PushBack(strVal, SceneFile.Allocator());
	}
	SceneFile.AddMember("TexturesFilesPaths", TextureFilePaths);

	for (auto& ShaderName : ShaderResourcePathList)
	{
		rapidjson::Value strVal;
		strVal.SetString(ShaderName.second.c_str(), ShaderName.second.length(), SceneFile.Allocator());
		ShaderFilePaths.PushBack(strVal, SceneFile.Allocator());
	}
	SceneFile.AddMember("ShaderFilesPaths", ShaderFilePaths);



	//Deserialise AnimationDataFile
	//- Check through all the animation components for the animationdatafile names
	//- Get file Path of the animationDataFile from the Resource Manager

	NamePath AnimationResourcePathList;
	rapidjson::Value AnimationFilePaths;
	AnimationFilePaths.SetArray();

	for (auto& IdAnimPair : GetComponentMap(Animation))
	{
		const std::map<std::string, float>& AnimFileList = ((AnimationComponent*)IdAnimPair.second)->GetAnimationDataFileList();

		for (auto& animFile : AnimFileList)
		{
			bool add = true;

			if (MyResourceSystem.GetAnimationResource(animFile.first))
			{
				// AnimationResourcePathList does not have the aniamation yet 
				for (auto& string : AnimationResourcePathList)
				{
					if (!string.first.compare(animFile.first))
					{
						add = false;
						break;
					}
				}

				if (add)
				{
					std::string FilePath = MyResourceSystem.GetAnimationResourcePath(animFile.first);
					if(!FilePath.empty())
						AnimationResourcePathList.insert(std::pair<std::string, std::string>(animFile.first, FilePath));
				}
			}
		}
	}

	for (auto& AnimName : AnimationResourcePathList)
	{
		rapidjson::Value strVal;
		strVal.SetString(AnimName.second.c_str(), AnimName.second.length(), SceneFile.Allocator());
		AnimationFilePaths.PushBack(strVal, SceneFile.Allocator());
	}
	SceneFile.AddMember("AnimationDataFilesPaths", AnimationFilePaths);



	//Deserialise AudioFiles
	//- Check throught the AudioComponents to get audio file name
	//- Get the File path of the audiofile from the Resource Manager
	NamePath AudioResourcePathList;
	rapidjson::Value AudioFilePaths;
	AudioFilePaths.SetArray();

	for (auto& IdAudioPair : GetComponentMap(Audio))
	{
		std::string audioFile = ((AudioComponent*)IdAudioPair.second)->GetFileName();

		bool add = true;

		if (MyResourceSystem.GetSoundResource(audioFile))
		{
			// AudioResourcePathList does not have the audio yet 
			for (auto& string : AudioResourcePathList)
			{
				if (!string.first.compare(audioFile))
				{
					add = false;
					break;
				}
			}

			if (add)
			{
				std::string FilePath = MyResourceSystem.GetSoundResourcePath(audioFile);
				if (!FilePath.empty())
					AudioResourcePathList.insert(std::pair<std::string, std::string>(audioFile, FilePath));
			}
	
		}
	}

	for (auto& AudioName : AudioResourcePathList)
	{
		rapidjson::Value strVal;
		strVal.SetString(AudioName.second.c_str(), AudioName.second.length(), SceneFile.Allocator());
		AudioFilePaths.PushBack(strVal, SceneFile.Allocator());
	}
	SceneFile.AddMember("AudioFilesPaths", AudioFilePaths);



	//Deserialise Font Used
	//- Check throught the Font Component for the font type used
	//- Get the File path of the Fontfile from the Resource Manager
	NamePath FontResourcePathList;
	rapidjson::Value FontFilePaths;
	FontFilePaths.SetArray();

	for (auto& IdFontPair : GetComponentMap(Font))
	{
		std::string fontFile = ((FontComponent*)IdFontPair.second)->GetFontType();

		bool add = true;

		if (MyResourceSystem.GetFontResource(fontFile))
		{
			// AudioResourcePathList does not have the audio yet 
			for (auto& string : FontResourcePathList)
			{
				if (!string.first.compare(fontFile))
				{
					add = false;
					break;
				}
			}

			if (add)
			{
				std::string FilePath = MyResourceSystem.GetFontResourcePath(fontFile);
				FontResourcePathList.insert(std::pair<std::string, std::string>(fontFile, FilePath));
			}
		}
	}

	for (auto& FontName : FontResourcePathList)
	{
		rapidjson::Value strVal;
		strVal.SetString(FontName.second.c_str(), FontName.second.length(), SceneFile.Allocator());
		FontFilePaths.PushBack(strVal, SceneFile.Allocator());
	}
	SceneFile.AddMember("FontFilesPath", FontFilePaths);



	rapidjson::Value clonableObjects;
	clonableObjects.SetArray();

	rapidjson::Value nonClonableObjects;
	nonClonableObjects.SetArray();

	for (auto& IdIdcomPair : GetComponentMap(Identity))
	{
		const size_t id = IdIdcomPair.first;
		std::string ObjType = ((IdentityComponent*)IdIdcomPair.second)->ObjectType();


		rapidjson::Value obj;
		obj.SetObject();
		GameObject* proObj = nullptr;
		//Object exists in PrototypeAssetList - Save in ClonableObjects list
		if (proObj = MyResourceSystem.GetPrototypeResource(ObjType))
		{
			std::unordered_map <ComponentId, IComponent* >& comList = _gameObjectIdMap[id]->GetComponentList();

			for (auto& IdComPair : comList)
			{
				IComponent* protoCom = proObj->GetComponent(IdComPair.first);
				IdComPair.second->DeserialiseComponentSceneFile(protoCom, obj, SceneFile.GetAllocator());
			}
			clonableObjects.PushBack(obj, SceneFile.Allocator());

		}
		else  //Object does not exists in PrototypeAssetList - Save in NonClonableObjects list
		{
			std::unordered_map <ComponentId, IComponent* >& comList = _gameObjectIdMap[id]->GetComponentList();

			for (auto& IdComPair : comList)
			{
				//IComponent* protoCom = proObj->GetComponent(IdComPair.first);
				IdComPair.second->DeSerialiseComponent(obj, SceneFile.GetAllocator());
			}

			nonClonableObjects.PushBack(obj, SceneFile.Allocator());

		}
	}


	SceneFile.AddMember("ClonableObjects", clonableObjects);
	SceneFile.AddMember("NonClonableObjects", nonClonableObjects);


	size_t namesize = filename.find_last_of(".json") - 5 - filename.find_last_of("\\");
	std::string file = filename.substr(filename.find_last_of("\\/") + 1, namesize);


	//Returns false if scene already exists
	MyResourceSystem.AddNewScene(std::pair < std::string, std::string>(file, filename));
	SceneFile.ProduceJsonFile();

}

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
		De_SerialiseLevel(ofn.lpstrFile);
	}
}

void Factory::DeleteLevel()
{
	MyResourceManager.ClearAllResources();

	DeleteLevelNotPrefab();
}

void Factory::DeleteLevelNotPrefab()
{
	for (auto it : _gameObjectIdMap)
		delete it.second;
	_gameObjectIdMap.clear();

	MyComponentManger.ClearAllComponents();
}

//For GamePlay 
//void Factory::SerialPrefabObjects(Serialiser& Level)
//{
//	if (Level.HasMember("PrototypesFilePaths"))
//	{
//		for (unsigned i = 0; i < Level["PrototypesFilePaths"].Size(); i++)	//Loop through the Serialisation Array
//		{
//			std::string path = Level["PrototypesFilePaths"][i].GetString();
//			GameObject* temp = new GameObject(0);
//			temp->Serialise(path);	//Serialise a gameobject with the string
//
//			std::string typeId = (dynamic_cast<IdentityComponent*>(temp->GetComponent(ComponentId::IDENTITY_COMPONENT)))->ObjectType();
//			//insert into the prototype list
//			_prototypeNameMap.insert(std::pair <std::string, GameObject*>(typeId, temp));
//
//			_prototypeFileList.insert(std::pair<std::string, std::string>(typeId, path));
//			//temp->Set_typeId((TypeIdGO)typeId); //Set GameObjectType inside GameObject
//
//		}
//	}
//}

void Factory::SerialiseAllPrefabAssets(std::unordered_map<std::string, std::string>& list)
{
	MyResourceSystem.AddPrototypeResourceList(list);

	////Serialise all Prototypesu8
	//for (auto& nameFile : MyResourceSystem.GetPrototypeList())
	//{
	//	GameObject* temp = new GameObject();
	//	Serialiser FilePath(nameFile.second);

	//	temp->Serialise(FilePath);	//Serialise a gameobject with fileName

	//	//insert into the prototype list
	//	MyResourceSystem.GetPrototypeMap().insert(std::pair <std::string, GameObject*>(nameFile.first, temp));
	//}
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

	NewPrototype->DeSerialise(filePath);	//Deserialise prototype into a .json File

	//Add Prototype Resource to editor Prototype List 
	IdentityComponent* IdCom = dynamic_cast<IdentityComponent*>(NewPrototype->GetComponent(ComponentId::CT_Identity));
	MyResourceSystem.GetPrototypeMap().insert(std::pair <std::string, GameObject*>(IdCom->ObjectType(), NewPrototype));
	MyResourceSystem.GetPrototypeList().insert(std::pair<std::string, std::string>(IdCom->ObjectType(), filePath));
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

#ifdef LEVELEDITOR //for Level editor Mode
	MyFactory.DeleteLevelNotPrefab();
	MyFactory.SerialiseLevel(MyResourceSystem.GetSceneList()[_currentScene]);

#else	//for GamePlay mode
	MyFactory.DeleteLevel();
	MyFactory.SerialiseLevel(MyResourceManager.GetSceneList()[_currentScene]);
#endif


	MyCameraSystem.Init();
}

void Factory::ChangeScene(const std::string& scene)
{
	_prevScene = _currentScene;

	if (scene.compare("Quit") == 0 || scene.compare("quit") == 0 ||
		scene.compare("Restart") == 0 || scene.compare("restart") == 0)
	{
		_currentScene = scene;
		return;
	}

#ifdef LEVELEDITOR //for Level editor Mode
	if (MyResourceSystem.GetSceneList().find(scene) != MyResourceSystem.GetSceneList().end())
#else	//for GamePlay mode
	if (MyResourceManager.GetSceneList().find(scene) != MyResourceManager.GetSceneList().end())
#endif
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

//For GamePlay 
void Factory::SerialiseScenes(Serialiser GameSceneFile)
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
	DeleteLevelNotPrefab();
}

std::unordered_map<std::string, ComponentCreator*>& Factory::GetComponentList()
{
	return _componentMap;
}