#pragma once
#include "PrecompiledHeaders.h"

class LogicSystem final
{
// list||map of all logic componenets
	std::vector <IGameObject*> list;
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
	void Update()
	{
		// run through 'list' and update the logic
			// update scripts
				// access std::vector<script> from GO
				// itr through and run all scripts
			// update AI
	}
	void Exit()
	{
		// unload list ?
	}
// Others
	// add GO to list
	
	// add script

	// update for scripts
};