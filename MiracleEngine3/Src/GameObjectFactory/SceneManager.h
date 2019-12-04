#pragma once
#include "PrecompiledHeaders.h"
#include "Engine/EngineSystems.h"

#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

class GameObjectFactory; // forward declare, access FileRead_Level

enum class Scenes {
	NOCHANGE,
	RESTART,
	MAIN_MENU,
	LEVEL1,
	WIN,
	LOSE,
	QUIT,
	INSTRUCTION
};
inline const char* ToString(Scenes type)	//Convert TypeIdGO Enum type to const char* - For Use only in Imgui
{
	switch (type)
	{
	case Scenes::RESTART:	return " ";
	case Scenes::MAIN_MENU:	return "./Resources/TextFiles/States/MainMenu.txt";
	case Scenes::LEVEL1:	return "./Resources/TextFiles/States/TestLevel.txt";
	case Scenes::WIN:		return "./Resources/TextFiles/States/Win.txt";
	case Scenes::LOSE:		return "./Resources/TextFiles/States/Lose.txt";
	case Scenes::QUIT:		return " ";
	case Scenes::INSTRUCTION:		return "./Resources/TextFiles/States/Instruction.txt";
	default:      return "Unknown Scene";
	}
}
class SceneManager
{
	Scenes _currScene;
public:
	SceneManager();
	void ChangeScene(Scenes scene = Scenes::RESTART);
	Scenes GetCurrentScene();
};

#endif