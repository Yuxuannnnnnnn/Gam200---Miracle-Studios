#include "PrecompiledHeaders.h"
#include "InspectionImguiWindow.h"


GameObject* InspectionImguiWindow::_inspectObj = nullptr;



InspectionImguiWindow::InspectionImguiWindow(bool open, ImGuiWindowFlags flags)
	:IBaseImguiWindow("Inspection", 1301, 15, 620, 600, open, flags)
{
}

void InspectionImguiWindow::Update()
{
	if (_engineSystems._gameObjectFactory->CheckObjOrignialPointer(_inspectObj))
	{
		std::unordered_map < ComponentId, IComponentSystem* > componentList = (_inspectObj)->GetComponentList();


		static int selected = 0;
		ImGui::BeginChild("left pane", ImVec2(215, 0), true);
		for (auto& commponentPair : componentList)
		{
			char label[128];
			sprintf(label, commponentPair.second->ComponentName().c_str());
			if (ImGui::Selectable(label, selected == (int)(commponentPair.first)))
				selected = (int)(commponentPair.first);
		}
		ImGui::EndChild();
		ImGui::SameLine();

		ImGui::BeginGroup();
		{
			ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing() - 20)); // Leave room for 1 line below us
			//if (ImGui::CollapsingHeader(commponentPair.second->ComponentName().c_str()))
			//{
			componentList[(ComponentId)selected]->Inspect();
			//}
			ImGui::EndChild();
			if (_inspectObj->Get_uID() <= 1000)
			{
				//ImGui::SetWindowFontScale(1.1);
				//ImGui::Indent(400.0f);
				ImVec2 buttonSize(50, 25); // My button size
				//ImGui::SetCursorPos(ImVec2(500, 500));
				if(ImGui::Button("SAVE", buttonSize))
				{

				}
			}

		}
		ImGui::EndGroup();
	}
	else
	{
		_inspectObj = nullptr;
	}

}
void InspectionImguiWindow::InspectGameObject(GameObject* inspectObj)
{
	_inspectObj = inspectObj;
	//size_t uID = _inspectObj->Get_uID();				//Get Unique Number of each GameObject
	//unsigned ObjectTypeID = _inspectObj->GameObjectType(); //Get Object Type of each GameObject
	//std::string string = std::string("Inspection Window of ") + ToString((TypeIdGO)ObjectTypeID) + " " + std::to_string(uID); // "Object Type + Object unique number" string
	//IBaseImguiWindow::SetName(string.c_str());
}
