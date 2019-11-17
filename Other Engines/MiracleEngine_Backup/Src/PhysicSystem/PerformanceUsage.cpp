///////////////////////////////////////////////////////////////////////////////////////
//
//	PerformanceUsage.h
//	
//	Authors: yuu, yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////

#include "PerformanceUsage.h"

PerformanceUsage::PerformanceUsage() :
	FPS{ 0 },
	FrameRate{ 0 },
	PerFrameTime{ 0 },
	InputFrameTime{ 0 },
	LogicFrameTime{ 0 },
	PhysicFrameTime{ 0 },
	GraphicFrameTime{ 0 }
{

}

void PerformanceUsage::PrintPerformanceUsage()
{
	if (!PerFrameTime)
		return;

	PerFrameTime = PerFrameTime * 1000 * 1000;

	double input = InputFrameTime / PerFrameTime * 100;
	double logic = LogicFrameTime / PerFrameTime * 100;
	double physic = PhysicFrameTime / PerFrameTime * 100;
	double graphic = GraphicFrameTime / PerFrameTime * 100;

	ImGui::Text("Engine Frame Rate : %.3f ", FrameRate);
	ImGui::Text("Engine FPS : %d ", FPS);
	ImGui::Text("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	ImGui::Text("Input usage   : %.3f%% ", input);
	ImGui::Text("Logic usage   : %.3f%% ", logic);
	ImGui::Text("Physic usage  : %.3f%% ", physic);
	ImGui::Text("Graphic usage : %.3f%% ", graphic);
}