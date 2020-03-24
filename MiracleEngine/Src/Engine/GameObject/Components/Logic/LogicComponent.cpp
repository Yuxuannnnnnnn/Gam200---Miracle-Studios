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
	//if (document.HasMember("ScriptId") && document["ScriptId"].IsArray())	//Checks if the variable exists in .Json file
	//	for (unsigned i = 0; i < document["ScriptId"].Size(); i++)
	//	{
	//		if (document["ScriptId"][i].IsString())
	//		{
	//			std::string str = (document["ScriptId"][i].GetString());
	//			AddScript(str);
	//		}
	//	}

	if (document.HasMember("LogicComponent") && document["LogicComponent"].IsBool())
		SetEnable(document["LogicComponent"].GetBool());


	//for (auto& script: _scriptContianer)
	//{
	//	delete MyLogicSystem.getScriptPtr(script.second);
	//	MyLogicSystem.GetScriptList().erase(script.second);
	//}
	// _scriptContianer.clear();
	// _ScriptIds.clear();


	if (document.HasMember("Scripts") && document["Scripts"].IsArray())
		for (unsigned i = 0; i < document["Scripts"].Size(); i++)
		{
			Serialiser datafile(document["Scripts"][i]);
			if (datafile.HasMember("Script2Id"))
			{
				std::string name = datafile["Script2Id"].GetString();

				//not feasible if there are duplicate scripts in one object
				//Temporary solution for scripts
				if (_scriptContianer.find(ToScriptId(name)) != _scriptContianer.end()) //If LogicComponent already has the script
				{
					
					size_t scriptID = _scriptContianer[ToScriptId(name)]; 
					_scriptContianer.erase(ToScriptId(name));	//remove script from scriptContainer
					delete MyLogicSystem.getScriptPtr(scriptID); //delete script ptr from logicSystem
					MyLogicSystem.GetScriptList().erase(scriptID); //remove script pair from logicSystem
				}


				IScript2* script = AddScript2(datafile["Script2Id"].GetString()); //Add Script to the GameOject

				script->SerialiseComponent(datafile); //Serialise data to script , Iscript will serialise the type
			}
		}
}

//For Prototypes
void LogicComponent::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
	rapidjson::Value value;

	value.SetBool(GetEnable());
	prototypeDoc.AddMember("LogicComponent", value);


	value.SetArray();
	for (auto& script : _scriptContianer) //For every Script in this Object
	{
		rapidjson::Value Object;
		Object.SetObject();

		IScript2* script2ptrs = MyLogicSystem.getScriptPtr(script.second);
		script2ptrs->DeSerialiseComponent(Object, prototypeDoc.GetAllocator()); //Sent in an array and an allocator
																		//Add Each Scriptdata as an object in the array
																				//Scripts do not need to have the original Deserialise function
		value.PushBack(Object, prototypeDoc.GetAllocator());
	}
	prototypeDoc.AddMember("Scripts", value);
}

//For nonclonables
void LogicComponent::DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator)
{
	rapidjson::Value value;

	value.SetBool(GetEnable());
	prototypeDoc.AddMember("LogicComponent", value, allocator);


	value.SetArray();
	for (auto& script : _scriptContianer) //For every Script in this Object
	{
		rapidjson::Value Object;
		Object.SetObject();

		IScript2* script2ptrs = MyLogicSystem.getScriptPtr(script.second);
		script2ptrs->DeSerialiseComponent(Object, allocator); //Sent in an array and an allocator
																		//Add Each Scriptdata as an object in the array
																				//Scripts do not need to have the original Deserialise function
		value.PushBack(Object, allocator);
	}																		


	prototypeDoc.AddMember("Scripts", value, allocator);
}

