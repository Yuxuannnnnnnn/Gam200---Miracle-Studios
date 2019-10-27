#pragma once
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_win32.h"
#include "imgui_internal.h"


class ImguiWindowComponent: public IComponentSystem
{
private:
	bool _open;
	char _name[40]; //name up to 40 char
	ImGuiWindowFlags _flags;

public:
	//Set the settings for the imgui window to be rendered
	ImguiWindowComponent(const char* name, bool open = true, ImGuiWindowFlags flags = 0);

	void SetWindowTrue(); //Set Imgui window to appear on screen

	void Update(); //Creates window at every frame

	
};

