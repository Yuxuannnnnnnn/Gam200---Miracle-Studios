#pragma once
#include "PrecompiledHeaders.h"
#include "../../IComponent.h"
#include "IScript.h"
#include "IScript2.h"

#ifndef LOGICCOMPONENT_H
#define LOGICCOMPONENT_H

//class IScript; //forward declare, for the ScriptStringToInt()

class LogicComponent : public IComponent
{
	std::vector<std::string> _ScriptIds;
	//std::unordered_map<std::string, IComponent*> _DataList; //THIS NEEDS TO CHANGE, CAUSE THIS INFO IS IN ParentGO_ComponentList
public:
	LogicComponent();
	LogicComponent(GameObject* parent, size_t uId, IComponent* component = nullptr);
	virtual ~LogicComponent() {};
	LogicComponent(const LogicComponent& rhs) = default;
	LogicComponent& operator=(const LogicComponent& rhs) = default;

	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser& document) override;
	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;
	void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator);

	void Inspect() override;
	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator) override { return; }

	void Init();
	void Update(double dt);
	void Exit();

	std::vector<std::string>& GetScriptIds();
	
	IComponent* Resolver_StringToDataComponent(std::string& dataName);
	void AddScriptDataCompResolver(std::string& scriptName); // need add some 'table' like structure to see which SCRIPT needs which DATACOMP
	void AddScript(std::string& scriptName);
	void AddDataComp(std::string& dataName);		//should only be used from within AddScript()
	
	void RemoveScriptDataCompResolver(std::string& scriptName);
	void RemoveScript(std::string& scriptName);
	void RemoveDataComp(std::string& dataName);	//should only be used from within RemoveScript()
	
	void CloneScripts(LogicComponent* parent, GameObject* src);		//AddScript() & copy data info in comps
	void ClearScripts();

	LogicComponent* CloneComponent();

	LogicComponent* CloneComponent(GameObject* parent, GameObject* src);

/////////////////////////////////////////////////////////////////////////////
// c++ scripting



private:
	std::unordered_map<ScriptType, size_t> _scriptContianer;

public:
	IScript2* AddScript2(const std::string& scriptName);
	size_t GetScript2Id(ScriptType type);

	std::unordered_map<ScriptType, size_t>& GetScriptContianer();
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
