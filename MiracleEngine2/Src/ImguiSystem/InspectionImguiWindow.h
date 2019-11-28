#pragma once
#include <IBaseImguiWindow.h>

#ifndef INSPECTION_IMGUI_WINDOW_H
#define INSPECTION_IMGUI_WINDOW_H


//When an Object is Clicked in the Hierarchy Window,
//The Inspection window will show all the components of the Objects
class InspectionImguiWindow : public IBaseImguiWindow
{
	static GameObject* _inspectObj;	//Changed based on picking OR clicking on object inside the HierarchyImguWindow

public:
	InspectionImguiWindow(bool open = true,	//Set the settings for the imgui windows
		ImGuiWindowFlags flags = 0);

	void Update() override
	{
		if (_inspectObj)
		{

			std::unordered_map < ComponentId, IComponentSystem* > componentList = _inspectObj->GetComponentList();
			for (auto& commponentPair : componentList)
			{
				if (ImGui::CollapsingHeader(commponentPair.second->ComponentName().c_str()))
				{
					commponentPair.second->Inspect();
				}
			}
		}
	}

	static void InspectGameObject(GameObject* inspectObj)
	{
		_inspectObj = inspectObj;

		//size_t uID = _inspectObj->Get_uID();				//Get Unique Number of each GameObject
		//unsigned ObjectTypeID = _inspectObj->GameObjectType(); //Get Object Type of each GameObject
		//std::string string = std::string("Inspection Window of ") + ToString((TypeIdGO)ObjectTypeID) + " " + std::to_string(uID); // "Object Type + Object unique number" string
		//IBaseImguiWindow::SetName(string.c_str());
	}
};

#endif