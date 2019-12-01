#pragma once
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_win32.h"
#include "imgui_internal.h"



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

	void SetName(const char* name);
	void SetWindowTrue(); //Set Imgui window to appear on screen
	void Setflags(ImGuiWindowFlags_ flag); //Set the flags for each imgui Window

	virtual void Update() = 0; //Derived ImguiWindow to override - Content for every frame
	
};

