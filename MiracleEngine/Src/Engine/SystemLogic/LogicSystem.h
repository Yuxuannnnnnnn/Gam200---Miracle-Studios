#pragma once
#include "GameObject/Components/Logic/LogicComponent.h"
#include "GameObject/Components/Logic/IScript2.h"
#include "GameObject/Components/Logic/ScriptCreator.h"

#ifndef LOGICSYSTEM_H
#define LOGICSYSTEM_H

class LogicSystem final
{
public:
	//std::unordered_map<size_t, LogicComponent*> _ListLogicComponents;
	bool bUseOldScripting = false;

	LogicSystem() : _scriptUId(0) {}
	~LogicSystem();
	LogicSystem(const LogicSystem& rhs) = delete;
	LogicSystem& operator=(const LogicSystem& rhs) = delete;

	void Init();
	void Update(double dt);

	//void Update(double dt);

	//IScript* AddScript(LogicComponent* object, ScriptId scriptType);
	//IScript* CloneScript(LogicComponent* object, IScript* script, ScriptId scriptType);
	//void RemoveScript(LogicComponent* object, ScriptId scriptType);
	//void DeleteLevelScripts();

/////////////////////////////////////////////////////////////////////////////
// c++ scripting
private:
	size_t _scriptUId;

	std::unordered_map<size_t, IScript2*> _scriptList;
	std::unordered_map<std::string, ScriptCreator*> _scriptTypeMap;

	bool enableScript2;
public:
	void AddScriptCreator(std::string scriptName, ScriptCreator* scriptCreator);

	IScript2* CloneScript2(size_t uId);

	IScript2* CreateNewScript(const std::string& scriptName);
	std::unordered_map<size_t, IScript2*>& GetScriptList();

	std::unordered_map<std::string, ScriptCreator*>& GetScriptTypeMap();
};

#endif
