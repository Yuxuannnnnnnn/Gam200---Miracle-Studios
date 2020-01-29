#pragma once

enum class ScriptType {
	SCRIPT_Player,
	SCRIPT_Enemy,
	SCRIPT_Bullet,
	SCRIPT_Turret,
	SCRIPT_COUNT
};

inline const char* ToScriptName(ScriptType type)
{
	switch (type)
	{
	case ScriptType::SCRIPT_Player:		return "Player";
	case ScriptType::SCRIPT_Enemy:		return "Enemy";
	case ScriptType::SCRIPT_Bullet:		return "Bullet";
	case ScriptType::SCRIPT_Turret:		return "Turret";

	default:      return "None";
	}
}

inline ScriptType ToScriptId(std::string& name)
{
	if (name.compare("Player") == 0)
		return ScriptType::SCRIPT_Player;
	if (name.compare("Enemy") == 0)
		return ScriptType::SCRIPT_Enemy;
	if (name.compare("Bullet") == 0)
		return ScriptType::SCRIPT_Bullet;
	if (name.compare("Turret") == 0)
		return ScriptType::SCRIPT_Turret;
	
	return ScriptType::SCRIPT_COUNT;
}