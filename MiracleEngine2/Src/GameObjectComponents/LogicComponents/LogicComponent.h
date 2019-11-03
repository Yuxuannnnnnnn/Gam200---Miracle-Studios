#pragma once
#include "PrecompiledHeaders.h"
#include "GameObjectComponents/IComponentSystem.h"
#include "GameObjectComponents/LogicComponents/IScript.h"

typedef std::unordered_map <unsigned, IScript*> Map_ScriptList;

class LogicComponent : public IComponentSystem
{
	Map_ScriptList _scriptList;
public:
	bool _componentEnable;

	LogicComponent() : _componentEnable{ true } {};
	virtual ~LogicComponent() {};
	LogicComponent(const LogicComponent& rhs) = default;
	LogicComponent& operator=(const LogicComponent& rhs) = default;

	void Update(double dt);

	Map_ScriptList& GetScriptMap();

	bool CheckScript(ScriptId scriptType);

	IScript* AddScript(ScriptId scriptType);

	void RemoveScript(ScriptId scriptType);

	IScript* GetScript(ScriptId scriptType);
};
