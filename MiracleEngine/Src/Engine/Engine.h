#pragma once

#include "../GraphicsSystem/GraphicsSystem.h"

class Engine
{
public:
	void Init();
	void Update();
	void Exit();
private:
	GraphicsSystem* _graphicSystem;
};

