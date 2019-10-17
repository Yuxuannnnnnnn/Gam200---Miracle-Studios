#pragma once
#include "PrecompiledHeaders.h"

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
	void Init()
	{
		// attach all scripts to objects
		
		// load all GOs with logic component into private:list
	}
	void Update(const std::map < size_t, LogicComponent* >& lcmap)
	{
		// run through 'list' and update the logic
			// update scripts
				// access std::vector<script> from GO
				// itr through and run all scripts
			// update AI

		GameObject* tmp = nullptr;
		for (auto const& x : lcmap)
		{
			//tmp = x.second->GetOwner();
			//_scriptList[x.second->GetID()](tmp);
		}
	}
	void Exit()
	{
		// unload list ?
	}
// Others
	// add GO to list
	
	// add script
	void AddScript(int ID, scriptptr script)
	{
		_ScriptList.push_back(script);
	}
	// update for scripts

};