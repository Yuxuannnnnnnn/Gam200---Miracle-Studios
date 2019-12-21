#pragma once
#include "IBaseImguiWindow.h"
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
	typedef std::unordered_map<std::string, std::string> NamePath;
	NamePath _vertexFiles;
	NamePath _fragmentFiles;

public:

	NamePath GetVertexShaderFiles()
	{
		return _vertexFiles;
	}

	NamePath GetFragementShaderFiles()
	{
		return _fragmentFiles;
	}

	AssetsImguiWindow(bool open = true,	//Set the settings for the imgui window
		ImGuiWindowFlags flags = ImGuiWindowFlags_::ImGuiWindowFlags_MenuBar);

	void Update() override;
};

