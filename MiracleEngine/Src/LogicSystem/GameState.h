#pragma once

/*
	This file should work together with functiosn that control
	- UI / Menu showing and interaction
	- Pausing of application
*/

enum GameStateId {
	GS_TEST = 0,
// Intro
	GS_SPLASH,
	GS_DIGI_LOGO,
// Main Menu
	GS_MENU_MAIN,
	GS_MENU_OPTIONS,
	GS_MENU_STATS,
	GS_MENU_QUIT,
// In Game
	GS_IG_RUNNING,
	GS_IG_PAUSED_ESCAPE,
	GS_IG_PAUSE_LEVELUP,
	GS_IG_PAUSE_STORY,
	GS_IG_STOPPING_DEATH,
	GS_IG_STOPPING_LEVELEND,
// Level Changing
	GS_LEVELCHANGE, // will stay in this state until load complete
};

class GameState {
	GameStateId _currState{ GS_TEST };
	GameStateId _prevState{ GS_TEST };
	GameStateId _nextState{ GS_TEST };
public:
	GameState() = default;
	~GameState() {}
// InUpEx
	void Init()
	{
		_currState = _prevState = _nextState = GS_TEST;
	}
	void Update()
	{
		UpdateState();
	}
	void Exit() {}
// Get
	GameStateId GetCurrState()
	{
		return _currState;
	}
// Other - UpdateState
	void UpdateState()
	{
		if (_currState == _nextState)
		{
			switch (_currState)
			{
		// INTRO
			case GS_SPLASH:
				return;
			case GS_DIGI_LOGO:
				return;
		// MAIN MENU
			case GS_MENU_MAIN:
			// set Logic_Keyboard_Style control to MAIN_MENU
				return;
			case GS_MENU_OPTIONS:
				return;
			case GS_MENU_STATS:
				return;
			case GS_MENU_QUIT:
				return;
		// IN GAME
			case GS_IG_RUNNING:
			// set Logic_Keyboard_Style control to INGAME
				return;
			case GS_IG_PAUSED_ESCAPE:
			// set Logic_Keyboard_Style control to INGAME_PAUSE
				return;
			case GS_IG_PAUSE_LEVELUP:
				return;
			case GS_IG_PAUSE_STORY:
				return;
			case GS_IG_STOPPING_DEATH:
				return;
			case GS_IG_STOPPING_LEVELEND:
				return;
		// LEVEL CHANGE
			case GS_LEVELCHANGE:
				return;

			default:
				return;
			}
		}
		else
		{
			_currState = _nextState;
		}
	}
};