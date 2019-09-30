///////////////////////////////////////////////////////////////////////////////////////
//
//	FrameRateController.cpp
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#include "FrameRateController.h"

// #include <iostream>
// #include <limits>
// typedef std::numeric_limits< double > dbl;

FrameRateController::FrameRateController() :
	TotalTime{ 0 },
	FramePerSec{ 0 },
	LockedFPS{ 0 },
	FrameCounter{ 0 },
	FrameTimeCounter{},
	PrevTime_Main{},
	CurrTime_Main{},
	FrameTime_Main{},
	PrevTime_Sub{},
	CurrTime_Sub{},
	FrameTime_Sub{}
{
}

void FrameRateController::Initialize(short FPS)
{
	TotalTime = 0;

	PrevTime_Main = Time::now();
	CurrTime_Main = Time::now();
	

	LockedFPS = FPS;
	FrameCounter = 0;
	UpdateFPS();
}


double FrameRateController::UpdateFrameTime()
{
  // std::cout.precision(dbl::max_digits10);
  // std::cout<< FrameTime.count() << std::endl;
  // std::cout<< (double)FrameTime.count() / 1000.0 << std::endl;
  
	// Record the ending time for the frame.
	CurrTime_Main = Time::now();

	// Recalculate the current time the frame's been running.
	FrameTime_Main = std::chrono::duration_cast<ms>(CurrTime_Main - PrevTime_Main);

	// Increment TotalTime count
	TotalTime += FrameTime_Main.count();

	// FPS section
	if (LockedFPS)
	{
		FrameCounter++;
		FrameTimeCounter += FrameTime_Main;

		if (FrameTimeCounter > oneSec)
			UpdateFPS();
		
		if (FrameCounter >= LockedFPS)
		{
			ms waitTime = std::chrono::duration_cast<ms>(oneSec - FrameTimeCounter);

			TotalTime += waitTime.count();

			std::this_thread::sleep_for(waitTime);

			UpdateFPS();
		}
	}

	PrevTime_Main = Time::now();

	return (double)FrameTime_Main.count() / 1000.0;
}

void FrameRateController::StartTimeCounter()
{
	PrevTime_Sub = Time::now();
}

double FrameRateController::EndTimeCounter()
{
	CurrTime_Sub = Time::now();

	FrameTime_Sub = std::chrono::duration_cast<ms>(CurrTime_Sub - PrevTime_Sub);

	return (double)FrameTime_Sub.count();
}

double FrameRateController::GetTotalRunTime() const
{
  return (double)TotalTime / 1000.0;
}

double FrameRateController::GetFrameTime() const
{
	return (double)FrameTime_Main.count();
}

double FrameRateController::GetFrameRate() const
{
	if(FrameTime_Main.count())
		return (double)(1000 / FrameTime_Main.count());

	return 0;
}


short FrameRateController::GetFPS() const
{
	return FramePerSec;
}

void FrameRateController::UpdateFPS()
{
	FramePerSec = FrameCounter;

	FrameTimeCounter = ms(0);
	FrameCounter = 0;
}
