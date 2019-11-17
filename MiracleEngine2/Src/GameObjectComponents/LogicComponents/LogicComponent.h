#pragma once
#include "PrecompiledHeaders.h"
#include "GameObjectComponents/IComponentSystem.h"
#include "GameObjectComponents/LogicComponents/IScript.h"

#ifndef LOGICCOMPONENT_H
#define LOGICCOMPONENT_H

typedef std::unordered_map <unsigned, IScript*> Map_ScriptList;

class LogicComponent : public IComponentSystem
{

public:
	Map_ScriptList _scriptList;
	bool _componentEnable;
	// CompName
	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser & document) override;
	virtual void Inspect() override;

	//Constructor
	LogicComponent();
	LogicComponent(GameObject* parent, size_t uId, IComponentSystem* component = nullptr);
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

#endif
