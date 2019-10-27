#pragma once
#include "IBaseImguiWindow.h"


class HierarchyImguiWindow : public IBaseImguiWindow
{
public:

	HierarchyImguiWindow(bool open = true,	//Set the settings for the imgui window
		ImGuiWindowFlags flags = 0);		

	void Update() override; //Content for every frame

};

