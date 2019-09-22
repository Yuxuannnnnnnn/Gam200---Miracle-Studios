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

FrameRateController::FrameRateController()
{
	FrameTime = ms(0);              // Initialize the last frame time
}

void FrameRateController::Initialize()
{
	PrevTime = Time::now();
	CurrTime = Time::now();
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
	CurrTime = Time::now();

	// Recalculate the current time the frame's been running.
	FrameTime = std::chrono::duration_cast<ms>(CurrTime - PrevTime);



	PrevTime = Time::now();

	TotalTime += FrameTime.count(); // Increment TotalTime count

  FrameRate = 1000.0 / (double)FrameTime.count();

	return (double)FrameTime.count() / 1000.0;
}

double FrameRateController::GetTotalRunTime() const
{
  return (double)TotalTime / 1000.0;
}

double FrameRateController::GetFrameRate() const
{
  return FrameRate;
}
