#pragma once

/*
	This file should work together with functiosn that control
	- UI / Menu showing and interaction
	- Pausing of application
*/

enum class GameStateId		//GameStates follow TDD
{
	GS_TEST = 0,	

	GS_DIGI_LOGO,		// Intro - Digipen Logo first, Cannot allow to skip
	GS_GAME_LOGO,		// Press any button, must allow to skip straight to Main Menu

	GS_MAIN_MENU,		// Main Menu- From Splash Screen & Pause(Comfirmation Box)

	GS_IN_GAME,			// In Game - From Map Selection -->Many Waves in a game, need to keep track of waves
	GS_RESTART,			// Restart - From Pause(Comfirmation Box)
	GS_GAME_OVER,		// Game_Over - From_In_Game
	GS_QUIT,			// Quit - From Main Menu(Comfirmation Box) & Game Pause(Comfirmation Box)(Must free&Unload the previous In-Game state first)
	GS_PAUSE,			// Pause - From In_Game(Dont unload and free the In-Game State)
	GS_RESUME,			// Resume - From Pause(Go back to updating the In-Game state, no need init)

//Must have Back button - go back previous state
	GS_HOW_TO_PLAY,		// How To Play - From Main Menu & Game Pause
	GS_CREDITS,			// Credits - From Main Menu & Game Pause
	GS_OPTIONS,			// Options - From Main Menu & Game Pause
	GS_LEADERBOARD,		// LeaderBoard - From Main Menu -->Show Highscores, need to keep scores in a file
	GS_MAP_SELECTION	// Map Selection - From Main Menu -->Show different Maps to play on


	//GS_IG_RUNNING,			// In Game
	//GS_IG_PAUSED_ESCAPE,		//
	//GS_IG_PAUSE_LEVELUP,		//
	//GS_IG_PAUSE_STORY,		//
	//GS_IG_STOPPING_DEATH,		//
	//GS_IG_STOPPING_LEVELEND,  //



	//GS_LEVELCHANGE			//Level Changing - will stay in this state until load complete
};

class GameStateManager {

private:
	GameStateId _currState;
	GameStateId _prevState;
	GameStateId _nextState;


public:
	GameStateManager(GameStateId currState = GameStateId::GS_MAIN_MENU,
		GameStateId prevState = GameStateId::GS_MAIN_MENU,
		GameStateId nextState = GameStateId::GS_MAIN_MENU);

	~GameStateManager() = default;

//UpEx
	void Update();
	void Exit();

// Getter
	GameStateId GetCurrState() const;
	GameStateId GetNextState() const;
	GameStateId GetPrevState() const;

	void SetNextGameState(GameStateId state);

	bool CheckIfCurrStateQuit() const;
	bool CheckIfCurrNextStateSame() const;
	
// UpdateState
	void UpdateState();
};