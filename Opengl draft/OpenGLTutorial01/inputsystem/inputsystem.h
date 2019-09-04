#pragma once

#include <windows.h>

#include "keydef.h"
#include "../Isystem.h"
#include "../engine/engine.h"

class InputSystem : public ISystem
{
public:
	void Init() override;
	void Update() override;
	void Exit() override;
private:
	unsigned char _currBuffer[256];
	unsigned char _prevBuffer[256];
};