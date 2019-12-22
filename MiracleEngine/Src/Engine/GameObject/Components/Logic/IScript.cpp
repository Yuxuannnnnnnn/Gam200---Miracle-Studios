#include "PrecompiledHeaders.h"
#include "IScript.h"

ScriptId IScript::ScriptStringToInt(std::string& in)	//Convert TypeIdGO Enum type to const char* - For Use only in Imgui
{
	if (in == "Unknown TypeIdGO")
		return ScriptId::EMPTY;
	else if (in == "PLAYER")
		return ScriptId::PLAYER;
	else if (in == "BULLET")
		return ScriptId::BULLET;
	else if (in == "ENEMY")
		return ScriptId::ENEMY;
	else if (in == "TURRET")
		return ScriptId::TURRET;
	else if (in == "SPAWNER")
		return ScriptId::SPAWNER;
	else if (in == "ENEMYTWO")
		return ScriptId::ENEMYTWO;
	else if (in == "ENEMYTHREE")
		return ScriptId::ENEMYTHREE;
	else if (in == "SPAWNERTWO")
		return ScriptId::SPAWNERTWO;
	else if (in == "EXPLOSION")
		return ScriptId::EXPLOSION;
	else if (in == "BUTTONUI")
		return ScriptId::BUTTON_UI;
	else if (in == "PICKUPS")
		return ScriptId::PICK_UPS;
	else if (in == "BOSS")
		return ScriptId::BOSS;
	else
		return ScriptId::EMPTY;
}
