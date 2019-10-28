#include "PrecompiledHeaders.h"
#include "GameStateManager.h"




GameStateManager::GameStateManager(GameStateId currState, 
		GameStateId prevState, GameStateId nextState)
	: _currState{ currState }, _prevState{ prevState }, _nextState{ nextState }
{

}


void GameStateManager::Update()
{
}

GameStateId GameStateManager::GetCurrState() const
{
	return _currState;
}

GameStateId GameStateManager::GetNextState() const
{
	return _nextState;
}



void GameStateManager::UpdateState()
{
	if (_currState == _nextState)
	{
		switch (_currState)
		{
		case GameStateId::GS_DIGI_LOGO:			return;
		case GameStateId::GS_GAME_LOGO:			return;
		case GameStateId::GS_MAIN_MENU:			return;// set Logic_Keyboard_Style control to MAIN_MENU
		case GameStateId::GS_IN_GAME:			return;
		case GameStateId::GS_RESTART:			return;
		case GameStateId::GS_GAME_OVER:			return;
		case GameStateId::GS_QUIT:				return;// set Logic_Keyboard_Style control to INGAME
		case GameStateId::GS_PAUSE:				return;// set Logic_Keyboard_Style control to INGAME_PAUSE
		case GameStateId::GS_RESUME:			return;
		case GameStateId::GS_HOW_TO_PLAY:		return;
		case GameStateId::GS_CREDITS:			return;
		case GameStateId::GS_OPTIONS:			return;
		case GameStateId::GS_LEADERBOARD:		 return;
		case GameStateId::GS_MAP_SELECTION:		 return;

		default:	return;
		}
	}
	else
	{
		_currState = _nextState;
	}
}