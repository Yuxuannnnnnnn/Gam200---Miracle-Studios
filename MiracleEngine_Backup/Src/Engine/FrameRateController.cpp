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
	FrameRate{ 0 }
{
	FrameTime_Main = ms(0);
	FrameTime_Sub = ms(0);
}

void FrameRateController::Initialize()
{
	PrevTime_Main = Time::now();
	CurrTime_Main = Time::now();
	TotalTime = 0;
	FrameRate = 0;
}


double FrameRateController::UpdateFrameTime()
{
  // std::cout.precision(dbl::max_digits10);
  // std::this_thread::sleep_for(0.5s);
  // std::cout<< FrameTime.count() << std::endl;
  // std::cout<< (double)FrameTime.count() / 1000.0 << std::endl;
  
	// Record the ending time for the frame.
	CurrTime_Main = Time::now();

	// Recalculate the current time the frame's been running.
	FrameTime_Main = std::chrono::duration_cast<ms>(CurrTime_Main - PrevTime_Main);

	PrevTime_Main = Time::now();

	TotalTime += FrameTime_Main.count(); // Increment TotalTime count

  FrameRate = 1000.0 / (double)FrameTime_Main.count();

	return (double)FrameTime_Main.count() / 1000.0;
}

double FrameRateController::GetTotalRunTime() const
{
  return (double)TotalTime / 1000.0;
}

double FrameRateController::GetFrameRate() const
{
  return FrameRate;
}

double FrameRateController::GetFrameTime() const
{
	return (double)FrameTime_Main.count();
}

void FrameRateController::StartTimeCounter()
{
	PrevTime_Sub = Time::now();
}

double FrameRateController::EndTimeCounter()
{
	CurrTime_Sub = Time::now();

	FrameTime_Sub = std::chrono::duration_cast<ms>(CurrTime_Sub - PrevTime_Sub);

	return (double)FrameTime_Main.count();
}

