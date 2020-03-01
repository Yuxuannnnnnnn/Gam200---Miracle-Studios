#pragma once
#include "GlobalContainer.h"

#ifndef ENGINE_H
#define ENGINE_H

class Engine
{
public:
	Engine(HINSTANCE hInstance, int nCmdShow);

	void Init();
	void Update();
	int Exit();
};

#endif