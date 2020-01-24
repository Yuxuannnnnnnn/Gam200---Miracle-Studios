#include "PrecompiledHeaders.h"
#include "AssetsImguiWindow.h"



//#define LESSTEXTURE


AssetsImguiWindow::AssetsImguiWindow(bool open, ImGuiWindowFlags flags)

	:IBaseImguiWindow("Assets",1, 20, 347, 490, open, flags)
{
	std::string audiosPath = "./Resources/Audio";
	std::string fontsPath = "./Resources/Fonts";

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




	std::vector<std::string> texturesPath;

	texturesPath.push_back("./Resources/Image");

#ifndef LESSTEXTURE

	texturesPath.push_back("./Resources/Image/Character_Animation");
	texturesPath.push_back("./Resources/Image/Enemies_Spawner");
	texturesPath.push_back("./Resources/Image/Enemy(AI)");
	texturesPath.push_back("./Resources/Image/Environment_Animation");
	texturesPath.push_back("./Resources/Image/Powers_effect");
							 	
	texturesPath.push_back("./Resources/Image/Props_design");
	texturesPath.push_back("./Resources/Image/Props_design/SCI_FI");
	texturesPath.push_back("./Resources/Image/Props_design/SCI_FI/rusted_v2");
							 		 
	texturesPath.push_back("./Resources/Image/Tile");
							 		
	texturesPath.push_back("./Resources/Image/Interface");
	texturesPath.push_back("./Resources/Image/Interface/Instruction_Menu");
	texturesPath.push_back("./Resources/Image/Interface/HP_and_Progress_Bar");

#endif 


	std::vector<Folder*> FolderList;
	FolderList.push_back(&Image);

#ifndef LESSTEXTURE

	FolderList.push_back(&characterAnimation);
	FolderList.push_back(&EnemiesSpawner);
	FolderList.push_back(&EnemyAI);
	FolderList.push_back(&EnvironmentAnimation);
	FolderList.push_back(&PowersEffect);
	FolderList.push_back(&PropsDesign);
	FolderList.push_back(&SCI_FI);
	FolderList.push_back(&rusted_v2);
	FolderList.push_back(&Tile);
	FolderList.push_back(&Interface);
	FolderList.push_back(&Instruction_Menu);
	FolderList.push_back(&HP_and_Progress_Bar);

#endif 


	int i = 0;
	{
		for (auto& path : texturesPath)
		{
			for (const auto& textureFile : std::filesystem::directory_iterator(path))
			{
				std::string path = textureFile.path().u8string();

				if (path.find(".png") == std::string::npos)
				{
					continue;
				}
				std::cout << textureFile.path() << std::endl;
				//size_t namesize = path.find_last_of(".png") - 4 - path.find_last_of("\\/");
				std::string fileName = path.substr(path.find_last_of("\\/") + 1);
				ResourceList.insert(std::pair<std::string, std::string>(fileName, path));

				FolderList[i]->FileName.push_back(std::string(fileName));
			}
			i++;
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
					PopUpBoxImguiWindow::SaveSceneWarning* type = new PopUpBoxImguiWindow::SaveSceneWarning{ scenePair.first };
					MyPopUpBox.SetPopUpBox < PopUpBoxImguiWindow::SaveSceneWarning> (type);
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

			std::string string1 = "Create New GamObject ";
			if (ImGui::Button(string1.c_str()))
			{
				GameObject* newGameobject = MyFactory.CreateEmptyGameObject();//new GameObject();
				newGameobject->AddComponent(ComponentId::CT_Identity);
				newGameobject->AddComponent(ComponentId::CT_Transform);
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

				HierarchyImguiWindow* HierarchyWindow = dynamic_cast<HierarchyImguiWindow*>(_engineSystems._imguiSystem->GetWindows()["Hierarchy"]);

				if (!string.compare(selectedObj))
				{
					if(!HierarchyWindow->GetObjIsSelected())
						flags = ImGuiSelectableFlags_Disabled;
					else
						flags = ImGuiSelectableFlags_AllowDoubleClick;
				}
				else
				{
					flags = ImGuiSelectableFlags_AllowDoubleClick;
				}


				if (ImGui::Selectable(string.c_str(), selected, flags))
				{
					if (ImGui::IsMouseReleased(0))
					{
						InspectionImguiWindow::InspectGameObject(ObjPair.second);
						selectedObj = string;
						HierarchyWindow->SetisObjectSelected(false);
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
		auto& textureFiles = MyResourceSystem.GetTexture2DList();
		size_t textureCount = textureFiles.size();
		std::string string = "Textures (" + std::to_string(textureCount) + ")";

		if (ImGui::CollapsingHeader(string.c_str()))
		{
			ImGui::Spacing();

			//auto textureFiles = MyResourceSystem.GetTexture2DList();
			TextureImguiWindow* textureWindow = dynamic_cast<TextureImguiWindow*>(_engineSystems._imguiSystem->GetWindows()["Texture"]);
			ImGuiSelectableFlags_ flags;
			static std::string selectedObj;

			for (auto& textureName : Image.FileName)
			{
				static bool selected;
				std::string string = " - " + textureName;

				if (!string.compare(selectedObj))
				{
					if (textureWindow->GetOpen())
					{
						flags = ImGuiSelectableFlags_Disabled;
					}
					else
					{
						flags = ImGuiSelectableFlags_AllowDoubleClick;
					}
				}
				else
				{
					flags = ImGuiSelectableFlags_AllowDoubleClick;
				}

				Texture2D* texture = MyResourceSystem.GetTexture2DResource(textureName);

				if (ImGui::Selectable(string.c_str(), selected, flags))
				{
					if (ImGui::IsMouseReleased(0))
					{
						TextureImguiWindow::setTexture(textureWindow, texture, textureName);
						selectedObj = string;
					}
				}

				ImGui::Spacing();
			}
			//ImGui::TreePop();


			//ImGui::Indent(ImGui::GetTreeNodeToLabelSpacing());
			//ImGui::Unindent(ImGui::GetTreeNodeToLabelSpacing());

			{
				ImGui::SetWindowFontScale(1.1);
				string = characterAnimation.folderName;
				if (ImGui::TreeNode(string.c_str()))
				{
					ImGui::SetWindowFontScale(1);
					for (auto& textureName : characterAnimation.FileName)
					{
						static bool selected;
						std::string string = " - " + textureName;
						if (!string.compare(selectedObj))
						{
							if (textureWindow->GetOpen())
							{
								flags = ImGuiSelectableFlags_Disabled;
							}
							else
							{
								flags = ImGuiSelectableFlags_AllowDoubleClick;
							}
						}
						else
						{
							flags = ImGuiSelectableFlags_AllowDoubleClick;
						}
						Texture2D* texture = MyResourceSystem.GetTexture2DResource(textureName);
						if (ImGui::Selectable(string.c_str(), selected, flags))
						{
							if (ImGui::IsMouseReleased(0))
							{
								TextureImguiWindow::setTexture(textureWindow, texture, textureName);
								selectedObj = string;
							}
						}
						ImGui::Spacing();
					}
					ImGui::TreePop();
				}
			}

			{
				ImGui::SetWindowFontScale(1.1);
				string = EnemiesSpawner.folderName;
				if (ImGui::TreeNode(string.c_str()))
				{
					ImGui::SetWindowFontScale(1);
					for (auto& textureName : EnemiesSpawner.FileName)
					{
						static bool selected;
						std::string string = " - " + textureName;
						if (!string.compare(selectedObj))
						{
							if (textureWindow->GetOpen())
							{
								flags = ImGuiSelectableFlags_Disabled;
							}
							else
							{
								flags = ImGuiSelectableFlags_AllowDoubleClick;
							}
						}
						else
						{
							flags = ImGuiSelectableFlags_AllowDoubleClick;
						}
						Texture2D* texture = MyResourceSystem.GetTexture2DResource(textureName);
						if (ImGui::Selectable(string.c_str(), selected, flags))
						{
							if (ImGui::IsMouseReleased(0))
							{
								TextureImguiWindow::setTexture(textureWindow, texture, textureName);
								selectedObj = string;
							}
						}
						ImGui::Spacing();
					}
					ImGui::TreePop();
				}
			}

			{
				ImGui::SetWindowFontScale(1.1);
				string = EnemyAI.folderName;
				if (ImGui::TreeNode(string.c_str()))
				{
					ImGui::SetWindowFontScale(1);
					for (auto& textureName : EnemyAI.FileName)
					{
						static bool selected;
						std::string string = " - " + textureName;
						if (!string.compare(selectedObj))
						{
							if (textureWindow->GetOpen())
							{
								flags = ImGuiSelectableFlags_Disabled;
							}
							else
							{
								flags = ImGuiSelectableFlags_AllowDoubleClick;
							}
						}
						else
						{
							flags = ImGuiSelectableFlags_AllowDoubleClick;
						}
						Texture2D* texture = MyResourceSystem.GetTexture2DResource(textureName);
						if (ImGui::Selectable(string.c_str(), selected, flags))
						{
							if (ImGui::IsMouseReleased(0))
							{
								TextureImguiWindow::setTexture(textureWindow, texture, textureName);
								selectedObj = string;
							}
						}
						ImGui::Spacing();
					}
					ImGui::TreePop();
				}
			}

			{
				ImGui::SetWindowFontScale(1.1);
				string = EnvironmentAnimation.folderName;
				if (ImGui::TreeNode(string.c_str()))
				{
					ImGui::SetWindowFontScale(1);
					for (auto& textureName : EnvironmentAnimation.FileName)
					{
						static bool selected;
						std::string string = " - " + textureName;
						if (!string.compare(selectedObj))
						{
							if (textureWindow->GetOpen())
							{
								flags = ImGuiSelectableFlags_Disabled;
							}
							else
							{
								flags = ImGuiSelectableFlags_AllowDoubleClick;
							}
						}
						else
						{
							flags = ImGuiSelectableFlags_AllowDoubleClick;
						}
						Texture2D* texture = MyResourceSystem.GetTexture2DResource(textureName);
						if (ImGui::Selectable(string.c_str(), selected, flags))
						{
							if (ImGui::IsMouseReleased(0))
							{
								TextureImguiWindow::setTexture(textureWindow, texture, textureName);
								selectedObj = string;
							}
						}
						ImGui::Spacing();
					}
					ImGui::TreePop();
				}
			}

			{
				ImGui::SetWindowFontScale(1.1);
				string = PowersEffect.folderName;
				if (ImGui::TreeNode(string.c_str()))
				{
					ImGui::SetWindowFontScale(1);
					for (auto& textureName : PowersEffect.FileName)
					{
						static bool selected;
						std::string string = " - " + textureName;
						if (!string.compare(selectedObj))
						{
							if (textureWindow->GetOpen())
							{
								flags = ImGuiSelectableFlags_Disabled;
							}
							else
							{
								flags = ImGuiSelectableFlags_AllowDoubleClick;
							}
						}
						else
						{
							flags = ImGuiSelectableFlags_AllowDoubleClick;
						}
						Texture2D* texture = MyResourceSystem.GetTexture2DResource(textureName);
						if (ImGui::Selectable(string.c_str(), selected, flags))
						{
							if (ImGui::IsMouseReleased(0))
							{
								TextureImguiWindow::setTexture(textureWindow, texture, textureName);
								selectedObj = string;
							}
						}
						ImGui::Spacing();
					}
					ImGui::TreePop();
				}
			}

			{
				ImGui::SetWindowFontScale(1.1);
				string = PropsDesign.folderName;
				if (ImGui::TreeNode(string.c_str()))
				{
					ImGui::SetWindowFontScale(1);
					for (auto& textureName : PropsDesign.FileName)
					{
						static bool selected;
						std::string string = " - " + textureName;
						if (!string.compare(selectedObj))
						{
							if (textureWindow->GetOpen())
							{
								flags = ImGuiSelectableFlags_Disabled;
							}
							else
							{
								flags = ImGuiSelectableFlags_AllowDoubleClick;
							}
						}
						else
						{
							flags = ImGuiSelectableFlags_AllowDoubleClick;
						}
						Texture2D* texture = MyResourceSystem.GetTexture2DResource(textureName);
						if (ImGui::Selectable(string.c_str(), selected, flags))
						{
							if (ImGui::IsMouseReleased(0))
							{
								TextureImguiWindow::setTexture(textureWindow, texture, textureName);
								selectedObj = string;
							}
						}
						ImGui::Spacing();
					}

					ImGui::SetWindowFontScale(1.1);
					string = SCI_FI.folderName;
					if (ImGui::TreeNode(string.c_str()))
					{
						ImGui::SetWindowFontScale(1);
						for (auto& textureName : SCI_FI.FileName)
						{
							static bool selected;
							std::string string = " - " + textureName;
							if (!string.compare(selectedObj))
							{
								if (textureWindow->GetOpen())
								{
									flags = ImGuiSelectableFlags_Disabled;
								}
								else
								{
									flags = ImGuiSelectableFlags_AllowDoubleClick;
								}
							}
							else
							{
								flags = ImGuiSelectableFlags_AllowDoubleClick;
							}
							Texture2D* texture = MyResourceSystem.GetTexture2DResource(textureName);
							if (ImGui::Selectable(string.c_str(), selected, flags))
							{
								if (ImGui::IsMouseReleased(0))
								{
									TextureImguiWindow::setTexture(textureWindow, texture, textureName);
									selectedObj = string;
								}
							}
							ImGui::Spacing();
						}

						ImGui::SetWindowFontScale(1.1);
						string = rusted_v2.folderName;
						if (ImGui::TreeNode(string.c_str()))
						{
							ImGui::SetWindowFontScale(1);
							for (auto& textureName : rusted_v2.FileName)
							{
								static bool selected;
								std::string string = " - " + textureName;
								if (!string.compare(selectedObj))
								{
									if (textureWindow->GetOpen())
									{
										flags = ImGuiSelectableFlags_Disabled;
									}
									else
									{
										flags = ImGuiSelectableFlags_AllowDoubleClick;
									}
								}
								else
								{
									flags = ImGuiSelectableFlags_AllowDoubleClick;
								}
								Texture2D* texture = MyResourceSystem.GetTexture2DResource(textureName);
								if (ImGui::Selectable(string.c_str(), selected, flags))
								{
									if (ImGui::IsMouseReleased(0))
									{
										TextureImguiWindow::setTexture(textureWindow, texture, textureName);
										selectedObj = string;
									}
								}
								ImGui::Spacing();
							}
							ImGui::TreePop();
						}
						ImGui::TreePop();
					}
					ImGui::TreePop();
				}
			}


			{
				ImGui::SetWindowFontScale(1.1);
				string = Tile.folderName;
				if (ImGui::TreeNode(string.c_str()))
				{
					ImGui::SetWindowFontScale(1);
					for (auto& textureName : Tile.FileName)
					{
						static bool selected;
						std::string string = " - " + textureName;
						if (!string.compare(selectedObj))
						{
							if (textureWindow->GetOpen())
							{
								flags = ImGuiSelectableFlags_Disabled;
							}
							else
							{
								flags = ImGuiSelectableFlags_AllowDoubleClick;
							}
						}
						else
						{
							flags = ImGuiSelectableFlags_AllowDoubleClick;
						}
						Texture2D* texture = MyResourceSystem.GetTexture2DResource(textureName);
						if (ImGui::Selectable(string.c_str(), selected, flags))
						{
							if (ImGui::IsMouseReleased(0))
							{
								TextureImguiWindow::setTexture(textureWindow, texture, textureName);
								selectedObj = string;
							}
						}
						ImGui::Spacing();
					}
					ImGui::TreePop();
				}
			}

			{
				ImGui::SetWindowFontScale(1.1);
				string = Interface.folderName;
				if (ImGui::TreeNode(string.c_str()))
				{
					ImGui::SetWindowFontScale(1);
					for (auto& textureName : Interface.FileName)
					{
						static bool selected;
						std::string string = " - " + textureName;
						if (!string.compare(selectedObj))
						{
							if (textureWindow->GetOpen())
							{
								flags = ImGuiSelectableFlags_Disabled;
							}
							else
							{
								flags = ImGuiSelectableFlags_AllowDoubleClick;
							}
						}
						else
						{
							flags = ImGuiSelectableFlags_AllowDoubleClick;
						}
						Texture2D* texture = MyResourceSystem.GetTexture2DResource(textureName);
						if (ImGui::Selectable(string.c_str(), selected, flags))
						{
							if (ImGui::IsMouseReleased(0))
							{
								TextureImguiWindow::setTexture(textureWindow, texture, textureName);
								selectedObj = string;
							}
						}
						ImGui::Spacing();
					}

					ImGui::SetWindowFontScale(1.1);
					string = Instruction_Menu.folderName;
					if (ImGui::TreeNode(string.c_str()))
					{
						ImGui::SetWindowFontScale(1);
						for (auto& textureName : Instruction_Menu.FileName)
						{
							static bool selected;
							std::string string = " - " + textureName;
							if (!string.compare(selectedObj))
							{
								if (textureWindow->GetOpen())
								{
									flags = ImGuiSelectableFlags_Disabled;
								}
								else
								{
									flags = ImGuiSelectableFlags_AllowDoubleClick;
								}
							}
							else
							{
								flags = ImGuiSelectableFlags_AllowDoubleClick;
							}
							Texture2D* texture = MyResourceSystem.GetTexture2DResource(textureName);
							if (ImGui::Selectable(string.c_str(), selected, flags))
							{
								if (ImGui::IsMouseReleased(0))
								{
									TextureImguiWindow::setTexture(textureWindow, texture, textureName);
									selectedObj = string;
								}
							}
							ImGui::Spacing();
						}
						ImGui::TreePop();
					}

					ImGui::SetWindowFontScale(1.1);
					string = HP_and_Progress_Bar.folderName;
					if (ImGui::TreeNode(string.c_str()))
					{
						ImGui::SetWindowFontScale(1);
						for (auto& textureName : HP_and_Progress_Bar.FileName)
						{
							static bool selected;
							std::string string = " - " + textureName;
							if (!string.compare(selectedObj))
							{
								if (textureWindow->GetOpen())
								{
									flags = ImGuiSelectableFlags_Disabled;
								}
								else
								{
									flags = ImGuiSelectableFlags_AllowDoubleClick;
								}
							}
							else
							{
								flags = ImGuiSelectableFlags_AllowDoubleClick;
							}
							Texture2D* texture = MyResourceSystem.GetTexture2DResource(textureName);
							if (ImGui::Selectable(string.c_str(), selected, flags))
							{
								if (ImGui::IsMouseReleased(0))
								{
									TextureImguiWindow::setTexture(textureWindow, texture, textureName);
									selectedObj = string;
								}
							}
							ImGui::Spacing();
						}
						ImGui::TreePop();
					}

					ImGui::TreePop();
				}
			}

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
