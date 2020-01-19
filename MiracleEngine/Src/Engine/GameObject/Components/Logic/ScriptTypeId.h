#pragma once

enum class ScriptType {
	SCRIPT_Player,
	SCRIPT_COUNT
};

inline const char* ToScriptName(ScriptType type)
{
	switch (type)
	{
	case ScriptType::SCRIPT_Player:		return "Player";

	default:      return "None";
	}
}

inline ScriptType ToScriptId(std::string& name)
{
	if (name.compare("Player") == 0)
		return ScriptType::SCRIPT_Player;
	return ScriptType::SCRIPT_COUNT;
}