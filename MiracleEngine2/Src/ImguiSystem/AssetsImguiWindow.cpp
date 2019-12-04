#include "PrecompiledHeaders.h"
#include "AssetsImguiWindow.h"



AssetsImguiWindow::AssetsImguiWindow(bool open, ImGuiWindowFlags flags)

	:IBaseImguiWindow("Assets",1, 20, 347, 505, open, flags)
{
	std::string audiosPath = "./Resources/Audio";
	std::string texturesPath = "./Resources/Image";
	std::string shadersPath = "./Resources/Shader";	//Can Write and Add New Shader File?
	std::string fontsPath = "./Resources/Fonts";

	std::string statesPath = "./Resources/TextFiles/Scenes/Scenes";
	std::string gameObjectsPath = "./Resources/TextFiles/GameObjects";
	std::string AnimationDataPath = "./Resources/TextFiles/AnimationData";

	typedef std::unordered_map<std::string, std::string> NamePath;

	NamePath ResourceList;
	{
		for (const auto& audioFile : std::filesystem::directory_iterator(audiosPath))
		{
			std::cout << audioFile.path() << std::endl;
			std::string path = audioFile.path().u8string();
			size_t namesize = path.find_last_of(".ogg") - 4 - path.find_last_of("\\");
			std::string fileName = path.substr(path.find_last_of("\\") + 1, namesize);
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
			//size_t namesize = path.find_last_of(".png") - 4 - path.find_last_of("\\");
			std::string fileName = path.substr(path.find_last_of("\\") + 1);
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
			std::string fileName = path.substr(path.find_last_of("\\")+ 1);
			if (fileName.find(".vert") != std::string::npos)
			{
				_vertexFiles.insert(std::pair<std::string, std::string>(fileName, path));
			}
			else if (fileName.find(".frag") != std::string::npos)
			{
				_fragmentFiles.insert(std::pair<std::string, std::string>(fileName, path));
			}
			ResourceList.insert(std::pair<std::string, std::string>(fileName, path));
		}

		//ResourceManager::GetInstance().AddShaderResourceList(ResourceList);
		ResourceList.clear();
	}

	{
		for (const auto& fontFile : std::filesystem::directory_iterator(fontsPath))
		{
			std::cout << fontFile.path() << std::endl;
			std::string path = fontFile.path().u8string();
			size_t namesize = path.find_last_of(".ttf") - 4 - path.find_last_of("\\");
			std::string fileName = path.substr(path.find_last_of("\\") + 1, namesize);
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
			size_t namesize = path.find_last_of(".json") - 5 - path.find_last_of("\\");
			std::string fileName = path.substr(path.find_last_of("\\") + 1, namesize);
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
			size_t namesize = path.find_last_of(".json") - 5 - path.find_last_of("\\");
			std::string fileName = path.substr(path.find_last_of("\\") + 1, namesize);
			ResourceList.insert(std::pair<std::string, std::string>(fileName, path));
		}

		EngineSystems::GetInstance()._prefabFactory->SerialiseAllPrefabAssets(ResourceList);
		ResourceList.clear();
	}

	{
		for (const auto& AnimationDataFile : std::filesystem::directory_iterator(AnimationDataPath))
		{
			std::cout << AnimationDataFile.path() << std::endl;
			std::string path = AnimationDataFile.path().u8string();
			size_t namesize = path.find_last_of(".json") - 5 - path.find_last_of("\\");
			std::string fileName = path.substr(path.find_last_of("\\") + 1, namesize);
			ResourceList.insert(std::pair<std::string, std::string>(fileName, path));
		}

		ResourceManager::GetInstance().AddAnimationResourceList(ResourceList);
		ResourceList.clear();

	}
}

