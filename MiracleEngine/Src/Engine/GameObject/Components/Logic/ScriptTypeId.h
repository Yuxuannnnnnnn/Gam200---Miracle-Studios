#pragma once

#define SCRIPTS(F) \
F(SCRIPT_Player),				 \
F(SCRIPT_Enemy),				 \
F(SCRIPT_Bullet),				 \
F(SCRIPT_Turret),				 \
F(SCRIPT_Spawner),				 \
F(SCRIPT_Explosion),			 \
F(SCRIPT_PickUps),				 \
F(SCRIPT_ButtonController),		 \
F(SCRIPT_HealthController),		 \
F(SCRIPT_ShieldSkill),			 \
F(SCRIPT_HitEffect),			 \
F(SCRIPT_MouseCursor),			 \
F(SCRIPT_EntrancePortal),		 \
F(SCRIPT_PauseMenu),			 \
F(SCRIPT_RegisterLink),			 \
F(SCRIPT_SplashScreen),			 \
F(SCRIPT_Boss),					 \
F(SCRIPT_LoadingScreen),		 \
F(SCRIPT_BossHealthController),\
F(SCRIPT_OptionScript)


// Create the Enums
#define F(e) e
enum class ScriptType { SCRIPTS(F), SCRIPT_COUNT};
#undef F

// Create the strings
#define F(s) std::string(#s).substr(7)
static std::string ScriptNamesArray[] = { SCRIPTS(F) };
#undef F


//std::string totitle(std::string s)
//{
//	for (char& c : s)   c = std::tolower(c);
//	for (char& c : s) { c = std::toupper(c); break; }
//	return s;
//}

inline ScriptType ToScriptId(std::string& s)
{
	return ScriptType(std::find(ScriptNamesArray, ScriptNamesArray + (int)(ScriptType::SCRIPT_COUNT), s) - ScriptNamesArray);
}

inline const char* ToScriptName(ScriptType script)
{
	return (script < ScriptType::SCRIPT_COUNT) ? ScriptNamesArray[(int)(script)].c_str() : "";
}



//enum class ScriptType {
//	SCRIPT_Player,
//	SCRIPT_Enemy,
//	SCRIPT_Bullet,
//	SCRIPT_Turret,
//	SCRIPT_Spawner,
//	SCRIPT_Explosion,
//	SCRIPT_PickUps,
//	SCRIPT_ButtonController, 
//	SCRIPT_HealthController,
//	SCRIPT_ShieldSkill,
//	SCRIPT_HitEffect,
//	SCRIPT_MouseCursor,
//	SCRIPT_EntrancePortal,
//	SCRIPT_PauseMenu,
//	SCRIPT_RegisterLink,
//	SCRIPT_SplashScreen,
//	SCRIPT_Boss,
//	SCRIPT_LoadingScreen,
//	SCRIPT_BossHealthController,
//	SCRIPT_COUNT
//};

//#define scriptTOSTRING(type) std::string(#type).substr(18)

//inline const char* ToScriptName(ScriptType type)
//{
//	switch (type)
//	{
//	case ScriptType::SCRIPT_Player:		return "Player";
//	case ScriptType::SCRIPT_Enemy:		return "Enemy";
//	case ScriptType::SCRIPT_Bullet:		return "Bullet";
//	case ScriptType::SCRIPT_Turret:		return "Turret";
//	case ScriptType::SCRIPT_Spawner:	return "Spawner";
//	case ScriptType::SCRIPT_Explosion:	return "Explosion";
//	case ScriptType::SCRIPT_PickUps:	return "PickUps";
//	case ScriptType::SCRIPT_ButtonController:	return "ButtonController";
//	case ScriptType::SCRIPT_HealthController:	return "HealthController";
//	case ScriptType::SCRIPT_ShieldSkill:	return "ShieldSkill";
//	case ScriptType::SCRIPT_HitEffect:	return "HitEffect";
//	case ScriptType::SCRIPT_MouseCursor:	return "MouseCursor";
//	case ScriptType::SCRIPT_EntrancePortal:	return "EntrancePortal";
//	case ScriptType::SCRIPT_PauseMenu:	return "PauseMenu";
//	case ScriptType::SCRIPT_RegisterLink:	return "RegisterLink";
//	case ScriptType::SCRIPT_SplashScreen:	return "SplashScreen";
//	case ScriptType::SCRIPT_Boss:		return "Boss";
//	case ScriptType::SCRIPT_LoadingScreen:		return "LoadingScreen";
//	case ScriptType::SCRIPT_BossHealthController:		return "BossHealthController";
//
//	default:      return "None";
//	}
//}

//inline ScriptType ToScriptId(std::string& name)
//{
//	if (name.compare("Player") == 0)
//		return ScriptType::SCRIPT_Player;
//	if (name.compare("Enemy") == 0)
//		return ScriptType::SCRIPT_Enemy;
//	if (name.compare("Bullet") == 0)
//		return ScriptType::SCRIPT_Bullet;
//	if (name.compare("Turret") == 0)
//		return ScriptType::SCRIPT_Turret;
//	if (name.compare("Spawner") == 0)
//		return ScriptType::SCRIPT_Spawner;
//	if (name.compare("Explosion") == 0)
//		return ScriptType::SCRIPT_Explosion;
//	if (name.compare("PickUps") == 0)
//		return ScriptType::SCRIPT_PickUps;
//	if (name.compare("ButtonController") == 0)
//		return ScriptType::SCRIPT_ButtonController;
//	if (name.compare("HealthController") == 0)
//		return ScriptType::SCRIPT_HealthController;
//	if (name.compare("ShieldSkill") == 0)
//		return ScriptType::SCRIPT_ShieldSkill;
//	if (name.compare("HitEffect") == 0)
//		return ScriptType::SCRIPT_HitEffect;
//	if (name.compare("MouseCursor") == 0)
//		return ScriptType::SCRIPT_MouseCursor;
//	if (name.compare("EntrancePortal") == 0)
//		return ScriptType::SCRIPT_EntrancePortal;
//	if (name.compare("PauseMenu") == 0)
//		return ScriptType::SCRIPT_PauseMenu;
//	if (name.compare("RegisterLink") == 0)
//		return ScriptType::SCRIPT_RegisterLink;
//	if (name.compare("SplashScreen") == 0)
//		return ScriptType::SCRIPT_SplashScreen;
//	if (name.compare("Boss") == 0)
//		return ScriptType::SCRIPT_Boss;
//	if (name.compare("LoadingScreen") == 0)
//		return ScriptType::SCRIPT_LoadingScreen;
//	if (name.compare("BossHealthController") == 0)
//		return ScriptType::SCRIPT_BossHealthController;
//	
//	return ScriptType::SCRIPT_COUNT;
//}