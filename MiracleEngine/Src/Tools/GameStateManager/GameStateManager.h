#pragma once

/*
	This file should work together with functiosn that control
	- UI / Menu showing and interaction
	- Pausing of application
*/

enum Game_States {
	TEST = 0,
// Intro
	SPLASH,
	DIGI_LOGO,
// Main Menu
	MENU_MAIN,
	MENU_OPTIONS,
	MENU_STATS,
	MENU_QUIT,
// In Game
	IG_RUNNING,
	IG_PAUSED_ESCAPE,
	IG_PAUSE_LEVELUP,
	IG_PAUSE_STORY,
	IG_STOPPING_DEATH,
	IG_STOPPING_LEVELEND,
};

class GameStateManager {

	unsigned _currState{ TEST };
public:
	GameStateManager() = default;
	~GameStateManager() {}

	void Init() {}
	void Update()
	{
		UpdateState();
	}
	void Exit() {}
	
	void UpdateState()
	{
		switch (_currState)
		{
// INTRO
		case SPLASH:
			return;
		case DIGI_LOGO:
			return;
// MAIN MENU
		case MENU_MAIN:
			// set Logic_Keyboard_Style control to MAIN_MENU
			return;
		case MENU_OPTIONS:
			return;
		case MENU_STATS:
			return;
		case MENU_QUIT:
			return;
// IN GAME
		case IG_RUNNING:
			// set Logic_Keyboard_Style control to INGAME
			return;
		case IG_PAUSED_ESCAPE:
			// set Logic_Keyboard_Style control to INGAME_PAUSE
			return;
		case IG_PAUSE_LEVELUP:
			return;
		case IG_PAUSE_STORY:
			return;
		case IG_STOPPING_DEATH:
			return;
		case IG_STOPPING_LEVELEND:
			return;

		default:
			return;
		}
	}
};