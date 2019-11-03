#include "PrecompiledHeaders.h"
#include "HierarchyImguiWindow.h"






HierarchyImguiWindow::HierarchyImguiWindow(bool open, ImGuiWindowFlags flags)
	:IBaseImguiWindow("Hierarchy", open, flags)
{
}




void HierarchyImguiWindow::Update()  //Update() function used in ImguiSystem.cpp
{
	ShowGameObjects();				//Show Every GameObject in the GameObjectList
}






void HierarchyImguiWindow::ShowGameObjects()			//Show Every GameObject in the GameObjectList - Used in Update() 
{
	ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.65f);

	if (ImGui::BeginMenuBar())
	{
		ImGui::Spacing();
		if (ImGui::BeginMenu("File Menu "))
		{
			ImGui::Spacing();
			if (ImGui::BeginMenu("Load  "))
			{
				if (ImGui::MenuItem("./Resources/TextFiles/States/TestLevel1.txt"))
				{
					EngineSystems::GetInstance()._gameObjectFactory->DeleteLevel();
					EngineSystems::GetInstance()._gameObjectFactory->FileRead_Level("./Resources/TextFiles/States/TestLevel.txt");
				}
				ImGui::EndMenu();
			}
			ImGui::Spacing();
			if (ImGui::MenuItem("Save   "))
			{
			}
			ImGui::Spacing();
			//if (ImGui::MenuItem("./Resources/TextFiles/States/TestLevel2.txt"))
			//{
			//
			//}

			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}


	const std::unordered_map<size_t, GameObject*>& objlist = EngineSystems::GetInstance()._gameObjectFactory->getObjectlist();

	size_t objListSize = objlist.size(); //number of total gameObjects in the list
	std::string totalGameObjects("Total Number of GameObjects in this level is: ");
	totalGameObjects += std::to_string(objListSize);  //"Total Number of GameObjects in this level is: objListSize" string
	
	ImGui::Text(totalGameObjects.c_str());	//Shows Total Number of GameObjects in this level on Imgui Window
	ImGui::Spacing();


	for (auto& gameObjectPair : objlist)
	{
		if (gameObjectPair.first < 1000)	//Do not print the prototypes
			continue;

		GameObject* gameObject = gameObjectPair.second; //Get GameObject* from std::pair

		size_t uID = gameObject->Get_uID();				//Get Unique Number of each GameObject
		unsigned ObjectTypeID = gameObject->GameObjectType(); //Get Object Type of each GameObject
		std::string string = ToString((TypeIdGO)ObjectTypeID) + std::string(" ") + std::to_string(uID); // "Object Type + Object unique number" string

		static bool selected;
		if (ImGui::Selectable(string.c_str(), selected, ImGuiSelectableFlags_AllowDoubleClick))
			if (ImGui::IsMouseReleased(0))
			{
				InspectionImguiWindow::InspectGameObject(gameObject);
				//std::unordered_map < unsigned, IComponentSystem* > componentList = gameObject->GetComponentList(); //Get ComponenntList from each GameObject
				//ShowGameObjectComponents(componentList);	//Show every Component of a GameObject
				//ImGui::TreePop();
				//ImGuiID id = ImGui::GetID(string.c_str());
				//ImGui::GetStateStorage()->SetInt(id, 0);
			}
	}
}



//void HierarchyImguiWindow::ShowGameObjectComponents(
//	std::unordered_map < unsigned, IComponentSystem* > componentList)	//Show every Component of a GameObject - Used in ShowGameObjects()
//{
//	for (auto& iComponentPair : componentList)
//	{
//		IComponentSystem* component = iComponentPair.second;	//Get component* from std::pair
//		unsigned componentType = iComponentPair.first;	//Get ComponentType from std::pair
//
//
//		if (ImGui::TreeNode(component->ComponentName().c_str()))
//		{
//
//			switch (componentType)	//Calls the Suitable Show Component function that the Object has
//			{
//			case (unsigned)ComponentId::TRANSFORM_COMPONENT:	ShowTransformComponent(component); break;
//			case (unsigned)ComponentId::GRAPHICS_COMPONENT:	ShowGraphicsComponent(component);  break;
//			case (unsigned)ComponentId::RIGIDBODY_COMPONENT:	ShowRigidBodyComponent(component); break;
//			case (unsigned)ComponentId::CIRCLECOLLIDER_COMPONENT:	ShowColliderComponent(component);  break;
//			case (unsigned)ComponentId::BOXCOLLIDER_COMPONENT:	ShowColliderComponent(component);  break;
//			case (unsigned)ComponentId::EDGECOLLIDER_COMPONENT:	ShowColliderComponent(component);  break;
//			case (unsigned)ComponentId::LOGIC_COMPONENT:		ShowLogicComponent(component);	   break;
//			case (unsigned)ComponentId::AUDIO_COMPONENT:		ShowAudioCommponent(component);	   break;
//			}
//
//			ImGui::Text("Text");
//
//			ImGui::TreePop();
//		}
//	}
//}






