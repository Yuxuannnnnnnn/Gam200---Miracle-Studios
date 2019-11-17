#include "PrecompiledHeaders.h"
#include "IBaseImguiWindow.h"

#include <cstring>


IBaseImguiWindow::IBaseImguiWindow(const char* name, const bool open, 
	const ImGuiWindowFlags flags)				//Set the settings for the imgui window
	:_open{ open }, _name{"\0"}, _flags{ flags }
{
	strcpy_s(_name, name);
}

bool& IBaseImguiWindow::GetOpen()  //get the bool for whether the window is opened - bool may be set false by Imgui::begin when the window is closed
{
	return _open;
}


const char* IBaseImguiWindow::GetName() const  //get name for the window
{
	return _name;
}

ImGuiWindowFlags IBaseImguiWindow::GetFlags() const  //get flags for the window
{
	return _flags;
}


void IBaseImguiWindow::SetWindowTrue() //Set Imgui window to appear on screen
{
	_open = true;
}


void IBaseImguiWindow::Setflags(ImGuiWindowFlags_ flag) //Set the flags for each imgui Window
{
	_flags |= flag;
}




