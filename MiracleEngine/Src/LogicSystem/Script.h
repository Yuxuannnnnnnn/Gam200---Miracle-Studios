#pragma once
#include "PrecompiledHeaders.h"
#include "GameObjectComponents/IComponentSystem.h" // need to be able to access other components

#ifndef SCRIPT_H
#define	SCRIPT_H


class LogicComponent; // forward declare, need to know LogicComp
class GameObjectFactory; // forward declare, need clone bullet
class InputSystem; // forward declare, need to handle input

namespace Script_1 {
	void Update();
}

namespace Script_2 {
	void Update(LogicComponent* parent);
}

namespace Script_HealthMinus {
	void Update(int& health, int changeVal);
}

namespace Script_Input {
	enum class Input_Style {
		OFF = 0,

		MAIN_MENU,

		INGAME,
		INGAME_PAUSE_ESCAPE,
		INGAME_PAUSE_LEVELUP,
	};

	//Logic_Keyboard_Style _InputStyle{ INPUT_OFF };

	void Logic_Input_MainMenu();
	void Logic_Input_Ingame(
		GameObjectFactory* factory, GameObject* player,
		InputSystem* input, Input_Style inputStyle);
	void Logic_Input_IngamePause();

	void Update(
		GameObjectFactory* factory, GameObject* player, InputSystem* input);
}

namespace Script_Shoot {
	void Update(GameObject* obj, GameObjectFactory* factory);
}

#endif
