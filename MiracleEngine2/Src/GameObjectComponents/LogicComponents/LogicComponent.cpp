#include "PrecompiledHeaders.h"
#include "LogicComponent.h"
#include "Engine/EngineSystems.h"

void LogicComponent::Update(double dt)
{
	for (auto it : _scriptList)
	{
		it.second->Update(dt);
	}
}

Map_ScriptList& LogicComponent::GetScriptMap()
{
	return _scriptList;
}

bool LogicComponent::CheckScript(ScriptId scriptType)
{
	Map_ScriptList::iterator it = _scriptList.find((unsigned)scriptType);

	if (it == _scriptList.end() || !it->second)
		return false;

	return true;
}

IScript* LogicComponent::AddScript(ScriptId scriptType)
{
	if (CheckScript(scriptType))
		return GetScript(scriptType);

	IScript* newScript = EngineSystems::GetInstance()._gameObjectFactory->AddScript(this, scriptType);
	_scriptList.insert(std::pair<unsigned, IScript*>((unsigned)scriptType, newScript));

	return newScript;
}

void LogicComponent::RemoveScript(ScriptId scriptType)
{
	if (!CheckScript(scriptType))
		return;

	EngineSystems::GetInstance()._gameObjectFactory->RemoveScript(this, scriptType);
	_scriptList.erase((unsigned)scriptType);
}

IScript* LogicComponent::GetScript(ScriptId scriptType)
{
	return _scriptList[(unsigned)scriptType];
}