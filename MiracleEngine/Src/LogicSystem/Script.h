#pragma once
#include "PrecompiledHeaders.h"

namespace Script_1 {
	void Update()
	{
		std::cout << "SCRIPT - 1" << std::endl;
	}
}

namespace Script_2 {
	void Update()
	{
		std::cout << "SCRIPT - 2" << std::endl;
	}
}

namespace Script_HealthMinus {
	void Update(int& health, int changeVal)
	{
		std::cout << "SCRIPT - 3" << std::endl;
	}
}

namespace Script_Input {
	enum Logic_Keyboard_Style {
		INPUT_OFF = 0,

		INPUT_MAIN_MENU,

		INPUT_INGAME,
		INPUT_INGAME_PAUSE_ESCAPE,
		INPUT_INGAME_PAUSE_LEVELUP,
	};

	Logic_Keyboard_Style _InputStyle{ INPUT_OFF };
	//InputSystem keyboard;

	// functions to check key UpDownHold for chosen keys
	// GetKeyDown(AE_LEFT); GetKeyUp(ESCAPE); GetKeyHold(MB_RIGHT);
	void Logic_Input_MainMenu() // for menu input
	{
		// for MainMenu
	}
	Vector3 Logic_Input_Ingame() // for in game input
	{
		Vector3 moveResult; // for throwing resultant movement force to player

	// OTHERS
		//if (keyboard.KeyDown(KEYB_ESCAPE)) // open pause menu
		//	_InputStyle = INGAME_PAUSE_ESCAPE;
		//// MOVEMENT		// in future need to do a speed multi OR leave it to phy to do it?
		//if (keyboard.KeyDown(KEYB_W))
		//	moveResult.Y(1.0f);
		//if (keyboard.KeyDown(KEYB_S))
		//	moveResult.Y(-1.0f);
		//if (keyboard.KeyDown(KEYB_D))
		//	moveResult.X(1.0f);
		//if (keyboard.KeyDown(KEYB_A))
		//	moveResult.X(-1.0f);
		//// MOUSE
		//if (keyboard.KeyDown(MOUSE_LBUTTON))
		//	(void)1; // Shoot	
		//if (keyboard.KeyDown(MOUSE_RBUTTON))
		//	(void)1; // Do something

	// give resultant to player
		return moveResult;
	}
	void Logic_Input_IngamePause() // for ingame pause
	{
		// for InGame on Death, Upgrade, Levelup, EscapeKeyPress

		//if (keyboard.KeyDown(KEYB_ESCAPE)) // exit pause menu
		//	_InputStyle = INGAME;
		return;
	}

	void Update(int inputStyle)
	{
		std::cout << "SCRIPT - InputScript" << std::endl;

		_InputStyle = (Logic_Keyboard_Style)inputStyle;

		switch (_InputStyle)
		{
		case INPUT_OFF:
			return;
		case INPUT_MAIN_MENU:
			Logic_Input_MainMenu();
			return;
		case INPUT_INGAME:
			Logic_Input_Ingame();
			return;
		case INPUT_INGAME_PAUSE_ESCAPE:
			Logic_Input_IngamePause();
			return;
		default:
			return;
		}
	}
}