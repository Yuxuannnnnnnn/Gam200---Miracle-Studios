#pragma once
#include "IBaseImguiWindow.h"


class AssetsImguiWindow: public IBaseImguiWindow
{
public:

	AssetsImguiWindow(bool open = true,	//Set the settings for the imgui window
		ImGuiWindowFlags flags = ImGuiWindowFlags_::ImGuiWindowFlags_MenuBar)
		:IBaseImguiWindow("Assets", open, flags)
	{
	}

	void Update() override;
};

