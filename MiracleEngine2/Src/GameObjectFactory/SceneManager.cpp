#include "PrecompiledHeaders.h"
#include"SceneManager.h"

SceneManager::SceneManager() :
	_scenes{},
	_currentScene{ "MainMenu" }
{
}

//Scenes SceneManager::GetCurrentScene()
//{
//	switch (_currScene)
//	{
//	case Scenes::RESTART:
//		return Scenes::RESTART;
//	case Scenes::MAIN_MENU:
//		return Scenes::MAIN_MENU;
//	case Scenes::LEVEL1:
//		return Scenes::LEVEL1;
//	case Scenes::WIN:
//		return Scenes::WIN;
//	case Scenes::LOSE:
//		return Scenes::LOSE;
//	default:
//		return Scenes::RESTART;
//	}
//}

//void SceneManager::ChangeScene(Scenes scene)
//{
//
//	switch (scene)
//	{
//	case Scenes::RESTART:
//		EngineSystems::GetInstance()._gameObjectFactory->DeleteLevelNotPrefab();
//		EngineSystems::GetInstance()._gameObjectFactory->SerialiseLevel(ToString(_currScene));
//		return;
//	case Scenes::MAIN_MENU:
//		EngineSystems::GetInstance()._gameObjectFactory->DeleteLevelNotPrefab();
//		EngineSystems::GetInstance()._gameObjectFactory->SerialiseLevel(ToString(Scenes::MAIN_MENU));
//		break;
//	case Scenes::LEVEL1:
//		EngineSystems::GetInstance()._gameObjectFactory->DeleteLevelNotPrefab();
//		EngineSystems::GetInstance()._gameObjectFactory->SerialiseLevel(ToString(Scenes::LEVEL1));
//		EngineSystems::GetInstance()._aiSystem->CreateNodeMap();
//		break;
//	case Scenes::WIN:
//		EngineSystems::GetInstance()._gameObjectFactory->SerialiseLevel(ToString(Scenes::WIN));
//		break;
//	case Scenes::LOSE:
//		EngineSystems::GetInstance()._gameObjectFactory->SerialiseLevel(ToString(Scenes::LOSE));
//		break;
//	default:
//		break;
//	}
//
//	_currScene = scene;
//}



void SceneManager::InitScene()
{
	_currentScene = "MainMenu";
	EngineSystems::GetInstance()._gameObjectFactory->SerialiseLevel(_currentScene);
}

void SceneManager::ChangeScene(std::string scene)
{
	NamePath::const_iterator  it = _scenes.find(scene);
	if (it == _scenes.end() && (scene.compare("Restart")) && (scene.compare("restart"))
		&& scene.compare("Quit") && scene.compare("quit") )	//No such scene
	{
		return;
	}

	_currentScene = scene;

	if (scene.compare("Quit") == 0 && scene.compare("quit") == 0)
	{
		return;
	}

	if (scene.compare("Restart") == 0 || scene.compare("restart") == 0)
	{
#ifdef LEVELEDITOR //for Level editor Mode
		if (_engineSystems.GetInstance()._imguiSystem->_editorMode) //when level editor mode is ON
		{
			EngineSystems::GetInstance()._gameObjectFactory->DeleteLevelNotPrefab();
		}
		else //when level editor mode is OFF
		{
			EngineSystems::GetInstance()._gameObjectFactory->DeleteLevel();
		}
#else	//for GamePlay mode
		EngineSystems::GetInstance()._gameObjectFactory->DeleteLevel();
#endif
		EngineSystems::GetInstance()._gameObjectFactory->SerialiseLevel(_currentScene);
	}
	else
	{
#ifdef LEVELEDITOR //for Level editor Mode
		if (_engineSystems.GetInstance()._imguiSystem->_editorMode) //when level editor mode is ON
		{
			EngineSystems::GetInstance()._gameObjectFactory->DeleteLevelNotPrefab();
		}
		else //when level editor mode is OFF
		{
			EngineSystems::GetInstance()._gameObjectFactory->DeleteLevel();
		}
#else	//for GamePlay mode
		EngineSystems::GetInstance()._gameObjectFactory->DeleteLevel();
#endif

		EngineSystems::GetInstance()._gameObjectFactory->SerialiseLevel(_scenes[scene]);
	}
}

void SceneManager::SerialiseScenes(Serialiser GameSceneFile)
{
	if (GameSceneFile.HasMember("GameScenes"))
	{
		for (unsigned i = 0; i < GameSceneFile["GameScenes"].Size(); i++)
		{
			std::string filePath = GameSceneFile["GameScenes"][i].GetString();
			std::string fileName = filePath.substr(0, filePath.find_last_of("\\/"));
			fileName = filePath.substr(filePath.find_last_of("."), filePath.back());

			_scenes.insert(std::pair<std::string, std::string>(fileName, filePath));
		}
	}
}

void SceneManager::LoadAllSceneAssets(NamePath GameSceneFile)
{
	_scenes = GameSceneFile;


	for (auto& scene : _scenes)
		std::cout << scene.second <<std::endl;
}