#include "PrecompiledHeaders.h"
#include "LogicComponent.h"



LogicComponent::LogicComponent()
{};
LogicComponent::~LogicComponent()
{
	// delete IScript2
	for (auto& itr : _scriptContianer)
	{
		delete MyLogicSystem.GetScriptList()[itr.second];
		MyLogicSystem.GetScriptList().erase(itr.second);
	}
}
LogicComponent::LogicComponent(GameObject* parent, size_t uId, IComponent* component)
	: IComponent(parent, uId)
{
	if (component)
	{
		LogicComponent* logicComponent = dynamic_cast<LogicComponent*>(component);
		if (!_ScriptIds.empty())
		{
			for (auto itr : logicComponent->_ScriptIds)
				AddScript(itr);
			// copy data to this dataComps
				// for now just use default vals by DataComp()ctor
		}
	}
}

std::string LogicComponent::ComponentName() const
{
	return "Logic Component";
}

void LogicComponent::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("ScriptId") && document["ScriptId"].IsArray())	//Checks if the variable exists in .Json file
		for (unsigned i = 0; i < document["ScriptId"].Size(); i++)
		{
			if (document["ScriptId"][i].IsString())
			{
				std::string str = (document["ScriptId"][i].GetString());
				AddScript(str);
			}
		}

	if (document.HasMember("Script2Id") && document["Script2Id"].IsArray() &&
		document.HasMember("Script2Data") && document["Script2Data"].IsArray())	//Checks if the variable exists in .Json file
		for (unsigned i = 0; i < document["Script2Id"].Size(); i++)
		{
			if (document["Script2Id"][i].IsString())
			{
				IScript2* script = AddScript2(document["Script2Id"][i].GetString());

				Serialiser datafile(document["Script2Data"][i]);
				script->SerialiseComponent(datafile);
			}
		}
}

void LogicComponent::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
	rapidjson::Value value;

	value.SetBool(true);
	prototypeDoc.AddMember("LogicComponent", rapidjson::Value(true));

	value.SetArray();
	for (auto& scriptPair : _ScriptIds)
	{
		//value.PushBack(rapidjson::Value(scriptPair.first).Move(), prototypeDoc.Allocator());
	}

	prototypeDoc.AddMember("ScriptId", value);
}

void LogicComponent::DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
{
	rapidjson::Value value;

	value.SetBool(true);
	prototypeDoc.AddMember("LogicComponent", rapidjson::Value(true), allocator);

	value.SetArray();
	for (auto& scriptPair : _ScriptIds)
	{
		//value.PushBack(rapidjson::Value(scriptPair.first).Move(), prototypeDoc.Allocator());
	}

	prototypeDoc.AddMember("ScriptId", value, allocator);
}



void LogicComponent::Inspect()
{
	std::cout << "LogicComponent::Inspect() \n";
	std::cout << "\t Scripts :: ";
	for (auto itr : _ScriptIds)
		std::cout << itr << ", ";
	std::cout << "\n";

	std::cout << "\t DataComponents :: ";
	for (auto itr : _ScriptIds)
	{
		for (auto itr2 : _engineSystems._scriptSystem->_ScriptsAll[itr]->_DataDep)
		{
			if(GetParentPtr()->GetComponent(ToComponentID(itr2)))
				GetParentPtr()->GetComponent(ToComponentID(itr2))->Inspect();
		}
	}

	//IComponent::Inspect();
	//for (auto& scriptPair : _ScriptIds)
	//{
	//	//scriptPair.second->Inspect();
	//}
}

void LogicComponent::Init()
{

}
void LogicComponent::Update(double dt)
{
	if (!_ScriptIds.empty())
	{
		// call ScriptSys to run through script
		for (auto itr : _ScriptIds)
			_engineSystems._scriptSystem->RunScript(GetParentPtr(), itr);
	}
	return;
}
void LogicComponent::Exit()
{

}

std::vector<std::string>& LogicComponent::GetScriptIds()
{
	return _ScriptIds;
}


