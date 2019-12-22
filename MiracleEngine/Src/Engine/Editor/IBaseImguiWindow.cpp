#include "PrecompiledHeaders.h"
#include "IBaseImguiWindow.h"

#include <cstring>


IBaseImguiWindow::IBaseImguiWindow(const char* name, int xPos, int yPos, unsigned width, unsigned height, bool open, ImGuiWindowFlags flags, ImGuiCond_ _windowCondition)	//Set the settings for the imgui window
	:_open{ open }, _name{ "\0" }, _flags{ flags }, _xPos{ xPos }, _yPos{ yPos }, _width{ width }, _height{ height }, _windowCondition{ _windowCondition }
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

void IBaseImguiWindow::SetName(const char * name)
{
	strcpy_s(_name, name);
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



