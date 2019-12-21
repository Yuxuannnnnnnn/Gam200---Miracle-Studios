///////////////////////////////////////////////////////////////////////////////////////
//
//	PerformanceUsage.h
//	
//	Authors: yuu, yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#include "PrecompiledHeaders.h"
#include "PerformanceUsage.h"

PerformanceUsage::PerformanceUsage() :
	FPS{ 0 },
	PerFrameTime{ 0 },
	InputFrameTime{ 0 },
	LogicFrameTime{ 0 },
	PhysicFrameTime{ 0 },
	AudioFrameTime{ 0 },
	GraphicFrameTime{ 0 },
	IMGUIFrameTime{ 0 }
{

}

void PerformanceUsage::PrintPerformanceUsage()
{
	if (_GlobalContainer._imguiSystem->_editorMode)
	{
		if (!PerFrameTime)
			return;

		double input = (InputFrameTime / PerFrameTime) * 100;
		double logic = (LogicFrameTime / PerFrameTime) * 100;
		double physic = (PhysicFrameTime / PerFrameTime) * 100;
		double audio = (AudioFrameTime / PerFrameTime) * 100;
		double graphic = (GraphicFrameTime / PerFrameTime) * 100;
		double imgui = (IMGUIFrameTime / PerFrameTime) * 100;

		double others = 100 - input - logic - physic - graphic - imgui;

		ImGui::Begin("FPS Performance Viewer");
		ImGui::Text("Engine FPS : %d ", FPS);
		ImGui::Text("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
		ImGui::Text("Input usage   : %.3f%% ", input);
		ImGui::Text("Logic usage   : %.3f%% ", logic);
		ImGui::Text("Physic usage  : %.3f%% ", physic);
		ImGui::Text("Audio usage   : %.3f%% ", audio);
		ImGui::Text("Graphic usage : %.3f%% ", graphic);
		ImGui::Text("IMGUI usage   : %.3f%% ", imgui);
		ImGui::Text("Others usage  : %.3f%% ", others);
		ImGui::End();

		InputFrameTime = 0.0;
		LogicFrameTime = 0.0;
		PhysicFrameTime = 0.0;
		AudioFrameTime = 0.0;
		GraphicFrameTime = 0.0;
		IMGUIFrameTime = 0.0;

	}
}