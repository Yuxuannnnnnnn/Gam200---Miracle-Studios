#include "PrecompiledHeaders.h"
#include "InspectionImguiWindow.h"


GameObject* InspectionImguiWindow::_inspectObj = nullptr;
int InspectionImguiWindow::_componentSelected = 0;




InspectionImguiWindow::InspectionImguiWindow(bool open, ImGuiWindowFlags flags)
	:IBaseImguiWindow("Inspection", 1301, 15, 620, 600, open, flags)
{
}

void InspectionImguiWindow::Update()
{
	if (_engineSystems._gameObjectFactory->CheckObjOrignialPointer(_inspectObj))
	{
		std::unordered_map < ComponentId, IComponentSystem* > componentList = (_inspectObj)->GetComponentList();

		ImGui::BeginChild("left pane", ImVec2(215, 0), true);
		{
			for (auto& commponentPair : componentList)
			{
				char label[128];
				sprintf(label, commponentPair.second->ComponentName().c_str());
				if (ImGui::Selectable(label, _componentSelected == (int)(commponentPair.first)))
					_componentSelected = (int)(commponentPair.first);
			}

			//if (ImGui::Button("Add Component "))
			//{ }

		// Simplified one-liner Combo() API, using values packed in a single constant string
			//int item_current = -1;
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();

			ImGui::Separator();
			ImGui::Spacing();
			const char* items[(int)(ComponentId::COUNTCOMPONENT) + 1];

			items[0] = "Add Component";

			for (int i = 1; i < (int)ComponentId::COUNTCOMPONENT + 1; i++)
			{
				items[i]= ToString((ComponentId)(i - 1));
			}
			//ImGui::Combo("Add Component", &item_current, items, (int)(ComponentId::COUNTCOMPONENT));

			static const char* item_current = items[0];            // Here our selection is a single pointer stored outside the object.
			if (ImGui::BeginCombo(" ", item_current, ImGuiComboFlags_NoArrowButton)) // The second parameter is the label previewed before opening the combo.
			{
				for (int n = 0; n < (int)(ComponentId::COUNTCOMPONENT) + 1; n++)
				{
					bool is_selected = (item_current == items[n]);
					if (ImGui::Selectable(items[n], is_selected))
					{
						//item_current = items[n];
						if (n != 0)
						{
							_inspectObj->AddComponent((ComponentId)(n-1));
						}
					}

					//if (is_selected);
					//ImGui::SetItemDefaultFocus();   // Set the initial focus when opening the combo (scrolling + for keyboard navigation support in the upcoming navigation branch)

				}
				ImGui::EndCombo();
			}

			ImGui::Spacing();
			ImGui::Spacing();			
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Separator();
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();



			if (_inspectObj->Get_uID() <= 1000)
			{
				//ImGui::SetWindowFontScale(1.1);
				//ImGui::Indent(400.0f);
				ImVec2 buttonSize(120, 20); // My button size
				//ImGui::SetCursorPos(ImVec2(500, 500));

				if (ImGui::Button("SAVE Prototype ", buttonSize))
				{
					_inspectObj->DeSerialise();	//Save Prototype into .json file but will overwrite existing file with same name
				}
				ImGui::SameLine();
				ImGui::TextDisabled("(?)");
				if (ImGui::IsItemHovered())
				{
					ImGui::BeginTooltip();
					ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
					ImGui::TextUnformatted("Saves Prototype file into ./Resources/TextFiles/GameObjects, File Name corressponds to GameObjectType.json");
					ImGui::PopTextWrapPos();
					ImGui::EndTooltip();
				}
			}
		}
		ImGui::EndChild();

		ImGui::SameLine();

		ImGui::BeginGroup();
		{
			ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing() - 20)); // Leave room for 1 line below us
			//if (ImGui::CollapsingHeader(commponentPair.second->ComponentName().c_str()))
			//{
			componentList[(ComponentId)_componentSelected]->Inspect();
			//}
			ImGui::EndChild();

			ImVec2 buttonSize(120, 20); // My button size
			if (ImGui::Button("Save Component ", buttonSize))
			{
				componentList[(ComponentId)_componentSelected]->SaveComponent();
			}
			ImGui::SameLine();
			ImGui::TextDisabled("(?)");
			if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
				ImGui::TextUnformatted("Component Data is saved into system but not into .json file");
				ImGui::PopTextWrapPos();
				ImGui::EndTooltip();
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
	_componentSelected = 0;
	_inspectObj = inspectObj;
	//size_t uID = _inspectObj->Get_uID();				//Get Unique Number of each GameObject
	//unsigned ObjectTypeID = _inspectObj->GameObjectType(); //Get Object Type of each GameObject
	//std::string string = std::string("Inspection Window of ") + ToString((TypeIdGO)ObjectTypeID) + " " + std::to_string(uID); // "Object Type + Object unique number" string
	//IBaseImguiWindow::SetName(string.c_str());
}
