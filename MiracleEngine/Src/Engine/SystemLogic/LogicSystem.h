#pragma once
#include "GameObject/Components/Logic/LogicComponent.h"

#ifndef LOGICSYSTEM_H
#define LOGICSYSTEM_H

class LogicSystem final
{
public:
	//std::unordered_map<size_t, LogicComponent*> _ListLogicComponents;

	LogicSystem() = default;
	~LogicSystem() = default;
	LogicSystem(const LogicSystem& rhs) = delete;
	LogicSystem& operator=(const LogicSystem& rhs) = delete;

	void Init();
	void Update(double dt);

	//void Update(double dt);

	//IScript* AddScript(LogicComponent* object, ScriptId scriptType);
	//IScript* CloneScript(LogicComponent* object, IScript* script, ScriptId scriptType);
	//void RemoveScript(LogicComponent* object, ScriptId scriptType);
	//void DeleteLevelScripts();
};

#endif
