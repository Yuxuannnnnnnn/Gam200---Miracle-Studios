#pragma once
#include <unordered_map>
#include <unordered_set>
#include "GameObject/GameObject.h"
#include "GameObject/ComponentCreator.h"

///Forward Declaration of Component Creator
class ComponentCreator;

class Factory
{
public:
	Factory();
	~Factory();

	Factory(const Factory& rhs) = delete;
	Factory& operator= (const Factory& rhs) = delete;

	///Build a GameObject and serialize from the data file but do not initialize the GameObject.
	///Used to create a GameObject and then adjust its data before initialization
	GameObject* BuildAndSerialize(const std::string& filename);

	///Create initialize and Id a GOC from the data file.
	GameObject* CloneGameObject(GameObject* gameobject);

	///Add a GOC to the destroy list for delayed destruction.
	void Destroy(GameObject* gameObject);

	///Update the factory, destroying dead objects.
	void Update(float dt);

	///Destroy all the GOCs in the world. Used for final shutdown.
	void DestroyAll();

	///Create and Id a GOC at runtime. Used to dynamically build GOC.
	///After components have been added call GOC->Initialize().
	GameObject* CreateEmptyGameObject();

	IComponent* CreateEmptyComponent(const std::string& name);

	///Add a component creator enabling data driven composition
	void AddComponentCreator(const std::string& name, ComponentCreator* creator);

	///Get the game object with given id. This function will return NULL if
	///the object has been destroyed.
	GameObject* GetObjectWithId(size_t id);

	////////////////////////////////////////////////////////////////////////

	bool CheckObjOrignialPointer(GameObject* obj);

	std::unordered_map<size_t, GameObject*>& getObjectlist();

	void SerialiseLevel(std::string FileName);		//Read LevelText and Instantiate GObj //Level is read when NextGameState is In-GameState
	void DeleteLevel();								//Level is Deleted when out of In-GameState
	void DeleteLevelNotPrefab();
	void De_SerialiseLevel(std::string filename);


	////////////////////////////////////////////////////////////////////////////

	//Gameplay mode
	//void SerialPrefabObjects(Serialiser& Level);

	//LevelEditor mode
	void SerialiseAllPrefabAssets(std::unordered_map<std::string, std::string>& list);

	void AddNewPrototypeAsset(GameObject* NewPrototype, std::string filePath);

	///////////////////////////////////////////////////////////////////////////

	std::unordered_map<std::string, ComponentCreator*>& GetComponentList()
	{
		return _componentMap;
	}

	///////////////////////////////////////////////////////////////////////////

	void ChangeScene(const std::string& scene);

	//For GamePlay 
	void SerialiseScenes(Serialiser GameSceneFile);

	//For Level Editor
	void LoadAllSceneAssets(std::unordered_map<std::string, std::string>& GameSceneFile);

	const std::string& GetCurrentScene();

private:
	///Used to incrementally generate unique id's.
	unsigned _lastGameObjectId;

	///Map of component creator used for data driven composition
	typedef std::unordered_map<std::string, ComponentCreator*> ComponentMapType;
	ComponentMapType _componentMap;

	///Map of GameObject to their Ids used for safe referencing of game objects
	typedef std::unordered_map<size_t, GameObject*> GameObjectIdMapType;
	GameObjectIdMapType _gameObjectIdMap;

	///Objects to be deleted
	std::unordered_set<GameObject*> _objectsToBeDeleted;

	std::string _currentScene;
};

#define AddEmptyComponent(type) MyFactory->CreateEmptyComponent( #type );


/*


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

			GameObject* tmp = CreateNewGameObject(false);
			tmp->Serialise(datafile);
		}
	}

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
		//ObjType += ".json";
		//Object exists in PrototypeAssetList - Save in ClonableObjects list
		if (MyResourceSystem.GetPrototypeResource(ObjType))
		{
			// PrototypeResourceList does not have the prototype yet
			if ((std::find(PrototypeResourcePathList.begin(), PrototypeResourcePathList.end(), ObjType) == PrototypeResourcePathList.end()))
			{
				std::string FilePath = MyResourceSystem.GetPrototypeList()[ObjType];
				PrototypeResourcePathList.push_back(FilePath);
			}

		}
	}

	for (auto& prototypeName : PrototypeResourcePathList)
	{
		rapidjson::Value strVal;
		strVal.SetString(prototypeName.c_str(), prototypeName.length(), SceneFile.Allocator());
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
				VertFrag vertfrag = MyResourceManager.GetShaderResourcePath(TextureFile);
				ShaderResourcePathList.push_back(vertfrag.second);
				ShaderResourcePathList.push_back(vertfrag.first);
			}
		}
	}

	for (auto& TextureName : TextureResourcePathList)
	{
		rapidjson::Value strVal;
		strVal.SetString(TextureName.c_str(), TextureName.length(), SceneFile.Allocator());
		TextureFilePaths.PushBack(strVal, SceneFile.Allocator());
	}
	SceneFile.AddMember("TexturesFilesPaths", TextureFilePaths);

	for (auto& ShaderName : ShaderResourcePathList)
	{
		rapidjson::Value strVal;
		strVal.SetString(ShaderName.c_str(), ShaderName.length(), SceneFile.Allocator());
		ShaderFilePaths.PushBack(strVal, SceneFile.Allocator());
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

		const std::map<std::string, float>& AnimFileList = IdAnimPair.second->GetAnimationDataFileList();

		for (auto& animFile : AnimFileList)
		{
			if (MyResourceManager.GetAnimationResource(animFile.first))
			{
				if ((std::find(AnimationResourcePathList.begin(), AnimationResourcePathList.end(), animFile.first) == AnimationResourcePathList.end()))
				{
					std::string FilePath = MyResourceManager.GetAnimationResourcePath(animFile.first);
					AnimationResourcePathList.push_back(FilePath);
				}
			}
		}
	}

	for (auto& AnimName : AnimationResourcePathList)
	{
		rapidjson::Value strVal;
		strVal.SetString(AnimName.c_str(), AnimName.length(), SceneFile.Allocator());
		AnimationFilePaths.PushBack(strVal, SceneFile.Allocator());
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
		rapidjson::Value strVal;
		strVal.SetString(AudioName.c_str(), AudioName.length(), SceneFile.Allocator());
		AudioFilePaths.PushBack(strVal, SceneFile.Allocator());
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
		rapidjson::Value strVal;
		strVal.SetString(FontName.c_str(), FontName.length(), SceneFile.Allocator());
		FontFilePaths.PushBack(strVal, SceneFile.Allocator());
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

		rapidjson::Value obj;
		obj.SetObject();
		GameObject* proObj = nullptr;
		//Object exists in PrototypeAssetList - Save in ClonableObjects list
		if (proObj = MyResourceSystem.GetPrototypeResource(ObjType))
		{
			std::unordered_map <ComponentId, IComponent* >& comList = _listObject[id]->GetComponentList();

			for (auto& IdComPair : comList)
			{
				IComponent* protoCom = proObj->GetComponent(IdComPair.first);
				IdComPair.second->DeserialiseComponentSceneFile(protoCom, obj, SceneFile.GetAllocator());
			}
			clonableObjects.PushBack(obj, SceneFile.Allocator());

		}
		else  //Object does not exists in PrototypeAssetList - Save in NonClonableObjects list
		{
			std::unordered_map <ComponentId, IComponent* >& comList = _listObject[id]->GetComponentList();

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

}

*/