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
	
	FrameRateController(double FPS); //Constructor sets the FPS rate

	void SetFPS(double FPS = 0);	//Function can be used to set FPS dynamically during run time
	double UpdateFrameTime();

	void StartTimeCounter();
	double EndTimeCounter();

	double GetTotalRunTime() const;
	double GetFrameTime() const;

	short GetFPS() const;

	int GetSteps() const;
	double GetLockedDt() const;

	double Getdt() const;

private:
	unsigned long long TotalTime;
	long long accumulatedTime;

	int currentNumberOfSteps;

	long long LockedFPS;
	short FramePerSec;

	TimePoint PrevTime_Main;
	TimePoint CurrTime_Main;
	ns FrameTime_Main;

	TimePoint PrevTime_Sub;
	TimePoint CurrTime_Sub;
	ns FrameTime_Sub;

	double _dt;
};


#endif
