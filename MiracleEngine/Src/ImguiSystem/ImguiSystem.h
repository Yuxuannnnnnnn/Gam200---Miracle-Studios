#pragma once
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_win32.h"
#include "imgui_internal.h"


class ImguiSystem
{
private:
	ImVec4 clear_color;//for clearing opengl

public:
	ImguiSystem();

	void Init(const WindowsSystem& window); //Imgui system is initialised

	void UpdateFrame();	//Calls new frames for Imgui every loop

	void Render(); 	//Renders Imgui Windows and clears opengl buffer

	~ImguiSystem();	//Shutdown ImGui System



};

