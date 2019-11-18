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
		std::string audiosPath = "./Resources/Audio";
		std::string texturesPath = "./Resources/Image";
		std::string shadersPath = "./Resources/Shader";	//Can Write and Add New Shader File?

		std::string statesPath = "./Resources/TextFiles/States";
		std::string gameObjectsPath = "./Resources/TextFiles/GameObjects";

		for (const auto& audioFile : std::filesystem::directory_iterator(audiosPath))
		{
			std::cout << audioFile.path() << std::endl;
		}

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
		}
	}

	void Update() override;
};

