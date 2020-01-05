#include "PrecompiledHeaders.h"
#include "LogicComponent.h"



LogicComponent::LogicComponent()
{};

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
				_ScriptIds.push_back(str);
				AddScript(str);
			}
		}
}

void LogicComponent::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
	rapidjson::Value value;

	value.SetArray();
	for (auto& scriptPair : _ScriptIds)
	{
		//value.PushBack(rapidjson::Value(scriptPair.first).Move(), prototypeDoc.Allocator());
	}

	prototypeDoc.AddMember("ScriptId", value);
}



void LogicComponent::Inspect()
{
	std::cout << "LogicComponent::Inspect() \n";
	std::cout << "\t Scripts :: ";
	for (auto itr : _ScriptIds)
		std::cout << itr << ", ";
	std::cout << "\n";

	std::cout << "\t DataComponents :: ";
	for (auto itr : _DataList)
	{
		std::cout << itr.first;
		itr.second->Inspect();
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
std::unordered_map<std::string, DataComponent*>& LogicComponent::GetDataList()
{
	return _DataList;
}

void LogicComponent::AddScriptDataCompResolver(std::string& scriptName)
{
	std::vector<std::string> tempStrVec;
// list of all what each script needs as data component, before DataComponent.Register, will need this table or sth
	if (scriptName.empty())
	{
		std::cout << "WARNING: " << scriptName << " is empty. \n";
		return;
	}
	if (scriptName == "unknown")
	{
		std::cout << "Script: " << scriptName << ", does not have any data component. \n";
		return;
	}
	std::cout << "Script: " << scriptName << ", adding data components... \n";
	tempStrVec = EngineSystems::GetInstance()._scriptSystem->_TableScriptData[scriptName];
	if (tempStrVec.empty())
	{
		std::cout << "WARNING: " << scriptName << " not a script in _TableScriptData. \n";
		return;
	}
	for (auto itr : tempStrVec)
		AddDataComp(std::string(itr));
}
DataComponent* LogicComponent::Resolver_StringToDataComponent(std::string& dataName)
{
	if (dataName == "health")
	{
		return new DataHealth();
	}
	if (dataName == "health2")
	{
		return new DataHealth();
	}
	if (dataName == "ammo")
	{
		return new DataAmmo();
	}
	std::cout << "WARNING: LogicComponent::Resolver_StringToDataComponent(dataName) had no proper 'dataName' \n";
	return new DataComponent();
}

void LogicComponent::AddScript(std::string& scriptName)
{
	std::cout << "LogicComponent::AddScript(" << scriptName << ") \n";
	for (auto itr : _ScriptIds)
		if (itr == scriptName)
		{
			std::cout << "WARNING: Script already exists. \n";
			break; 
		}
	std::cout << "Adding script. \n";
	AddScriptDataCompResolver(scriptName);
}
void LogicComponent::AddDataComp(std::string& dataName)
{
	for (auto itr : _DataList)
// change to seach in ParentGO.ComponentList
		if (itr.first == dataName)
		{
			std::cout << "WARNING: DataComponent already exists. \n";
			break;
		}
// else add component
// need change to call GOFac to AddComponent(DataComponent);
	DataComponent* dataComp = Resolver_StringToDataComponent(dataName);
	_DataList[dataName] = dataComp;
}
void LogicComponent::RemoveScriptDataCompResolver(std::string& scriptName)
{
	std::vector<std::string> tempStrVec;
	// list of all what each script needs as data component, before DataComponent.Register, will need this table or sth
	if (scriptName.empty())
	{
		std::cout << "WARNING: " << scriptName << " is empty. \n";
		return;
	}
	if (scriptName == "unknown")
	{
		std::cout << "Script: " << scriptName << ", does not have any data component. \n";
		return;
	}
	std::cout << "Script: " << scriptName << ", adding data components... \n";
	tempStrVec = EngineSystems::GetInstance()._scriptSystem->_TableScriptData[scriptName];
	if (tempStrVec.empty())
	{
		std::cout << "WARNING: " << scriptName << " not a script in _TableScriptData. \n";
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
	// call RemoveDataComp(std::string& dataName)

}
void LogicComponent::RemoveDataComp(std::string& dataName)
{
	// check if DataComps linked with scriptName has no more dependency
	// remove DataComps with no dependency
}
void LogicComponent::CloneScriptsAndDatas(LogicComponent* source)
{
	for (auto itr : source->_ScriptIds)
		AddScript(itr);
}
//void LogicComponent::CloneDataComp(){}
void LogicComponent::ClearScripts()
{
	if (_ScriptIds.empty())
		return;
	else
		for (auto itr : _ScriptIds)
			RemoveScript(itr);
}
void LogicComponent::ClearDataComps()
{
	std::cout << "this should not be accessable \n";
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