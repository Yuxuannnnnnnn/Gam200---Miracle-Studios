#pragma once

enum class ScriptType {
	SCRIPT_Player,
	SCRIPT_Enemy,
	SCRIPT_Bullet,
	SCRIPT_Turret,
	SCRIPT_Spawner,
	SCRIPT_Explosion,
	SCRIPT_PickUps,
	SCRIPT_ButtonController, 
	SCRIPT_HealthController,
	SCRIPT_ShieldSkill,
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
	case ScriptType::SCRIPT_Spawner:	return "Spawner";
	case ScriptType::SCRIPT_Explosion:	return "Explosion";
	case ScriptType::SCRIPT_PickUps:	return "PickUps";
	case ScriptType::SCRIPT_ButtonController:	return "ButtonController";
	case ScriptType::SCRIPT_HealthController:	return "HealthController";
	case ScriptType::SCRIPT_ShieldSkill:	return "ShieldSkill";

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
	if (name.compare("Spawner") == 0)
		return ScriptType::SCRIPT_Spawner;
	if (name.compare("Explosion") == 0)
		return ScriptType::SCRIPT_Explosion;
	if (name.compare("PickUps") == 0)
		return ScriptType::SCRIPT_PickUps;
	if (name.compare("ButtonController") == 0)
		return ScriptType::SCRIPT_ButtonController;
	if (name.compare("HealthController") == 0)
		return ScriptType::SCRIPT_HealthController;
	if (name.compare("ShieldSkill") == 0)
		return ScriptType::SCRIPT_ShieldSkill;
	
	return ScriptType::SCRIPT_COUNT;
}