#pragma once
#include "EngineSystems.h"

#ifndef ENGINE_H
#define ENGINE_H

#define LEVELEDITOR	1

class Engine
{
public:

	Engine(HINSTANCE hInstance, int nCmdShow) 	
	{
		_engineSystems.Init(hInstance, nCmdShow);
	}

	void Init();
	void Update();
	int Exit();


public:

};

#endif