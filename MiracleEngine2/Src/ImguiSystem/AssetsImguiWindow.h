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
		std::string fontsPath =    "./Resources/Fonts";

		std::string statesPath =	  "./Resources/TextFiles/States";
		std::string gameObjectsPath = "./Resources/TextFiles/GameObjects";


		std::unordered_map<std::string, std::string> audioFilePath_FileName;

		for (const auto& audioFile : std::filesystem::directory_iterator(audiosPath))
		{
			std::cout << audioFile.path() << std::endl;					//File Path

			std::string path(audioFile.path().u8string());
			std::size_t found = path.find_last_of("/\\");

			std::cout << " file: " << path.substr(found + 1) << '\n';	//File Name

			audioFilePath_FileName.insert(std::pair<std::string, std::string>(path, path.substr(found + 1)));
		}

		//EngineSystem::resourceManager.AddAudioResource(audioFilePath_FileName);

		std::unordered_map<std::string, std::string> textureFilePath_FileName;

		for (const auto& textureFile : std::filesystem::directory_iterator(texturesPath))
		{
			std::cout << textureFile.path() << std::endl;					//File Path

			std::string path(textureFile.path().u8string());
			std::size_t found = path.find_last_of("/\\");

			std::cout << " file: " << path.substr(found + 1) << '\n';	//File Name

			textureFilePath_FileName.insert(std::pair<std::string, std::string>(path, path.substr(found + 1)));
		}

		//EngineSystem::resourceManager.AddTextureResource(textureFilePath_FileName);

		std::unordered_map<std::string, std::string> shaderFilePath_FileName;

		for (const auto& shaderFile : std::filesystem::directory_iterator(shadersPath))
		{
			std::cout << shaderFile.path() << std::endl;					//File Path

			std::string path(shaderFile.path().u8string());
			std::size_t found = path.find_last_of("/\\");

			std::cout << " file: " << path.substr(found + 1) << '\n';	//File Name

			shaderFilePath_FileName.insert(std::pair<std::string, std::string>(path, path.substr(found + 1)));
		}

		//EngineSystem::resourceManager.AddShaderResource(shaderFilePath_FileName);


		std::unordered_map<std::string, std::string> fontFilePath_FileName;

		for (const auto& fontFile : std::filesystem::directory_iterator(fontsPath))
		{
			std::cout << fontFile.path() << std::endl;					//File Path

			std::string path(fontFile.path().u8string());
			std::size_t found = path.find_last_of("/\\");

			std::cout << " file: " << path.substr(found + 1) << '\n';	//File Name

			fontFilePath_FileName.insert(std::pair<std::string, std::string>(path, path.substr(found + 1)));
		}

		//EngineSystem::resourceManager.AddFontsResource(fontFilePath_FileName);

		std::unordered_map<std::string, std::string> statesFilePath_FileName;

		for (const auto& stateFile : std::filesystem::directory_iterator(statesPath))
		{
			std::cout << stateFile.path() << std::endl;					//File Path

			std::string path(stateFile.path().u8string());
			std::size_t found = path.find_last_of("/\\");

			std::cout << " file: " << path.substr(found + 1) << '\n';	//File Name

			statesFilePath_FileName.insert(std::pair<std::string, std::string>(path, path.substr(found + 1)));
		}

		//EngineSystem::SceneManager.AddSceneFiles(statesFilePath_FileName);

		std::unordered_map<std::string, std::string> gameObjectFilePath_FileName;

		for (const auto& gameObjectFile : std::filesystem::directory_iterator(gameObjectsPath))
		{
			std::cout << gameObjectFile.path() << std::endl;			//File Path

			std::string path(gameObjectFile.path().u8string());
			std::size_t found = path.find_last_of("/\\");

			std::cout << " file: " << path.substr(found + 1) << '\n';	//File Name

			gameObjectFilePath_FileName.insert(std::pair<std::string, std::string>(path, path.substr(found + 1)));
		}

		//EngineSystem::PreFab.AddPrototypes(statesFilePath_FileName);

	}

	void Update() override;
};

