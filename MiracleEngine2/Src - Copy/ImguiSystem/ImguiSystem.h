#pragma once
#include "HierarchyImguiWindow.h"
#include "IBaseImguiWindow.h"
#include "AssetsImguiWindow.h"
#include "PreFabImguiWindow.h"
#include "TextureImguiWindow.h"


class ImguiSystem
{
private:
	ImVec4 clear_color;//For clearing opengl
	const Window& _window; //Reference to win32

	std::unordered_map<std::string, IBaseImguiWindow*> _ImguiWindows; //List of all ImGuiWindows

	
public:
	bool _editorMode;

	std::unordered_map<std::string, IBaseImguiWindow*> GetWindows()
	{
		return _ImguiWindows;
	}

	ImguiSystem(const Window& window); //Initialise ImguiSystem

	void UpdateFrame();	//Calls new frames for Imgui every loop

	void Render(); 	//Renders Imgui Windows and clears opengl buffer

	~ImguiSystem();	//Shutdown ImGui System



};

