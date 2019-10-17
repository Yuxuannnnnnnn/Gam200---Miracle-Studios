#pragma once
#include "PrecompiledHeaders.h"
//#include "MathLib/Vector3.h"
//#include "Inputsystem/InputSystem.h" // keyboard class
//#include "GameObject.h" // player class
//#include "IComponentSystem.h"

enum Logic_Keyboard_Style {
	OFF = 0,

	MAIN_MENU,

	INGAME,
	INGAME_PAUSE_ESCAPE,
	INGAME_PAUSE_LEVELUP,
};
//enum Logic_Menu { 
//	NONE = 0,
//	MENU_EXIT,			// Show the 'Want to exit' pop up
//	MENU_PAUSE,			// Show paused Menu
//	IG_RUN,				// turn off all all pop ups
//	IG_PAUSE_LEVELUP,	// pause game and show LevelUp
//};

class LogicComponent: public IComponentSystem
{
private:
	size_t _Parent;
	//InputSystem keyboard;				// need to be able to get one from InputSystem
	Logic_Keyboard_Style _InputStyle{ OFF };	// keep track of keyboard input style
public:
	LogicComponent() {}

	std::string ComponentName() const override
	{
		return "Logic Component";
	}

	void Init()
	{
		_InputStyle = INGAME;
	}
	void Update() // supposedly all components should have an Init,Update,Exit(), so need add override
	{

	}


	/******************************************************************************/
	/**
	\brief Call this in Player to allow for input
	*/
	/******************************************************************************/
	void Logic_Input(InputSystem keyboard, Logic_Keyboard_Style style)
	{
		switch (style)
		{
		case OFF:
			return;
		case MAIN_MENU:
			Logic_Input_MainMenu(keyboard);
			return;
		case INGAME:
			Logic_Input_Ingame(keyboard);
			return;
		case INGAME_PAUSE_ESCAPE:
			Logic_Input_IngamePause(keyboard);
			return;
		default:
			return;
		}
	}

	// functions to check key UpDownHold for chosen keys
	// GetKeyDown(AE_LEFT); GetKeyUp(ESCAPE); GetKeyHold(MB_RIGHT);
	void Logic_Input_MainMenu(InputSystem keyboard) // for menu input
	{
		// for MainMenu
	}
	Vector3 Logic_Input_Ingame(InputSystem keyboard) // for in game input
	{
		Vector3 moveResult; // for throwing resultant movement force to player

	// OTHERS
		if (keyboard.KeyDown(KEYB_ESCAPE)) // open pause menu
			_InputStyle = INGAME_PAUSE_ESCAPE;
	// MOVEMENT		// in future need to do a speed multi OR leave it to phy to do it?
		if (keyboard.KeyDown(KEYB_W))
			moveResult.Y(1.0f);
		if (keyboard.KeyDown(KEYB_S))
			moveResult.Y(-1.0f);
		if (keyboard.KeyDown(KEYB_D))
			moveResult.X(1.0f);
		if (keyboard.KeyDown(KEYB_A))
			moveResult.X(-1.0f);
	// MOUSE
		if (keyboard.KeyDown(MOUSE_LBUTTON))
			(void)1; // Shoot	
		if (keyboard.KeyDown(MOUSE_RBUTTON))
			(void)1; // Do something

	// give resultant to player
		return moveResult;
	}
	void Logic_Input_IngamePause(InputSystem keyboard) // for ingame pause
	{
		// for InGame on Death, Upgrade, Levelup, EscapeKeyPress

		if (keyboard.KeyDown(KEYB_ESCAPE)) // exit pause menu
			_InputStyle = INGAME;
	}


	/******************************************************************************/
	/**
	\brief Call this for menu behaviour
	*/
	/******************************************************************************/
	void Logic_Menu()
	{
		// switch from screen to screen
		// know what is current screen (cause each screen will have different objects on screen
		// allow ESCAPE to go back 1 screen
	}


	// functions for future implementation, prob need shift to their own .h.cpp files

	void Logic_AI_Enemy1()
	{
		// add FSM
		// add other logic stuff
	}

	void Logic_EntityCollision()
	{
		// call on collision between entities

		// if player.bullet collide enemy
		//		enemy.health--;
	}
};

