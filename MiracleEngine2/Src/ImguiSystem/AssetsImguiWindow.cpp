#include "PrecompiledHeaders.h"
#include "AssetsImguiWindow.h"

//void AssetsImguiWindow::Update()
//{
//	const std::unordered_map<TypeIdGO, GameObject*>& objlist = EngineSystems::GetInstance()._prefabFactory->GetPrototypeList();
//
//	for (auto& gameObjectPair : objlist)
//	{
//		GameObject* gameObject = gameObjectPair.second; //Get GameObject* from std::pair
//
//		size_t uID = gameObject->Get_uID();				//Get Unique Number of each GameObject
//		unsigned ObjectTypeID = gameObject->GameObjectType(); //Get Object Type of each GameObject
//		std::string string = ToString((TypeIdGO)ObjectTypeID) + std::string(" ") + std::to_string(uID); // "Object Type + Object unique number" string
//
//		static bool selected;
//		if (ImGui::Selectable(string.c_str(), selected, ImGuiSelectableFlags_AllowDoubleClick))
//		{
//			if (ImGui::IsMouseReleased(0))
//			{
//				InspectionImguiWindow::InspectGameObject(gameObject);
//				//std::unordered_map < unsigned, IComponentSystem* > componentList = gameObject->GetComponentList(); //Get ComponenntList from each GameObject
//				//ShowGameObjectComponents(componentList);	//Show every Component of a GameObject
//				//ImGui::TreePop();
//				//ImGuiID id = ImGui::GetID(string.c_str());
//				//ImGui::GetStateStorage()->SetInt(id, 0);
//			}
//		}
//		ImGui::Spacing();
//		std::string string1 = "Create Game Object " + std::string(ToString((TypeIdGO)ObjectTypeID));
//		if (ImGui::Button(string1.c_str()))
//		{
//			GameObject* newGameobject = EngineSystems::GetInstance()._gameObjectFactory->CloneGameObject(gameObject);
//			dynamic_cast<TransformComponent*>(newGameobject->GetComponent(ComponentId::TRANSFORM_COMPONENT))->SetPos(Vector3::Vec3Zero);
//		}
//	}
//}
//

void AssetsImguiWindow::Update()
{
	// We specify a default position/size in case there's no data in the .ini file. Typically this isn't required! We only do it to make the Demo applications a little more welcoming.
	//ImVec2 main_viewport_pos = ImGui::GetMainViewport()->Pos;
	//ImGui::SetNextWindowPos(ImVec2(main_viewport_pos.x + 650, main_viewport_pos.y + 20), ImGuiCond_FirstUseEver);
	//ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_Always);
}