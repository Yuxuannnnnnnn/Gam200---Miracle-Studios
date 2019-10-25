#pragma once
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_win32.h"
#include "imgui_internal.h"


class ImguiSystem
{
public:
	//Constructor, When a ImguiSystem Object is instantiated
	//the Imgui system is initialised
	ImguiSystem();


	void Update();



	//Destructor should be called when the program is exiting
	~ImguiSystem();



};

