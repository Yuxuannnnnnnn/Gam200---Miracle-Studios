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
		EngineSystems::GetInstance()._gameObjectFactory->DeleteLevelNotPrefab();
		EngineSystems::GetInstance()._gameObjectFactory->SerialiseLevel(ToString(Scenes::MAIN_MENU));
		break;
	case Scenes::LEVEL1:
		EngineSystems::GetInstance()._gameObjectFactory->DeleteLevelNotPrefab();
		EngineSystems::GetInstance()._gameObjectFactory->SerialiseLevel(ToString(Scenes::LEVEL1));
		EngineSystems::GetInstance()._aiSystem->CreateNodeMap();
		break;
	case Scenes::WIN:
		EngineSystems::GetInstance()._gameObjectFactory->DeleteLevelNotPrefab();
		EngineSystems::GetInstance()._gameObjectFactory->SerialiseLevel(ToString(Scenes::WIN));
		break;
	case Scenes::LOSE:
		EngineSystems::GetInstance()._gameObjectFactory->DeleteLevelNotPrefab();
		EngineSystems::GetInstance()._gameObjectFactory->SerialiseLevel(ToString(Scenes::LOSE));
		break;
	default:
		break;
	}

	_currScene = scene;
}
