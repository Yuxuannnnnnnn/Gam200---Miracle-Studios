#include "PrecompiledHeaders.h"
#include "HierarchyImguiWindow.h"






HierarchyImguiWindow::HierarchyImguiWindow(bool open, ImGuiWindowFlags flags)
	:IBaseImguiWindow("Hierarchy", 1, 515, 340, 570, open, flags)
{
}




void HierarchyImguiWindow::Update()  //Update() function used in ImguiSystem.cpp
{
	std::string string1 = "New Scene ";
	if (ImGui::Button(string1.c_str()))
	{
		MyFactory.DeleteLevelNotPrefab();
	}

	ImGui::SameLine();
	std::string string2 = "Save Scene ";
	if (ImGui::Button(string2.c_str()))
	{
		OPENFILENAME ofn = { sizeof ofn };
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = _engineSystems._windowSystem->getWindow().Get_hwnd();

		char file[1024] = "\0";
		ofn.lpstrFile = file;
		ofn.nMaxFile = 1024;
		ofn.Flags = OFN_ALLOWMULTISELECT | OFN_EXPLORER;

		ofn.lpstrFilter = ".json\0.json";
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = "./Resources/TextFiles/Scenes/Scenes";
		ofn.nFilterIndex = 1;
		ofn.lpstrTitle = TEXT("Save Scene File");
		ofn.lpstrDefExt = "rle";

		if (GetSaveFileName(&ofn)) //If the user specifies a file nameand clicks the OK buttonand the function is successful, the return value is nonzero.
		{
			std::cout << ofn.lpstrFile;
			MyFactory.De_SerialiseLevel(ofn.lpstrFile);
		}
	}

	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();

	ShowGameObjects();				//Show Every GameObject in the GameObjectList
}




void HierarchyImguiWindow::ShowGameObjects()			//Show Every GameObject in the GameObjectList - Used in Update() 
{
	ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.65f);


	const std::unordered_map<size_t, GameObject*>& objlist = MyFactory.getObjectlist();
	//const std::unordered_map<std::string, GameObject*>& protolist = EngineSystems::GetInstance()._prefabFactory->GetPrototypeList();

	size_t objListSize = objlist.size(); //number of total gameObjects in the list

	std::string totalGameObjects("Total Number of GameObjects in Scene is: ");
	totalGameObjects += std::to_string(objListSize);  //"Total Number of GameObjects in this level is: objListSize" string
	
	ImGui::Text(totalGameObjects.c_str());	//Shows Total Number of GameObjects in this level on Imgui Window

	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();

	int i = 0;

	for (auto& gameObjectPair : objlist)
	{
		GameObject* gameObject = gameObjectPair.second; //Get GameObject* from std::pair

		size_t uID = gameObject->Get_uID();				//Get Unique Number of each GameObject

		IdentityComponent* IdCom = dynamic_cast<IdentityComponent*> (gameObject->GetComponent(ComponentId::CT_Identity));

		std::string ObjectTypeID = IdCom->GetName(); //Get Object Type of each GameObject
		std::string string = std::to_string(i) + " " + ObjectTypeID; // "Object Type + Object unique number" string

		static bool selected;
		if (ImGui::Selectable(string.c_str(), selected, ImGuiSelectableFlags_AllowDoubleClick))
			if (ImGui::IsMouseReleased(0))
			{
				InspectionImguiWindow::InspectGameObject(gameObject);
				//std::unordered_map < unsigned, IComponent* > componentList = gameObject->GetComponentList(); //Get ComponenntList from each GameObject
				//ShowGameObjectComponents(componentList);	//Show every Component of a GameObject
				//ImGui::TreePop();
				//ImGuiID id = ImGui::GetID(string.c_str());
				//ImGui::GetStateStorage()->SetInt(id, 0);
			}
		i++;
	}
}



//void HierarchyImguiWindow::ShowGameObjectComponents(
//	std::unordered_map < unsigned, IComponent* > componentList)	//Show every Component of a GameObject - Used in ShowGameObjects()
//{
//	for (auto& iComponentPair : componentList)
//	{
//		IComponent* component = iComponentPair.second;	//Get component* from std::pair
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






