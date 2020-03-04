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

	LogicSystem();
	~LogicSystem();
	LogicSystem(const LogicSystem& rhs) = delete;
	LogicSystem& operator=(const LogicSystem& rhs) = delete;

	void Init();
	void Update(double dt);

	void LoadResource();

	void RegisterAllScript();

	//void Update(double dt);

	//IScript* AddScript(LogicComponent* object, ScriptId scriptType);
	//IScript* CloneScript(LogicComponent* object, IScript* script, ScriptId scriptType);
	//void RemoveScript(LogicComponent* object, ScriptId scriptType);
	//void DeleteLevelScripts();

/////////////////////////////////////////////////////////////////////////////
// c++ scripting
private:
	size_t _scriptUId;

	std::unordered_map<size_t, IScript2*> _scriptList; // _scriptContianer[script->_type] = script->_uId;
	std::unordered_map<std::string, ScriptCreator*> _scriptTypeMap;

	bool enableScript2;
	bool _resgister;
public:
	void AddScriptCreator(std::string scriptName, ScriptCreator* scriptCreator);

	IScript2* CloneScript2(size_t uId);

	IScript2* CreateNewScript(const std::string& scriptName);
	std::unordered_map<size_t, IScript2*>& GetScriptList();

	std::unordered_map<std::string, ScriptCreator*>& GetScriptTypeMap();

	std::vector<IScript2*> GetScriptList(size_t objUId);

	IScript2* getScriptPtr(size_t uID);

};

#endif
