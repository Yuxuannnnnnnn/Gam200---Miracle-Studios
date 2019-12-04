#include "PrecompiledHeaders.h"
#include"SceneManager.h"

SceneManager::SceneManager() :
	_currScene{Scenes::MAIN_MENU}
{
}

Scenes SceneManager::GetCurrentScene()
{
	switch (_currScene)
	{
	case Scenes::RESTART:
		return Scenes::RESTART;
	case Scenes::MAIN_MENU:
		return Scenes::MAIN_MENU;
	case Scenes::LEVEL1:
		return Scenes::LEVEL1;
	case Scenes::WIN:
		return Scenes::WIN;
	case Scenes::LOSE:
		return Scenes::LOSE;
	case Scenes::QUIT:
		return Scenes::QUIT;
	case Scenes::INSTRUCTION:
		return Scenes::INSTRUCTION;
	default:
		return Scenes::RESTART;
	}
}

void SceneManager::ChangeScene(Scenes scene)
{
	

	
	switch (scene)
	{
	case Scenes::RESTART:
		EngineSystems::GetInstance()._gameObjectFactory->DeleteLevelNotPrefab();
		EngineSystems::GetInstance()._gameObjectFactory->SerialiseLevel(ToString(_currScene));
		return;
	case Scenes::MAIN_MENU:
		_currScene = Scenes::MAIN_MENU;
		EngineSystems::GetInstance()._gameObjectFactory->DeleteLevelNotPrefab();
		EngineSystems::GetInstance()._gameObjectFactory->SerialiseLevel(ToString(Scenes::MAIN_MENU));
		break;
	case Scenes::LEVEL1:
		_currScene = Scenes::LEVEL1;
		EngineSystems::GetInstance()._gameObjectFactory->DeleteLevelNotPrefab();
		EngineSystems::GetInstance()._gameObjectFactory->SerialiseLevel(ToString(Scenes::LEVEL1));
		EngineSystems::GetInstance()._aiSystem->CreateNodeMap();
		break;
	case Scenes::WIN:
		_currScene = Scenes::WIN;
		EngineSystems::GetInstance()._gameObjectFactory->DeleteLevelNotPrefab();
		EngineSystems::GetInstance()._gameObjectFactory->SerialiseLevel(ToString(Scenes::WIN));
		break;
	case Scenes::LOSE:
		_currScene = Scenes::LOSE;
		EngineSystems::GetInstance()._gameObjectFactory->DeleteLevelNotPrefab();
		EngineSystems::GetInstance()._gameObjectFactory->SerialiseLevel(ToString(Scenes::LOSE));
		break;
	case Scenes::INSTRUCTION:
		_currScene = Scenes::INSTRUCTION;
		EngineSystems::GetInstance()._gameObjectFactory->DeleteLevelNotPrefab();
		EngineSystems::GetInstance()._gameObjectFactory->SerialiseLevel(ToString(Scenes::INSTRUCTION));
		break;
	case Scenes::QUIT:
		//EngineSystems::GetInstance()._gameObjectFactory->DeleteLevel();
		_currScene = Scenes::QUIT;
		break;
	default:
		break;
	}

	_currScene = scene;
}
