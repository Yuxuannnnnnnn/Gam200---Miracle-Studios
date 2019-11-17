#pragma once
#include "PrecompiledHeaders.h"

#ifndef LOGICSYSTEM_H
#define LOGICSYSTEM_H

#include <unordered_map>
#include "IScript.h"


typedef void (*scriptptr)(GameObject*);
class LogicSystem final
{
// list||map of all logic componenets
	
	typedef std::unordered_multimap<int, IScript*> ScriptMap;
	typedef std::pair<int, IScript*> ScriptPair;

	ScriptMap _ScriptList2;

	std::vector<scriptptr> _ScriptList;
public:
	LogicSystem() = default;
	~LogicSystem() = default;
	LogicSystem(const LogicSystem& rhs) = delete;
	LogicSystem& operator=(const LogicSystem& rhs) = delete;
// InUpEx
	void Init();
	void Update(const std::unordered_map < size_t, LogicComponent* >& lcmap,
		GameObjectFactory* factory, InputSystem* input);
	void Exit();
// Others
	// add GO to list
	
	// add script
	void AddScript(int ID, scriptptr script);
	// update for scripts

	//Shuyu

	void AddNewScript(IScript* script);
	std::vector<IScript*> GetGameObjectScripts(int id);

};

#endif