IComponent* LogicComponent::Resolver_StringToDataComponent(std::string& dataName)
{
	GameObject* parent = this->GetParentPtr();
	DataComponent* temp = nullptr;

	if (dataName == "DataMoveComponent")
	{
		temp = (DataComponent*)parent->AddComponent(ComponentId::CT_DataMove);
		temp->parentLogic = this;	
	}
	if (dataName == "DataTransformComponent")
	{
		temp = (DataComponent*)parent->AddComponent(ComponentId::CT_DataTransform);
		temp->parentLogic = this;
	}
	if (dataName == "DataPlayerComponent")
	{
		temp = (DataComponent*)parent->AddComponent(ComponentId::CT_DataPlayer);
		temp->parentLogic = this;
	}
	if (dataName == "DataHealthComponent")
	{
		temp = (DataComponent*)parent->AddComponent(ComponentId::CT_DataHealth);
		temp->parentLogic = this;
	}
	return temp;
}
void LogicComponent::AddScriptDataCompResolver(std::string& scriptName)
{

}
void LogicComponent::AddScript(std::string& scriptName)
{
	if (scriptName.empty())
	{
		if (DEBUG_LUA) std::cout << "WARNING: " << scriptName << " is empty. \n";
		return;
	}
	if (scriptName == "unknown")
	{
		if (DEBUG_LUA) std::cout << "WARNING: Script: " << scriptName << ", does not have any data component. \n";
		return;
	}
	if (DEBUG_LUA) std::cout << "DEBUG:\t LogicComponent::AddScript(" << scriptName << ") \n";
	for (auto itr : _ScriptIds)
		if (itr == scriptName)
		{
			if (DEBUG_LUA) std::cout << "WARNING: Script already exists. \n";
			break; 
		}
	_ScriptIds.push_back(scriptName);

	if (DEBUG_LUA) std::cout << "DEBUG:\t Script: " << scriptName << ", adding data components... \n";
	std::vector<std::string> tempStrVec = (_engineSystems._scriptSystem->_ScriptsAll[scriptName])->_DataDep;
	if (tempStrVec.empty())
	{
		if (DEBUG_LUA) std::cout << "WARNING: " << scriptName << " not a script in _TableScriptData. \n";
		return;
	}
	for (auto itr : tempStrVec)
		AddDataComp(itr);
}
void LogicComponent::AddDataComp(std::string& dataName)
{
	for (auto itr : GetParentPtr()->GetComponentList())
// change to seach in ParentGO.ComponentList
		if (itr.first == ToComponentID(dataName))
		{
			if (DEBUG_LUA) std::cout << "WARNING: DataComponent already exists. \n";
			break;
		}
// else add component
// need change to call GOFac to AddComponent(DataComponent);
	IComponent* dataComp = Resolver_StringToDataComponent(dataName); 
}

void LogicComponent::RemoveScriptDataCompResolver(std::string& scriptName)
{
	std::vector<std::string> tempStrVec;
	// list of all what each script needs as data component, before DataComponent.Register, will need this table or sth
	if (scriptName.empty())
	{
		if (DEBUG_LUA) std::cout << "WARNING: " << scriptName << " is empty. \n";
		return;
	}
	if (scriptName == "unknown")
	{
		if (DEBUG_LUA) std::cout << "WARNING: Script: " << scriptName << ", does not have any data component. \n";
		return;
	}
	if (DEBUG_LUA) std::cout << "DEBUG:\t Script: " << scriptName << ", removing data components... \n";
	tempStrVec = _engineSystems._scriptSystem->_ScriptsAll[scriptName]->_DataDep;
	if (tempStrVec.empty())
	{
		if (DEBUG_LUA) std::cout << "WARNING: " << scriptName << " not a script in _TableScriptData. \n";
		return;
	}
	for (auto itr : tempStrVec)
		RemoveDataComp(std::string(itr));
}
void LogicComponent::RemoveScript(std::string& scriptName)
{
	// remove scriptName
	std::vector<std::string>::iterator iterator = _ScriptIds.begin();
	for (auto itr : _ScriptIds)
	{
		++iterator;
		if (itr == scriptName)
			break;
	}
	_ScriptIds.erase(iterator);
	RemoveScriptDataCompResolver(scriptName);
}
void LogicComponent::RemoveDataComp(std::string& dataName)
{
	// check if DataComps linked with scriptName has no more dependency
	for (auto scriptName : _ScriptIds)
	{
		// go through itr's DataComps
		for (auto existingData : _engineSystems._scriptSystem->_ScriptsAll[scriptName]->_DataDep)
			if (existingData == dataName)
			{
				if (DEBUG_LUA) std::cout << "WARNING: DataComponent\"" << dataName << "\" still has dependancy! Cannot remove! \n";
				return;
			}
	}
	// else remove datacomp, supposed to use Factory's RemoveComponent()
	GetParentPtr()->RemoveComponent(ToComponentID(dataName));
	//	delete _DataList[dataName];
	//	_DataList.erase(_DataList.find(dataName));
}

