#pragma once
#include "PrecompiledHeaders.h"

#ifndef LOGICSYSTEM_H
#define LOGICSYSTEM_H



typedef void (*scriptptr)(GameObject*);
class LogicSystem final
{
// list||map of all logic componenets
	std::vector<GameObject*> _GOList;
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

};

#endif
