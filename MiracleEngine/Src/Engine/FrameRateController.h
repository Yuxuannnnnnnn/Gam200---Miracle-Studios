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
typedef std::chrono::milliseconds ms;
using namespace std::chrono_literals;

class FrameRateController
{
public:
	FrameRateController();

	void Initialize();
  double UpdateFrameTime();
  double GetTotalRunTime() const;
  double GetFrameRate() const;

private:
	TimePoint PrevTime;
	TimePoint CurrTime;
	unsigned long long TotalTime;
	ms FrameTime;
  double FrameRate;

};


#endif
