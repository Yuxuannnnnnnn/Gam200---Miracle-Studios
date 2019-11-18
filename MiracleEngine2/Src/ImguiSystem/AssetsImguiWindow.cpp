#include "PrecompiledHeaders.h"
#include "AssetsImguiWindow.h"



void AssetsImguiWindow::Update()
{
	GameObject* obj = EngineSystems::GetInstance()._gameObjectFactory->CreateNewGameObject(true);
	static bool selected;
	if (ImGui::Selectable("Desrialise", selected, ImGuiSelectableFlags_AllowDoubleClick))
	{
		if (ImGui::IsMouseReleased(0))
		{
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