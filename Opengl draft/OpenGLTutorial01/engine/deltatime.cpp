#include "deltatime.h"

void DeltaTime::Update()
{
	FPS = duration_cast<frame>(steady_clock::now() - fpsTimer);
	if (FPS.count() >= 1)
	{
		fpsTimer = steady_clock::now();
		_dt = duration_cast<ms>(FPS).count() / 1000;
	}
}

double DeltaTime::Getdt()
{
	return _dt;
}

