#pragma once
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_win32.h"
#include "imgui_internal.h"

#include "ImguiWindow.h"

class ImguiSystem
{
private:
	ImVec4 clear_color;//for clearing opengl
	const Window& _window;


public:
	ImguiSystem(const Window& window);

	void UpdateFrame();	//Calls new frames for Imgui every loop

	void Render(); 	//Renders Imgui Windows and clears opengl buffer

	~ImguiSystem();	//Shutdown ImGui System



};

