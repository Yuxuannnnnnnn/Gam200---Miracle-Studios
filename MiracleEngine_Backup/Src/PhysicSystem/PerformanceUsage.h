///////////////////////////////////////////////////////////////////////////////////////
//
//	PerformanceUsage.h
//	
//	Authors: yuu, yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _PERFORMANCE_USAGE_H
#define _PERFORMANCE_USAGE_H
#include "../Imgui/imgui.h"
#include "../Imgui/imgui_impl_win32.h"
#include "../Imgui/imgui_impl_opengl3.h"
#include "../Imgui/imgui_internal.h"

class PerformanceUsage
{
public:
	short FPS;
	double FrameRate;
	double PerFrameTime;
	double InputFrameTime;
	double LogicFrameTime;
	double PhysicFrameTime;
	double GraphicFrameTime;

public:
	PerformanceUsage();
	PerformanceUsage(const PerformanceUsage& rhs) = delete;
	PerformanceUsage& operator= (const PerformanceUsage& rhs) = delete;
	~PerformanceUsage() {}

	void PrintPerformanceUsage();
};

#endif