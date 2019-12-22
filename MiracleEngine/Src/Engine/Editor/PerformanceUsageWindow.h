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
#include "IBaseImguiWindow.h"

class PerformanceUsageWindow: public IBaseImguiWindow
{
public:
	short FPS;
	double PerFrameTime;
	double InputFrameTime;
	double LogicFrameTime;
	double PhysicFrameTime;
	double AudioFrameTime;
	double GraphicFrameTime;
	double IMGUIFrameTime;

public:
	PerformanceUsageWindow::PerformanceUsageWindow(bool open = true, ImGuiWindowFlags flags = 0)
		:IBaseImguiWindow("PerformanceUsage", 1690, 800, 200, 200, open, flags),
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

	PerformanceUsageWindow(const PerformanceUsageWindow& rhs) = delete;
	PerformanceUsageWindow& operator= (const PerformanceUsageWindow& rhs) = delete;
	~PerformanceUsageWindow() {}

	void Update() override;
};

#endif
