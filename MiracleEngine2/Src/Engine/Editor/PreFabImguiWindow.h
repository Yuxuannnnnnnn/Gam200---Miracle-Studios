#pragma once
#include "IBaseImguiWindow.h"


class PreFabImguiWindow: public IBaseImguiWindow
{

public:
	PreFabImguiWindow(bool open = true,	//Set the settings for the imgui windows
		ImGuiWindowFlags flags = 0);

	void Update() override;
};

