#pragma once
#include "PrecompiledHeaders.h"
#include "Interfaces/IComponent.h"
#include "Interfaces/IScript.h"

#ifndef LOGICCOMPONENT_H
#define LOGICCOMPONENT_H

//class IScript; //forward declare, for the ScriptStringToInt()
class DataComponent;

using Map_ScriptList = std::unordered_map <unsigned, IScript*>;
using Map_DataList = std::unordered_map <std::string, DataComponent*>;

class LogicComponent : public IComponent
{

public:
	Map_ScriptList _scriptList;
	bool _componentEnable;

	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser & document) override;
	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;
	void Inspect() override;

	LogicComponent();
	LogicComponent(GameObject* parent, size_t uId, IComponent* component = nullptr);
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
