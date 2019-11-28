#pragma once
#include "IBaseImguiWindow.h"
#include "Engine/EngineSystems.h"
#include <filesystem>


//Assets window must have 
//all the Texture files - Sprites and SpriteSheets
//All the GameObjectsPtototypes - 
	//Primary GameObjects such as Camera, Player, Enemy
	//UI GameObjects - 
	//Secondary GameObjects - Pickups
//All the Audio files
	//Background audios
	//Sound Effects

//Menu Button Can Add New Prototype

//For Each Prototype - Can new prototype 


class AssetsImguiWindow: public IBaseImguiWindow
{
public:

	AssetsImguiWindow(bool open = true,	//Set the settings for the imgui window
		ImGuiWindowFlags flags = ImGuiWindowFlags_::ImGuiWindowFlags_MenuBar)
		:IBaseImguiWindow("Assets", open, flags)
	{
		std::string audiosPath =   "./Resources/Audio";
		std::string texturesPath = "./Resources/Image";
		std::string shadersPath =  "./Resources/Shader";	//Can Write and Add New Shader File?

		std::string statesPath =	  "./Resources/TextFiles/States";
		std::string gameObjectsPath = "./Resources/TextFiles/GameObjects";

		typedef std::unordered_map<std::string, std::string> NamePath;

		NamePath ResourceList;

		for (const auto& audioFile : std::filesystem::directory_iterator(audiosPath))
		{
			std::cout << audioFile.path() << std::endl;
			std::string path = audioFile.path().u8string();
			std::string fileName = path.substr(0, path.find_last_of("\\/"));
			ResourceList.insert(std::pair<std::string, std::string>(fileName, path));
		}
		ResourceManager::GetInstance().AddAudioResourceList(ResourceList);
		ResourceList.clear();


		for (const auto& textureFile : std::filesystem::directory_iterator(texturesPath))
		{
			std::cout << textureFile.path() << std::endl;
		}

		for (const auto& shaderFile : std::filesystem::directory_iterator(shadersPath))
		{
			std::cout << shaderFile.path() << std::endl;
		}

		for (const auto& stateFile : std::filesystem::directory_iterator(statesPath))
		{
			std::cout << stateFile.path() << std::endl;
		}

		for (const auto& gameObjectFile : std::filesystem::directory_iterator(gameObjectsPath))
		{
			std::cout << gameObjectFile.path() << std::endl;
			std::string path = gameObjectFile.path().u8string();
			std::string fileName = path.substr(0, path.find_last_of("\\/"));
			ResourceList.insert(std::pair<std::string, std::string>(fileName, path));
		}

		//EngineSystems::GetInstance()._prefabFactory->SerialPrefabObjects(ResourceList);

	}

	void Update() override;
};

