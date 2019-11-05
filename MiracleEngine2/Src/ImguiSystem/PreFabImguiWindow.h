#pragma once
#include "IBaseImguiWindow.h"


class PreFabImguiWindow: public IBaseImguiWindow
{
public:

	PreFabImguiWindow(bool open = true,	//Set the settings for the imgui window
		ImGuiWindowFlags flags = ImGuiWindowFlags_::ImGuiWindowFlags_MenuBar)
		:IBaseImguiWindow("PreFab", open, flags)
	{
	}

	void Update() override;
};

