#pragma once
#include "IBaseImguiWindow.h"
#include "GameObject/GameObject.h"

#ifndef INSPECTION_IMGUI_WINDOW_H
#define INSPECTION_IMGUI_WINDOW_H


//When an Object is Clicked in the Hierarchy Window,
//The Inspection window will show all the components of the Objects
class InspectionImguiWindow : public IBaseImguiWindow
{
	static GameObject* _inspectObj;	//Changed based on picking OR clicking on object inside the HierarchyImguWindow
	static int _componentSelected;

public:
	InspectionImguiWindow(bool open = true,	//Set the settings for the imgui windows
		ImGuiWindowFlags flags = 0);

	void Update() override;


	static void InspectGameObject(GameObject* inspectObj);

};

#endif