//For clonables
void LogicComponent::DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator)
{
	LogicComponent* protoLogicCom = dynamic_cast<LogicComponent*>(protoCom);

	if (!protoLogicCom) //If there is no such component in the prototype Object
	{
		DeSerialiseComponent(value, allocator);
		return;
	}

	rapidjson::Value enable;

	bool addComponentIntoSceneFile = false;

	if (protoLogicCom->GetEnable() != this->GetEnable())
	{
		addComponentIntoSceneFile = true;
		enable.SetBool(GetEnable());
	}

	//if (addComponentIntoSceneFile)
	//{
		if (!enable.IsNull())
			value.AddMember("LogicComponent", enable, allocator);
		else
			value.AddMember("LogicComponent", protoLogicCom->GetEnable(), allocator);


		rapidjson::Value Array;
		Array.SetArray();

		for (auto script : _scriptContianer)
		{
			rapidjson::Value Object;
			Object.SetObject();

			IScript2* script2ptrs = MyLogicSystem.getScriptPtr(script.second);

			script2ptrs->DeserialiseComponentSceneFile(protoCom, Object, allocator); //Compare data for each script between prototype and this object
			//script2ptrs->DeSerialiseComponent(Object, allocator);

			if(!Object.IsNull()) //If the script is deserialised or differs from the prototype script
				Array.PushBack(Object, allocator);
		}

		value.AddMember("Scripts", Array, allocator);


	//}
}

void LogicComponent::Inspect()
{
	{
		std::vector<const char*> scriptlist((int)(ScriptType::SCRIPT_COUNT) + 1);
		std::vector <std::string > scriptlistString((int)(ScriptType::SCRIPT_COUNT) + 1);
		int a = 0;
		scriptlist[a] = "Add Script Type";
		scriptlistString[a] = "Add Script Type";
		a++;
		for (int i = 0; i < (int)(ScriptType::SCRIPT_COUNT); i ++)
		{
			scriptlistString[a] = ToScriptName((ScriptType)(i));
			scriptlist[a] = scriptlistString[a].c_str();
			a++;
		}
	
	
		ComboFilterState s = { 0, 0 };
	
		char buf[128];
	
		ImGuiFunctions Function;
		static bool op1 = false;
		static bool* open1 = &op1;
	
		strncpy(buf, "Add Script Type", 26 + 1);
	
		std::string fileName;
	
		//std::string fileName;
	
		if (Function.ComboFilter("                                    ##Add Script", buf, IM_ARRAYSIZE(buf), scriptlist, scriptlist.size(), s, fileName, open1))
		{
			AddScript2(fileName);
		}
	
		ImGui::Spacing();
		ImGui::Spacing();
	}


	// itr through _scriptContianer and call the actual IScript2* from LogicSys _scriptList
	//for (auto script2id : GetScriptContianer())
	int i = 0;
	for (auto& script2ptrs : MyLogicSystem.GetScriptList(GetParentId()))
	{
		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();
		std::string ScriptString = std::string("Script Type: ") + std::string(ToScriptName(script2ptrs->_type));
		ImGui::Text(ScriptString.c_str());
		ImGui::SameLine();

		std::string deleteScriptString = "Delete Script ##" + std::to_string(i);
		if (ImGui::Button(deleteScriptString.c_str()))
		{
			_scriptContianer.erase(script2ptrs->_type);
			size_t id = script2ptrs->_uId;
			delete MyLogicSystem.GetScriptList()[script2ptrs->_uId];
			MyLogicSystem.GetScriptList().erase(id);
			break;
		}
		ImGui::Spacing();
		script2ptrs->Inspect(); // and call their inspects
		i++;
	}




	if (DEBUG_LUA)
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
				if (GetParentPtr()->GetComponent(ToComponentID(itr2)))
					GetParentPtr()->GetComponent(ToComponentID(itr2))->Inspect();
			}
		}
	}
}



void LogicComponent::Init()
{
	for (auto& it : _scriptContianer)
		MyLogicSystem.GetScriptList()[it.second]->Init();
}

void LogicComponent::LoadResource()
{
	for (auto& it : _scriptContianer)
		MyLogicSystem.GetScriptList()[it.second]->LoadResource();
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