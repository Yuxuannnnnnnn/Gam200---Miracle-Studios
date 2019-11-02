#include "PrecompiledHeaders.h"
#include "LogicSystem.h"

#include "Engine/EngineSystems.h"

void LogicSystem::Update(double dt)
{
	for (auto it : _logicList)
		it.second->Update(dt);

}
