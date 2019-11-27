#pragma once
#include "PrecompiledHeaders.h"
#include "GameObjectComponents/IComponentSystem.h"
#include "GameObjectComponents/LogicComponents/IScript.h"

#ifndef LOGICCOMPONENT_H
#define LOGICCOMPONENT_H

//class IScript; //forward declare, for the ScriptStringToInt()

typedef std::unordered_map <unsigned, IScript*> Map_ScriptList;

class LogicComponent : public IComponentSystem
{

public:
	Map_ScriptList _scriptList;
	bool _componentEnable;

	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser & document) override;
	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;
	void Inspect() override;

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
