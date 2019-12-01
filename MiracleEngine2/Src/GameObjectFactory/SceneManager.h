#pragma once
#include "PrecompiledHeaders.h"
#include "Engine/EngineSystems.h"

#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

class GameObjectFactory; // forward declare, access FileRead_Level

//enum class Scenes {
//	NOCHANGE,
//	RESTART,
//	MAIN_MENU,
//	LEVEL1,
//	WIN,
//	LOSE,
//	QUIT
//};
//inline const char* ToString(Scenes type)	//Convert TypeIdGO Enum type to const char* - For Use only in Imgui
//{
//	switch (type)
//	{
//	case Scenes::RESTART:	return " ";
//	case Scenes::MAIN_MENU:	return "./Resources/TextFiles/States/MainMenu.txt";
//	case Scenes::LEVEL1:	return "./Resources/TextFiles/States/Level1.json";
//	case Scenes::WIN:		return " ";
//	case Scenes::LOSE:		return " ";
//	case Scenes::QUIT:		return " ";
//	default:      return "Unknown Scene";
//	}
//}
class SceneManager
{

	//Scenes _currScene;
public:
	SceneManager();
	//void ChangeScene(Scenes scene = Scenes::RESTART);
	//Scenes GetCurrentScene();


//For Dynamic Scene Changing based on .json file
private:
	typedef std::unordered_map<std::string, std::string> NamePath;

	NamePath _scenes;
	std::string _currentScene;

public:

	void InitScene();
	void ChangeScene(std::string scene);
	std::string GetCurrentScene() const
	{
		return _currentScene;
	}

//For GamePlay 
	void SerialiseScenes(Serialiser GameSceneFile);

//For Level Editor
	void LoadAllSceneAssets(NamePath GameSceneFile);
};

#endif