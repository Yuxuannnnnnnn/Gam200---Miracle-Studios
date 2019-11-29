#include "PrecompiledHeaders.h"
#include "AssetsImguiWindow.h"



AssetsImguiWindow::AssetsImguiWindow(bool open, ImGuiWindowFlags flags)
	:IBaseImguiWindow("Assets", open, flags)
{
	std::string audiosPath = "./Resources/Audio";
	std::string texturesPath = "./Resources/Image";
	std::string shadersPath = "./Resources/Shader";	//Can Write and Add New Shader File?
	std::string fontsPath = "./Resources/Fonts";

	std::string statesPath = "./Resources/TextFiles/States";
	std::string gameObjectsPath = "./Resources/TextFiles/GameObjects";

	typedef std::unordered_map<std::string, std::string> NamePath;

	NamePath ResourceList;
	{
		for (const auto& audioFile : std::filesystem::directory_iterator(audiosPath))
		{
			std::cout << audioFile.path() << std::endl;
			std::string path = audioFile.path().u8string();
			std::string fileName = path.substr(0, path.find_last_of("\\/"));
			ResourceList.insert(std::pair<std::string, std::string>(fileName, path));
		}
		ResourceManager::GetInstance().AddAudioResourceList(ResourceList);
		ResourceList.clear();
	}

	{
		for (const auto& textureFile : std::filesystem::directory_iterator(texturesPath))
		{
			std::cout << textureFile.path() << std::endl;
			std::string path = textureFile.path().u8string();
			std::string fileName = path.substr(0, path.find_last_of("\\/"));
			ResourceList.insert(std::pair<std::string, std::string>(fileName, path));
		}

		ResourceManager::GetInstance().AddTexture2DResourceList(ResourceList);
		ResourceList.clear();
	}

	{
		for (const auto& shaderFile : std::filesystem::directory_iterator(shadersPath))
		{
			std::cout << shaderFile.path() << std::endl;
			std::string path = shaderFile.path().u8string();
			std::string fileName = path.substr(0, path.find_last_of("\\/"));
			ResourceList.insert(std::pair<std::string, std::string>(fileName, path));
		}

		ResourceManager::GetInstance().AddShaderResourceList(ResourceList);
		ResourceList.clear();
	}

	{
		for (const auto& fontFile : std::filesystem::directory_iterator(fontsPath))
		{
			std::cout << fontFile.path() << std::endl;
			std::string path = fontFile.path().u8string();
			std::string fileName = path.substr(0, path.find_last_of("\\/"));
			ResourceList.insert(std::pair<std::string, std::string>(fileName, path));
		}
		ResourceManager::GetInstance().AddFontResourceList(ResourceList);
		ResourceList.clear();
	}

	{
		for (const auto& stateFile : std::filesystem::directory_iterator(statesPath))
		{
			std::cout << stateFile.path() << std::endl;
			std::string path = stateFile.path().u8string();
			std::string fileName = path.substr(0, path.find_last_of("\\/"));
			ResourceList.insert(std::pair<std::string, std::string>(fileName, path));
		}

		EngineSystems::GetInstance()._sceneManager->LoadAllSceneAssets(ResourceList);
		ResourceList.clear();
	}

	{
		for (const auto& gameObjectFile : std::filesystem::directory_iterator(gameObjectsPath))
		{
			std::cout << gameObjectFile.path() << std::endl;
			std::string path = gameObjectFile.path().u8string();
			std::string fileName = path.substr(0, path.find_last_of("\\/"));
			ResourceList.insert(std::pair<std::string, std::string>(fileName, path));
		}

		EngineSystems::GetInstance()._prefabFactory->SerialiseAllPrefabAssets(ResourceList);
		ResourceList.clear();
	}
}

void AssetsImguiWindow::Update()
{
	static bool selected;
	if (ImGui::Selectable("Desrialise", selected, ImGuiSelectableFlags_AllowDoubleClick))
	{
		if (ImGui::IsMouseReleased(0))
		{

			GameObject* obj = EngineSystems::GetInstance()._gameObjectFactory->CreateNewGameObject(true);
			obj->DeSerialise();
			//std::unordered_map < unsigned, IComponentSystem* > componentList = gameObject->GetComponentList(); //Get ComponenntList from each GameObject
			//ShowGameObjectComponents(componentList);	//Show every Component of a GameObject
			//ImGui::TreePop();
			//ImGuiID id = ImGui::GetID(string.c_str());
			//ImGui::GetStateStorage()->SetInt(id, 0);
		}
	}
	// We specify a default position/size in case there's no data in the .ini file. Typically this isn't required! We only do it to make the Demo applications a little more welcoming.
	//ImVec2 main_viewport_pos = ImGui::GetMainViewport()->Pos;
	//ImGui::SetNextWindowPos(ImVec2(main_viewport_pos.x + 650, main_viewport_pos.y + 20), ImGuiCond_FirstUseEver);
	//ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_Always);
}