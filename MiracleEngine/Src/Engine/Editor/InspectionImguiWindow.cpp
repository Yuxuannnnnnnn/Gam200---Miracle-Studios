#include "PrecompiledHeaders.h"
#include "InspectionImguiWindow.h"


GameObject* InspectionImguiWindow::_inspectObj = nullptr;
int InspectionImguiWindow::_componentSelected = 0;




InspectionImguiWindow::InspectionImguiWindow(bool open, ImGuiWindowFlags flags)
	:IBaseImguiWindow("Inspection", 1240, 15, 680, 580, open, flags, ImGuiCond_Once)
{
}

void InspectionImguiWindow::Update()
{
	if (MyFactory.CheckObjOrignialPointer(_inspectObj))
	{
		std::unordered_map < ComponentId, IComponent* >& componentList = (_inspectObj)->GetComponentList();

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
			const char* items[(int)(ComponentId::CT_Count) + 1];

			items[0] = "Add Component";

			for (int i = 1; i < (int)ComponentId::CT_Count + 1; i++)
			{
				items[i]= ToString((ComponentId)(i - 1));
			}
			//ImGui::Combo("Add Component", &item_current, items, (int)(ComponentId::COUNTCOMPONENT));

			static const char* item_current = items[0];            // Here our selection is a single pointer stored outside the object.
			if (ImGui::BeginCombo(" ", item_current, ImGuiComboFlags_NoArrowButton)) // The second parameter is the label previewed before opening the combo.
			{
				for (int n = 0; n < (int)(ComponentId::CT_Count) + 1; n++)
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
					OPENFILENAME ofn = { sizeof ofn };
					ZeroMemory(&ofn, sizeof(ofn));
					ofn.lStructSize = sizeof(ofn);
					ofn.hwndOwner = _engineSystems._windowSystem->getWindow().Get_hwnd();
					
					char file[1024] = "\0";
					std::string idType = dynamic_cast<IdentityComponent*>(_inspectObj->GetComponent(ComponentId::CT_Identity))->ObjectType();
					strncpy(file, idType.c_str(), idType.size());
					ofn.lpstrFile = file;
					ofn.nMaxFile = 1024;
					ofn.Flags = OFN_ALLOWMULTISELECT | OFN_EXPLORER | OFN_NOCHANGEDIR;
					
					ofn.lpstrFilter = ".json\0.json";
					ofn.lpstrFileTitle = NULL;
					ofn.nMaxFileTitle = 0;
					ofn.lpstrInitialDir = "./Resources/TextFiles/GameObjects";
					ofn.nFilterIndex = 1;
					ofn.lpstrTitle = TEXT("Save As");
					ofn.lpstrDefExt = "rle";

					if (GetSaveFileName(&ofn)) //If the user specifies a file nameand clicks the OK buttonand the function is successful, the return value is nonzero.
					{
						std::cout << ofn.lpstrFile;
						MyFactory.AddNewPrototypeAsset(_inspectObj, ofn.lpstrFile);	//Save Prototype into .json file but will overwrite existing file with same name
					}
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
			if (_inspectObj->GetComponent((ComponentId)_componentSelected))
				componentList[(ComponentId)_componentSelected]->Inspect();
			//}

			ImGui::EndChild();
			
			ImVec2 buttonSize(120, 20); // My button size

			if (ComponentId(_componentSelected) != ComponentId::CT_Identity && ComponentId(_componentSelected) != ComponentId::CT_Transform)
			{
				if (ImGui::Button("Delete Component ", buttonSize))
				{
					_inspectObj->RemoveComponent((ComponentId)_componentSelected);
				}
			}
			//ImGui::SameLine();
			//ImGui::TextDisabled("(?)");
			//if (ImGui::IsItemHovered())
			//{
			//	ImGui::BeginTooltip();
			//	ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
			//	ImGui::TextUnformatted("Component Data is saved into system but not into .json file");
			//	ImGui::PopTextWrapPos();
			//	ImGui::EndTooltip();
			//}
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