void AssetsImguiWindow::Update()
{
	ImGui::SetWindowFontScale(1);

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File  "))
		{
		}
		ImGui::EndMenuBar();
	}

	if (ImGui::CollapsingHeader("Scenes"))
	{
		auto& allScenes = _engineSystems._sceneManager->GetAllScenes();
		ImGui::Spacing();

		for (auto& scenePair : allScenes)
		{
			static bool selected;
			std::string string = " - " + scenePair.first;

			if (ImGui::Selectable(string.c_str(), selected, ImGuiSelectableFlags_AllowDoubleClick))
			{
				if (ImGui::IsMouseReleased(0))
				{
					_engineSystems._sceneManager->ChangeScene(scenePair.first);
				}
			}
			ImGui::Spacing();
		}
		//ImGui::TreePop();
	}

	std::unordered_map <std::string, GameObject* >& PrototypeList = _engineSystems._prefabFactory->GetPrototypeList();
	size_t prototypeCount = PrototypeList.size();
	std::string string = "Prototypes (" + std::to_string(prototypeCount) + ")";

	if (ImGui::CollapsingHeader(string.c_str()))
	{
		ImGui::Spacing();

		std::string string1 = "Create New Prototype ";
		if (ImGui::Button(string1.c_str()))
		{
			GameObject* newGameobject = _engineSystems._gameObjectFactory->CreateNewGameObject(true);
			newGameobject->AddComponent(ComponentId::IDENTITY_COMPONENT);
			InspectionImguiWindow::InspectGameObject(newGameobject);
		}
		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();

	//	int i = 0;
		for (auto& ObjPair: PrototypeList)
		{
			//std::string objName = std::to_string(i) + ". " + ObjPair.first;
			//i++;
			static bool selected;
			std::string string = " - " + ObjPair.first;

			if (ImGui::Selectable(string.c_str(), selected, ImGuiSelectableFlags_AllowDoubleClick))
			{
				if (ImGui::IsMouseReleased(0))
				{
					InspectionImguiWindow::InspectGameObject(ObjPair.second);
					//std::unordered_map < unsigned, IComponentSystem* > componentList = gameObject->GetComponentList(); //Get ComponenntList from each GameObject
					//ShowGameObjectComponents(componentList);	//Show every Component of a GameObject
					//ImGui::TreePop();
					//ImGuiID id = ImGui::GetID(string.c_str());
					//ImGui::GetStateStorage()->SetInt(id, 0);
				}
			}

			ImGui::SameLine();

			std::string string1 = "Clone " + ObjPair.first;
			if (ImGui::Button(string1.c_str()))
			{
				GameObject* newGameobject = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(EngineSystems::GetInstance()._prefabFactory->GetPrototypeList()[ObjPair.first]);
				dynamic_cast<TransformComponent*>(newGameobject->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(Vector3::Vec3Zero);
			}
			//std::unordered_map < unsigned, IComponentSystem* > componentList = gameObject->GetComponentList(); //Get ComponenntList from each GameObject
			//ShowGameObjectComponents(componentList);	//Show every Component of a GameObject
			//ImGui::TreePop();
			//ImGuiID id = ImGui::GetID(string.c_str());
			//ImGui::GetStateStorage()->SetInt(id, 0);

			ImGui::Spacing();
		}
		
		//ImGui::TreePop();

	}

	if (ImGui::CollapsingHeader("Textures"))
	{
		ImGui::Spacing();

		auto textureFiles = ResourceManager::GetInstance().GetTexture2DList();

		for (auto& texturePair : textureFiles)
		{
			static bool selected;
			std::string string = " - " + texturePair.first;

			Texture2D* texture = ResourceManager::GetInstance().GetTexture2DResource(texturePair.first);
			TextureImguiWindow* textureWindow = dynamic_cast<TextureImguiWindow *>(_engineSystems._imguiSystem->GetWindows()["Texture"]);

			if (ImGui::Selectable(string.c_str(), selected, ImGuiSelectableFlags_AllowDoubleClick))
			{
				if (ImGui::IsMouseReleased(0))
				{
					TextureImguiWindow::setTexture(textureWindow, texture, texturePair.first);
				}
			}

			ImGui::Spacing();

		}
		//ImGui::TreePop();

	}


	if (ImGui::CollapsingHeader("Shaders"))
	{
		ImGui::Spacing();

		//ImGui::TreePop();
		for (auto& vertexPair : _vertexFiles)
		{
			static bool selected;
			std::string string = " - " + vertexPair.first;

			if (ImGui::Selectable(string.c_str(), selected, ImGuiSelectableFlags_AllowDoubleClick))
			{
				if (ImGui::IsMouseReleased(0))
				{
				}
			}
			ImGui::Spacing();

		}

		for (auto& fragmentPair : _fragmentFiles)
		{
			static bool selected;
			std::string string = " - " + fragmentPair.first;

			if (ImGui::Selectable(string.c_str(), selected, ImGuiSelectableFlags_AllowDoubleClick))
			{
				if (ImGui::IsMouseReleased(0))
				{
				}
			}
			ImGui::Spacing();
		}

	}

	if (ImGui::CollapsingHeader("Fonts"))
	{
		ImGui::Spacing();

		auto fontFiles = ResourceManager::GetInstance().GetFontList();

		for (auto& fontPair : fontFiles)
		{
			static bool selected;
			std::string string = " - " + fontPair.first;

			if (ImGui::Selectable(string.c_str(), selected, ImGuiSelectableFlags_AllowDoubleClick))
			{
				if (ImGui::IsMouseReleased(0))
				{
				}
			}
			ImGui::Spacing();
		}

		//ImGui::TreePop();
	}

	if (ImGui::CollapsingHeader("Audio"))
	{
		ImGui::Spacing();

		auto audioFiles = ResourceManager::GetInstance().GetSoundList();

		for (auto& audioPair : audioFiles)
		{
			static bool selected;
			std::string string = " - " + audioPair.first;

			if (ImGui::Selectable(string.c_str(), selected, ImGuiSelectableFlags_AllowDoubleClick))
			{
				if (ImGui::IsMouseReleased(0))
				{
				}
			}
			ImGui::Spacing();

		}

		//ImGui::TreePop();
	}

	if (ImGui::CollapsingHeader("Animation Data Files"))
	{
		ImGui::Spacing();

		auto animationData = ResourceManager::GetInstance().GetAnimationlist();

		for (auto& animationPair : animationData)
		{
			static bool selected;
			std::string string = " - " + animationPair.first;

			if (ImGui::Selectable(string.c_str(), selected, ImGuiSelectableFlags_AllowDoubleClick))
			{
				if (ImGui::IsMouseReleased(0))
				{
				}
			}
			ImGui::Spacing();

		}
		//ImGui::TreePop();
	}

	// We specify a default position/size in case there's no data in the .ini file. Typically this isn't required! We only do it to make the Demo applications a little more welcoming.
	//ImVec2 main_viewport_pos = ImGui::GetMainViewport()->Pos;
	//ImGui::SetNextWindowPos(ImVec2(main_viewport_pos.x + 650, main_viewport_pos.y + 20), ImGuiCond_FirstUseEver);
	//ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_Always);
}
