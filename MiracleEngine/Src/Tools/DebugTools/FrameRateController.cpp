///////////////////////////////////////////////////////////////////////////////////////
//
//	FrameRateController.cpp
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#include "PrecompiledHeaders.h"
#include "FrameRateController.h"

 #include <iostream>
// #include <limits>
// typedef std::numeric_limits< double > dbl;



FrameRateController::FrameRateController(double FPS) :
	TotalTime{ 0 },
	accumulatedTime{ 0 },
	currentNumberOfSteps{ 0 },
	LockedFPS{ 0 },
	FramePerSec{ 0 },
	PrevTime_Main{},
	CurrTime_Main{},
	FrameTime_Main{},
	PrevTime_Sub{},
	CurrTime_Sub{},
	FrameTime_Sub{}
{
	TotalTime = 0;

	PrevTime_Main = Time::now();
	CurrTime_Main = Time::now();
	SetFPS(60);
}

void FrameRateController::SetFPS(double FPS)
{
	LockedFPS = (long long)(oneSecNs / FPS);
}


double FrameRateController::UpdateFrameTime()
{
  // std::cout.precision(dbl::max_digits10);
  // std::cout<< FrameTime.count() << std::endl;
  // std::cout<< (double)FrameTime.count() / 1000.0 << std::endl;
  
	ns deltaTime;

	// Record the ending time for the frame.
	CurrTime_Main = Time::now();
	currentNumberOfSteps = 0;

	// Recalculate the current time the frame's been running.
	FrameTime_Main = std::chrono::duration_cast<ns>(CurrTime_Main - PrevTime_Main);

	deltaTime = FrameTime_Main;

	// FPS section
	/*if (LockedFPS && FrameTime_Main.count() < LockedFPS)
	{
		ns waitTime(LockedFPS - FrameTime_Main.count());

		std::this_thread::sleep_for(waitTime);

		deltaTime += waitTime;
	}*/

	// Increment TotalTime count
	TotalTime += deltaTime.count();

	if (LockedFPS)
	{
		accumulatedTime += deltaTime.count();

		while (accumulatedTime >= LockedFPS)
		{
			accumulatedTime -= LockedFPS;
			currentNumberOfSteps++;
		}

	}
	

	FramePerSec = (short)(oneSecNs / deltaTime.count());
	
	PrevTime_Main = Time::now();

	return (double)deltaTime.count() / oneSecNs;
}

void FrameRateController::StartTimeCounter()
{
	PrevTime_Sub = Time::now();
}

double FrameRateController::EndTimeCounter()
{
	CurrTime_Sub = Time::now();

	FrameTime_Sub = std::chrono::duration_cast<ns>(CurrTime_Sub - PrevTime_Sub);

	return (double)FrameTime_Sub.count();
}

double FrameRateController::GetTotalRunTime() const
{
  return (double)TotalTime / (double)oneSecNs;
}

double FrameRateController::GetFrameTime() const
{
	return (double)FrameTime_Main.count();
}

short FrameRateController::GetFPS() const
{
	return FramePerSec;
}

int FrameRateController::GetSteps() const
{
	return currentNumberOfSteps;
}

double FrameRateController::GetLockedDt() const
{
	return (double)LockedFPS;
}