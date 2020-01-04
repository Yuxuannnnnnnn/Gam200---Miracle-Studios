#pragma once
#include "PrecompiledHeaders.h"
#include "../../IComponent.h"
#include "IScript.h"

#ifndef LOGICCOMPONENT_H
#define LOGICCOMPONENT_H

//class IScript; //forward declare, for the ScriptStringToInt()
class DataComponent;


class LogicComponent : public IComponent
{
	std::vector<std::string> _ScriptIds;
	std::unordered_map<std::string, DataComponent*> _DataList; //THIS NEEDS TO CHANGE, CAUSE THIS INFO IS IN ParentGO_ComponentList
public:
	LogicComponent();
	LogicComponent(GameObject* parent, size_t uId, IComponent* component = nullptr);
	virtual ~LogicComponent() {};
	LogicComponent(const LogicComponent& rhs) = default;
	LogicComponent& operator=(const LogicComponent& rhs) = default;

	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser& document) override;
	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;
	void Inspect() override;
	void DeserialiseComponentSceneFile(IComponent* protoCom, DeSerialiser& SceneFile) { return; }

	void Init();
	void Update(double dt);
	void Exit();

	std::vector<std::string>& GetScriptIds();
	std::unordered_map<std::string, DataComponent*>& GetDataList();

	void Resolver_AddDataComp(std::string& scriptName); // need add some 'table' like structure to see which SCRIPT needs which DATACOMP
	DataComponent* Resolver_StringToDataComponent(std::string& dataName);
	void AddScript(std::string& scriptName);
	void AddDataComp(std::string& dataName);		//should only be used from within AddScript()
	void RemoveScript(std::string& scriptName);
	void RemoveDataComp(std::string& dataName);	//should only be used from within RemoveScript()
	void CloneScriptsAndDatas(LogicComponent* source);		//AddScript() & copy data info in comps
	//void CloneDataComp();
	void ClearScripts();
	void ClearDataComps();
};

//public:
//	Map_ScriptList _scriptList;
//	bool _componentEnable;
//
//	std::string ComponentName() const override;
//	void SerialiseComponent(Serialiser & document) override;
//	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;
//	void Inspect() override;
//
//	LogicComponent();
//	LogicComponent(GameObject* parent, size_t uId, IComponent* component = nullptr);
//	virtual ~LogicComponent() {};
//	LogicComponent(const LogicComponent& rhs) = default;
//	LogicComponent& operator=(const LogicComponent& rhs) = default;
//
//	void Update(double dt);
//
//	Map_ScriptList& GetScriptMap();
//
//	bool CheckScript(ScriptId scriptType);
//
//	IScript* AddScript(ScriptId scriptType);
//
//	void RemoveScript(ScriptId scriptType);
//
//	IScript* GetScript(ScriptId scriptType);

#endif