LogicComponent* LogicComponent::CloneComponent()
{
	return nullptr;
//	LogicComponent* temp = new LogicComponent();
//	temp->_ScriptIds = _ScriptIds;
//	return temp;
}

void LogicComponent::CloneScripts(LogicComponent* parent, GameObject* src)
{
	_ScriptIds = ((LogicComponent*)src->GetComponent(ComponentId::CT_Logic))->_ScriptIds;
	for (auto nameScript : _ScriptIds)
	{
		if (nameScript.empty())
		{
			if (DEBUG_LUA) std::cout << "WARNING: " << nameScript << " is empty. \n";
			return;
		}
		if (nameScript == "unknown")
		{
			if (DEBUG_LUA) std::cout << "WARNING: Script: " << nameScript << ", does not have any data component. \n";
			return;
		}
		if (DEBUG_LUA) std::cout << "DEBUG:\t LogicComponent::CloneScript(" << nameScript << ") \n";
		for (auto nameComponent : _engineSystems._scriptSystem->_ScriptsAll[nameScript]->_DataDep)
		{
			// check if dataComp alr exist
			for (auto nameExistingComponent : GetParentPtr()->GetComponentList())
				if (nameExistingComponent.first == ToComponentID(nameComponent))
				{
					if (DEBUG_LUA) std::cout << "WARNING: DataComponent already exists. \n";
					break;
				}
			// clone from src
			src->GetComponent(ToComponentID(nameComponent))->CloneComponent();
		}
	}
}
void LogicComponent::ClearScripts()
{
	if (_ScriptIds.empty())
		return;
	_ScriptIds.clear();
}

/////////////////////////////////////////////////////////////////////////////
// c++ scripting

LogicComponent* LogicComponent::CloneComponent(GameObject* parent, GameObject* src)
{
	LogicComponent* temp = new LogicComponent();
	temp->SetParentPtr(parent);
	temp->SetParentId(parent->Get_uID());
	temp->CloneScripts((LogicComponent*)parent->GetComponent(ComponentId::CT_Logic), src);
	//temp->_ScriptIds = _ScriptIds;
//	for (auto& itr : _ScriptIds)
//		temp->AddScript(itr);

	// c++ scripting
	for (auto& itr : _scriptContianer)
	{
		IScript2* newScript = MyLogicSystem.CloneScript2(itr.second);
		newScript->SetParentPtr(parent);
		newScript->SetParentId(parent->Get_uID());

		temp->_scriptContianer[itr.first] = newScript->_uId;
	}

	return temp;
}

IScript2* LogicComponent::AddScript2(const std::string& scriptName)
{
	IScript2* script = MyLogicSystem.CreateNewScript(scriptName);
	script->SetParentPtr(this->GetParentPtr());
	script->SetParentId(this->GetParentId());

	_scriptContianer[script->_type] = script->_uId;

	return script;
}

size_t LogicComponent::GetScript2Id(ScriptType type)
{
	if (_scriptContianer.find(type) != _scriptContianer.end())
		return _scriptContianer[type];

	return 0;
}

std::unordered_map<ScriptType, size_t>& LogicComponent::GetScriptContianer()
{
	return _scriptContianer;
}

//bool LogicComponent::CheckScript(ScriptId scriptType)
//{
//	Map_ScriptIds::iterator it = _ScriptIds.find((unsigned)scriptType);
//
//	if (it == _ScriptIds.end() || !it->second)
//		return false;
//
//	return true;
//}
//
//IScript* LogicComponent::AddScript(ScriptId scriptType)
//{
//	if (CheckScript(scriptType))
//		return GetScript(scriptType);
//
//	IScript* newScript = EngineSystems::GetInstance()._logicSystem->AddScript(this, scriptType);
//	_ScriptIds.insert(std::pair<unsigned, IScript*>((unsigned)scriptType, newScript));
//
//	return new IScript();
//}
//
//void LogicComponent::RemoveScript(ScriptId scriptType)
//{
//	if (!CheckScript(scriptType))
//		return;
//
//	EngineSystems::GetInstance()._logicSystem->RemoveScript(this, scriptType);
//	_ScriptIds.erase((unsigned)scriptType);
//}
//
//IScript* LogicComponent::GetScript(ScriptId scriptType)
//{
//	return _ScriptIds[(unsigned)scriptType];
//}