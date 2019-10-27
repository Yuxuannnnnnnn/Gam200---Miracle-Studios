#include "PrecompiledHeaders.h"
#include "ImguiWindow.h"

#include <cstring>


ImguiWindowComponent::ImguiWindowComponent(const char* name, const bool open, const ImGuiWindowFlags flags)
	:_open{ open }, _name{"\0"}, _flags{ flags }
{
	strcpy_s(_name, name);

}



void ImguiWindowComponent::SetWindowTrue() //Set Imgui window to appear on screen
{
	_open = true;
}



void ImguiWindowComponent::Update()
{
	if (!_open) //if _open is false, imgui window will not be rendered/appear
	{
		return;
	}


	if (!ImGui::Begin(_name, &_open, _flags))
	{
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
		return;
	}


	ImGui::End();

}
