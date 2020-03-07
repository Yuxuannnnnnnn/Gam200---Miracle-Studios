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

class Folder
{
public:
	std::vector<std::string> FileName;

	std::string folderName;

	std::vector<Folder*> subFolder;//pointer to a subfolder folder which is newed.

	Folder(std::string name)
	{
		folderName = name;
	}
};



class AssetsImguiWindow: public IBaseImguiWindow
{
	//typedef std::unordered_map<std::string, std::string> NamePath;
	//NamePath _vertexFiles;
	//NamePath _fragmentFiles;

	//typedef std::map<std::string, std::string> Folder;
	typedef Folder SubFolder;
	typedef Folder SubSubFolder;

	Folder Image{ "Image" };
	Folder characterAnimation{ "characterAnimation" };
	Folder EnemiesSpawner{ "EnemiesSpawner" };
	Folder EnemyAI{"EnemyAI"};
	Folder EnvironmentAnimation{"EnvironmentAnimation"};
	Folder PowersEffect{"PowersEffect"};

	Folder PropsDesign{ "PropsDesign" };
	SubFolder SCI_FI{ "SCI_FI" };
	SubSubFolder rusted_v2{ "rusted_v2" };

	Folder Tile{ "Tile" };

	Folder Interface{ "Interface" };
	SubFolder Instruction_Menu{ "Instruction_Menu" };
	SubFolder HP_and_Progress_Bar{ "HP_and_Progress_Bar" };


	std::string selectedGameObject;
	GameObject* selectedGOPtr;

public:

	void SetSelectedObj(std::string name)
	{
		selectedGameObject = name;
	}

	//NamePath GetVertexShaderFiles()
	//{
	//	return _vertexFiles;
	//}
	//
	//NamePath GetFragementShaderFiles()
	//{
	//	return _fragmentFiles;
	//}

	AssetsImguiWindow(bool open = true,	//Set the settings for the imgui window
		ImGuiWindowFlags flags = ImGuiWindowFlags_::ImGuiWindowFlags_MenuBar);

	void Init();

	void Update() override;

	void ShowPrototypeChildObjects(GameObject* gameObject, int layer, int ID);
};

