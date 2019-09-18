#pragma once

#include "../GraphicsSystem/GraphicsSystem.h"
#include "FrameRateController.h"

class Engine
{
public:
	void Init();
	void Update();
	void Exit();
private:
	GraphicsSystem* _graphicSystem;
	FrameRateController* _frameController;
};

