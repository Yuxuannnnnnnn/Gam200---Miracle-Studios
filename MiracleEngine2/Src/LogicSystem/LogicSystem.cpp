#include "PrecompiledHeaders.h"
#include "LogicSystem.h"

#include "Engine/EngineSystems.h"

void LogicSystem::Update(double dt)
{
	for (auto it : _logicList)
	{
		if (!it.second->GetEnable() || !it.second->_componentEnable)
			continue;

		it.second->Update(dt);
	}

}
