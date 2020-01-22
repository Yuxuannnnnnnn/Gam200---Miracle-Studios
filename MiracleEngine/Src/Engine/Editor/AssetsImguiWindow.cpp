#include "PrecompiledHeaders.h"
#include "AssetsImguiWindow.h"



AssetsImguiWindow::AssetsImguiWindow(bool open, ImGuiWindowFlags flags)

	:IBaseImguiWindow("Assets",1, 20, 347, 490, open, flags)
{
	std::string audiosPath = "./Resources/Audio";
	std::string fontsPath = "./Resources/Fonts";
	std::string texturesPath = "./Resources/Image";

	std::string shadersPath = "./Resources/Shader";

	std::string statesPath = "./Resources/TextFiles/Scenes/Scenes";
	std::string gameObjectsPath = "./Resources/TextFiles/GameObjects";
	std::string AnimationDataPath = "./Resources/TextFiles/AnimationData";

	typedef std::map<std::string, std::string> NamePath;

	NamePath ResourceList;

	typedef std::unordered_map<std::string, std::string> unorderedNamePath;

	unorderedNamePath ResourceList1;
	{
		for (const auto& audioFile : std::filesystem::directory_iterator(audiosPath))
		{
			std::cout << audioFile.path() << std::endl;
			std::string path = audioFile.path().u8string();
			//size_t namesize = path.find_last_of(".ogg") - 4 - path.find_last_of("\\/");
			std::string fileName = path.substr(path.find_last_of("\\/") + 1);
			ResourceList.insert(std::pair<std::string, std::string>(fileName, path));
		}
		MyResourceSystem.AddAudioResourceList(ResourceList);
		ResourceList.clear();
	}

	{
		for (const auto& textureFile : std::filesystem::directory_iterator(texturesPath))
		{
			std::cout << textureFile.path() << std::endl;
			std::string path = textureFile.path().u8string();
			//size_t namesize = path.find_last_of(".png") - 4 - path.find_last_of("\\/");
			std::string fileName = path.substr(path.find_last_of("\\/") + 1);
			ResourceList.insert(std::pair<std::string, std::string>(fileName, path));
		}

		MyResourceSystem.AddTexture2DResourceList(ResourceList);
		ResourceList.clear();
	}

	typedef std::pair<std::string, std::string> VertFrag;
	std::unordered_map<std::string, VertFrag> ShaderResource;

	VertFrag vertFrag;
	{
		for (const auto& shaderFile : std::filesystem::directory_iterator(shadersPath))
		{
			std::cout << shaderFile.path() << std::endl;
			std::string path = shaderFile.path().u8string();
		
			std::string ShaderName = "";

			if (path.find(".vert") != std::string::npos)
			{
				size_t namesize = path.find_last_of(".vert") - 5 - path.find_last_of("\\/");
				ShaderName = path.substr(path.find_last_of("\\/") + 1, namesize);
				vertFrag.first = path;
				ShaderResource.insert(std::pair<std::string, VertFrag>(ShaderName, vertFrag));
			}
			else if (path.find(".frag") != std::string::npos)
			{
				//size_t namesize = path.find_last_of(".frag") - 5 - path.find_last_of("\\/");
				vertFrag.second = path;
			}
		}

		MyResourceSystem.AddShaderResourceList(ShaderResource);
		ShaderResource.clear();
	}

	{
		for (const auto& fontFile : std::filesystem::directory_iterator(fontsPath))
		{
			std::cout << fontFile.path() << std::endl;
			std::string path = fontFile.path().u8string();
			//size_t namesize = path.find_last_of(".ttf") - 4 - path.find_last_of("\\/");
			std::string fileName = path.substr(path.find_last_of("\\/") + 1);
			ResourceList.insert(std::pair<std::string, std::string>(fileName, path));
		}
		MyResourceSystem.AddFontResourceList(ResourceList);
		ResourceList.clear();
	}

	{
		for (const auto& stateFile : std::filesystem::directory_iterator(statesPath))
		{
			std::cout << stateFile.path() << std::endl;
			std::string path = stateFile.path().u8string();
			size_t namesize = path.find_last_of(".json") - 5 - path.find_last_of("\\");
			std::string fileName = path.substr(path.find_last_of("\\") + 1, namesize);
			ResourceList1.insert(std::pair<std::string, std::string>(fileName, path));
		}

		MyFactory.LoadAllSceneAssets(ResourceList1);
		ResourceList1.clear();
	}

	{
		for (const auto& gameObjectFile : std::filesystem::directory_iterator(gameObjectsPath))
		{
			std::cout << gameObjectFile.path() << std::endl;
			std::string path = gameObjectFile.path().u8string();
			size_t namesize = path.find_last_of(".json") - 5 - path.find_last_of("\\");
			std::string fileName = path.substr(path.find_last_of("\\") + 1, namesize);
			ResourceList1.insert(std::pair<std::string, std::string>(fileName, path));
		}

		MyFactory.SerialiseAllPrefabAssets(ResourceList1);
		ResourceList1.clear();
	}

	{
		for (const auto& AnimationDataFile : std::filesystem::directory_iterator(AnimationDataPath))
		{
			std::cout << AnimationDataFile.path() << std::endl;
			std::string path = AnimationDataFile.path().u8string();
			//size_t namesize = path.find_last_of(".json") - 5 - path.find_last_of("\\/");
			std::string fileName = path.substr(path.find_last_of("\\/") + 1);
			ResourceList.insert(std::pair<std::string, std::string>(fileName, path));
		}
	
		MyResourceSystem.AddAnimationResourceList(ResourceList);
		ResourceList.clear();
	
	}
}

