#pragma once
#include "PrecompiledHeaders.h"
#include "Engine/EngineSystems.h"

#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

class GameObjectFactory; // forward declare, access FileRead_Level

enum class Scenes {
	RESTART = 0,
	MAIN_MENU,
	LEVEL1,
	WIN,
	LOSE,
	QUIT
};
inline const char* ToString(Scenes type)	//Convert TypeIdGO Enum type to const char* - For Use only in Imgui
{
	switch (type)
	{
	case Scenes::RESTART:	return " ";
	case Scenes::MAIN_MENU:	return "./Resources/TextFiles/States/MainMenu.txt";
	case Scenes::LEVEL1:	return "./Resources/TextFiles/States/TestLevel.txt";
	case Scenes::WIN:		return " ";
	case Scenes::LOSE:		return " ";
	default:      return "Unknown Scene";
	}
}
class SceneManager
{
	Scenes _currScene;
public:
	void ChangeScene(Scenes scene = Scenes::RESTART);
	Scenes GetCurrentScene();
};

#endif