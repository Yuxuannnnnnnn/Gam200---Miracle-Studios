#pragma once
#include "PrecompiledHeaders.h"
#include "../GameObjectComponents/LogicComponents/PrecompiledScriptType.h"

#ifndef LOGICSYSTEM_H
#define LOGICSYSTEM_H

class LogicSystem final
{
public:
	std::unordered_map < size_t, LogicComponent* >	_logicList;
	std::unordered_multimap<size_t, IScript*> _scriptList;

	LogicSystem() = default;
	~LogicSystem() = default;
	LogicSystem(const LogicSystem& rhs) = delete;
	LogicSystem& operator=(const LogicSystem& rhs) = delete;

	void Update(double dt);

	IScript* AddScript(LogicComponent* object, ScriptId scriptType);
	IScript* CloneScript(LogicComponent* object, IScript* script, ScriptId scriptType);
	void RemoveScript(LogicComponent* object, ScriptId scriptType);
	void DeleteLevelScripts();
};

#endif
