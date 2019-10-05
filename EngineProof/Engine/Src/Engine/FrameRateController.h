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

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::high_resolution_clock::time_point TimePoint;
typedef std::chrono::nanoseconds ns;
typedef std::chrono::milliseconds ms;
typedef std::chrono::seconds s;

#define oneSecNs 1000000000.0

using namespace std::chrono_literals;

class FrameRateController
{
public:
	FrameRateController();

	void Initialize(double FPS = 0);
	double UpdateFrameTime();

	void StartTimeCounter();
	double EndTimeCounter();

	double GetTotalRunTime() const;
	double GetFrameTime() const;

	short GetFPS() const;

private:

private:
	unsigned long long TotalTime;
	
	long long LockedFPS;
	short FramePerSec;

	TimePoint PrevTime_Main;
	TimePoint CurrTime_Main;
	ns FrameTime_Main;

	TimePoint PrevTime_Sub;
	TimePoint CurrTime_Sub;
	ns FrameTime_Sub;
};


#endif
