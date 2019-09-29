///////////////////////////////////////////////////////////////////////////////////////
//
//	FrameRateController.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _FRAME_RATE_CONTROLLER_H
#define _FRAME_RATE_CONTROLLER_H

#include <chrono>
#include <thread>
#include "PhysicSystem/ISingleton.h"

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::high_resolution_clock::time_point TimePoint;
typedef std::chrono::milliseconds ms;
using namespace std::chrono_literals;

class FrameRateController : public ISingleton<FrameRateController>
{
public:
	FrameRateController();

	void Initialize();

	double UpdateFrameTime();

	void StartTimeCounter();
	double EndTimeCounter();

	double GetTotalRunTime() const;
	double GetFrameRate() const;
	double GetFrameTime() const;
	ms GetFrameTimeMS() const;

private:
	unsigned long long TotalTime;
	double FrameRate;

	TimePoint PrevTime_Main;
	TimePoint CurrTime_Main;
	ms FrameTime_Main;

	TimePoint PrevTime_Sub;
	TimePoint CurrTime_Sub;
	ms FrameTime_Sub;
};


#endif
