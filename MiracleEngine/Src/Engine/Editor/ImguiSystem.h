#pragma once
#include "HierarchyImguiWindow.h"
#include "IBaseImguiWindow.h"
#include "AssetsImguiWindow.h"
#include "PreFabImguiWindow.h"
#include "TextureImguiWindow.h"
#include "PerformanceUsageWindow.h"
#include "PopUpBoxImguiWindow.h"


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

	IBaseImguiWindow* GetWindow(std::string windowName)
	{
		if(_ImguiWindows.find(windowName) != _ImguiWindows.end())
			return _ImguiWindows[windowName];

		return nullptr;
	}

	ImguiSystem(const Window& window); //Initialise ImguiSystem

	void UpdateFrame();	//Calls new frames for Imgui every loop

	void Render(); 	//Renders Imgui Windows and clears opengl buffer

	~ImguiSystem();	//Shutdown ImGui System

	void Init();
};

#define MyPerformanceUsage (*(dynamic_cast<PerformanceUsageWindow *>(MyImguiSystem.GetWindow("PerformanceUsage"))))
#define MyPopUpBox (*(dynamic_cast<PopUpBoxImguiWindow *>(MyImguiSystem.GetWindow("PopUpBox"))))
#define MyInspectionWindow (*(dynamic_cast<InspectionImguiWindow *>(MyImguiSystem.GetWindow("Inspector"))))

