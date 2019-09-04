#include "inputsystem.h"


void InputSystem::Init()
{

}

void InputSystem::Update()
{
	memcpy(_prevBuffer, _currBuffer, sizeof(unsigned char) * 256);
	//memset(currBuff, 0, sizeof(unsigned char) * 256);
	//GetKeyState(0);

	//Get current keyboard state
	GetKeyState(0);
	GetKeyboardState(_currBuffer);


	// move left a key
	if (_currBuffer[KEYB_A] & 0x80)
	{
		engine->_objectlist[0]._posCurr._x = engine->_objectlist[0]._posCurr._x - 50 * engine->_dt.Getdt();
	}
	else if (_currBuffer[KEYB_D] & 0x80)
	{
		engine->_objectlist[0]._posCurr._x = engine->_objectlist[0]._posCurr._x + 50 * engine->_dt.Getdt();
	}
	else if (_currBuffer[KEYB_W] & 0x80)
	{
		engine->_objectlist[0]._posCurr._y = engine->_objectlist[0]._posCurr._y + 50 * engine->_dt.Getdt();
	}
	else if (_currBuffer[KEYB_S] & 0x80)
	{
		engine->_objectlist[0]._posCurr._y = engine->_objectlist[0]._posCurr._y - 50 * engine->_dt.Getdt();
	}

	if (_currBuffer[KEYB_ENTER] & 0x80)
	{
		// create bullet
		Bullet bullet(5.0f, { engine->_objectlist[0]._posCurr._x, engine->_objectlist[0]._posCurr._y }, { 0.0f, 0.0f }, 0.0f, { 0.0f, 0.0f, 1.0f });
		bullet._type = BULLET;
		engine->_objectlist.push_back(bullet);
	}
}

void InputSystem::Exit() 
{

}