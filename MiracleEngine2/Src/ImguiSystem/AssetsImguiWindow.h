#pragma once
#include "IBaseImguiWindow.h"
#include "Engine/EngineSystems.h"
#include <filesystem>
#include "Tools/MemoryManager/ResourceManager.h"


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
		ImGuiWindowFlags flags = ImGuiWindowFlags_::ImGuiWindowFlags_MenuBar);

	void Update() override;
};

