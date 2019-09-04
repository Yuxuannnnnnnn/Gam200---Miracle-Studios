#pragma once
#include <chrono>
using namespace std;
using namespace chrono;

using frame = duration<int32_t, ratio<1, 60>>;
using ms = duration<float, milli>;

class DeltaTime
{
public:
	void Update();
	double Getdt();
private:
	frame FPS;
	double _dt;
	time_point<steady_clock> fpsTimer = steady_clock::now();
};