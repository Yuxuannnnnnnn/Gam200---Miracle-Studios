#pragma once
#include <IBaseImguiWindow.h>



//When an Object is Clicked in the Hierarchy Window,
//The Inspection window will show all the components of the Objects
class InspectionImguiWindow : public IBaseImguiWindow
{

	//static GameObject
public:
	InspectionImguiWindow(bool open = true,	//Set the settings for the imgui window
		ImGuiWindowFlags flags = 0);

	void Update() override;
};

