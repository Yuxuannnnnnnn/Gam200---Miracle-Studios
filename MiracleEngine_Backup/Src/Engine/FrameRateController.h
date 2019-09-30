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
typedef std::chrono::seconds s;

#define oneSec s(1)

using namespace std::chrono_literals;

class FrameRateController : public ISingleton<FrameRateController>
{
public:
	FrameRateController();

	void Initialize(short FPS = 0);
	double UpdateFrameTime();

	void StartTimeCounter();
	double EndTimeCounter();

	double GetTotalRunTime() const;
	double GetFrameTime() const;
	double GetFrameRate() const;

	short GetFPS() const;

private:
	void UpdateFPS();

private:
	unsigned long long TotalTime;
	short FramePerSec;
	short LockedFPS;
	short FrameCounter;
	ms FrameTimeCounter;

	TimePoint PrevTime_Main;
	TimePoint CurrTime_Main;
	ms FrameTime_Main;

	TimePoint PrevTime_Sub;
	TimePoint CurrTime_Sub;
	ms FrameTime_Sub;
};


#endif