void AssetsImguiWindow::Update()
{
	ImGui::SetWindowFontScale(1);

	//if (ImGui::BeginMenuBar())
	//{
	//	if (ImGui::BeginMenu("File  "))
	//	{
	//	}
	//	ImGui::EndMenuBar();
	//}

	if (ImGui::CollapsingHeader("Scenes"))
	{
		auto& allScenes = MyResourceSystem.GetSceneList();
		size_t sceneCount = allScenes.size();
		std::string string = "Prototypes (" + std::to_string(sceneCount) + ")";

		ImGui::Spacing();


		static std::string selectedObj;
		selectedObj = " - " + MyFactory.GetCurrentScene();

		for (auto& scenePair : allScenes)
		{
			static bool selected;
			std::string string = " - " + scenePair.first;

			ImGuiSelectableFlags_ flags;


			if (!string.compare(selectedObj))
				flags = ImGuiSelectableFlags_Disabled;
			else
				flags = ImGuiSelectableFlags_AllowDoubleClick;



			if (ImGui::Selectable(string.c_str(), selected, flags))
			{
				if (ImGui::IsMouseReleased(0))
				{
					MyFactory.ChangeScene(scenePair.first);
				}
			}
			ImGui::Spacing();
		}
		//ImGui::TreePop();
	}


	{
		std::unordered_map <std::string, GameObject* >& PrototypeList = MyResourceSystem.GetPrototypeMap();
		size_t prototypeCount = PrototypeList.size();
		std::string string = "Prototypes (" + std::to_string(prototypeCount) + ")";

		if (ImGui::CollapsingHeader(string.c_str()))
		{
			ImGui::Spacing();

			std::string string1 = "Create New Prototype ";
			if (ImGui::Button(string1.c_str()))
			{
				GameObject* newGameobject = MyFactory.CreateEmptyGameObject();//new GameObject();
				newGameobject->AddComponent(ComponentId::CT_Identity);
				InspectionImguiWindow::InspectGameObject(newGameobject);
			}
			ImGui::Spacing();
			ImGui::Separator();
			ImGui::Spacing();

			int i = 0;

			for (auto& ObjPair : PrototypeList)
			{
				//std::string objName = std::to_string(i) + ". " + ObjPair.first;
				//i++;
				static bool selected;
				//std::string string = " - " + ObjPair.first;

				std::string string = std::to_string(i) + " " + ObjPair.first; // "Object Type + Object unique number" string


				ImGuiSelectableFlags_ flags;
				static std::string selectedObj;

				if (!string.compare(selectedObj))
					flags = ImGuiSelectableFlags_Disabled;
				else
					flags = ImGuiSelectableFlags_AllowDoubleClick;


				if (ImGui::Selectable(string.c_str(), selected, flags))
				{
					if (ImGui::IsMouseReleased(0))
					{
						InspectionImguiWindow::InspectGameObject(ObjPair.second);
						selectedObj = string;
						//std::unordered_map < unsigned, IComponent* > componentList = gameObject->GetComponentList(); //Get ComponenntList from each GameObject
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
					GameObject* newGameobject = MyFactory.CloneGameObject(MyResourceSystem.GetPrototypeMap()[ObjPair.first]);
					if(TransformComponent * tmp = dynamic_cast<TransformComponent*>(newGameobject->GetComponent(ComponentId::CT_Transform)))
						tmp->SetPos(Vector3::Vec3Zero);
				}
				//std::unordered_map < unsigned, IComponent* > componentList = gameObject->GetComponentList(); //Get ComponenntList from each GameObject
				//ShowGameObjectComponents(componentList);	//Show every Component of a GameObject
				//ImGui::TreePop();
				//ImGuiID id = ImGui::GetID(string.c_str());
				//ImGui::GetStateStorage()->SetInt(id, 0);

				ImGui::Spacing();
				i++;
			}

			//ImGui::TreePop();

		}
	}

	{
		auto textureFiles = MyResourceSystem.GetTexture2DList();
		size_t textureCount = textureFiles.size();
		std::string string = "Textures (" + std::to_string(textureCount) + ")";

		if (ImGui::CollapsingHeader(string.c_str()))
		{
			ImGui::Spacing();

			auto textureFiles = MyResourceSystem.GetTexture2DList();

			for (auto& texturePair : textureFiles)
			{
				static bool selected;
				std::string string = " - " + texturePair.first;

				ImGuiSelectableFlags_ flags;
				static std::string selectedObj;

				if (!string.compare(selectedObj))
					flags = ImGuiSelectableFlags_Disabled;
				else
					flags = ImGuiSelectableFlags_AllowDoubleClick;


				Texture2D* texture = MyResourceSystem.GetTexture2DResource(texturePair.first);
				TextureImguiWindow* textureWindow = dynamic_cast<TextureImguiWindow*>(_engineSystems._imguiSystem->GetWindows()["Texture"]);

				if (ImGui::Selectable(string.c_str(), selected, flags))
				{
					if (ImGui::IsMouseReleased(0))
					{
						TextureImguiWindow::setTexture(textureWindow, texture, texturePair.first);
						selectedObj = string;
					}
				}

				ImGui::Spacing();

			}
			//ImGui::TreePop();

		}
	}

	if (ImGui::CollapsingHeader("Shaders"))
	{
		ImGui::Spacing();

		//ImGui::TreePop();

		auto& ShaderList = MyResourceSystem.GetShaderList();
		for (auto& Shader : ShaderList)
		{
			static bool selected;
			std::string string = " - " + Shader.first;
		
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

		auto fontFiles = MyResourceSystem.GetFontList();

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

		auto audioFiles = MyResourceSystem.GetSoundList();

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

		auto animationData = MyResourceSystem.GetAnimationList();

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
