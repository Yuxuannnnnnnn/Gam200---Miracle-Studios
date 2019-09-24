#pragma once

#include "keydef.h"

//#include "../Isystem.h"
//#include "../engine/engine.h"

class InputSystem //: public ISystem
{
public:
	void Init();
	void Update();
	void Exit();
private:
	unsigned char _currBuffer[256];
	unsigned char _prevBuffer[256];
};