#pragma once
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_win32.h"
#include "imgui_internal.h"


enum class ImguiWindows //The List of ImguiWindows 
{
	//HIERARCHY = 0,
	//INSPECTOR = 1,
	//SCENE = 2,

	 //COMMAND_DEBUG = 3,
	 //CONSOLE = 4,
	 //PROFILER = 5,
	 //MEMORY_DEBUG = 6,
	 //GLOBAL_SETTINGS = 7,
	 //FILE_SYSTEM = 8,
	 //TREE_GRAPH = 9,
	 //RESOURCE_WINDOW = 10,
	 //MATERIAL_EDITOR = 11,
	 //GAME = 12,

	 COUNT //for now, 3 priority ImguiWindow to code

};


class IBaseImguiWindow
{
private:
	bool _open;
	char _name[40]; //name up to 40 char
	ImGuiWindowFlags _flags;

public:
	IBaseImguiWindow(const char* name, bool open = true, 
		ImGuiWindowFlags flags = 0); 	//Set the settings for the imgui window

	bool& GetOpen(); //get the bool for whether the window is opened - bool may be set false by Imgui::begin when the window is closed
	
	const char* GetName() const; //get name for the window
	ImGuiWindowFlags GetFlags() const; //get flags for the window

	void SetWindowTrue(); //Set Imgui window to appear on screen
	void Setflags(ImGuiWindowFlags_ flag); //Set the flags for each imgui Window

	virtual void Update() = 0; //Derived ImguiWindow to override - Content for every frame
	
};

