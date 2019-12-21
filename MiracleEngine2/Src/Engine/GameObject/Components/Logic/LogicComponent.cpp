#include "PrecompiledHeaders.h"
#include "LogicComponent.h"

LogicComponent::LogicComponent() : _componentEnable{ true }
{};

LogicComponent::LogicComponent(GameObject* parent, size_t uId, IComponent* component)
	: IComponent(parent, uId), _componentEnable{ true }
{
	if (component)
	{
		LogicComponent* logicComponent = dynamic_cast<LogicComponent*>(component);

		for (auto& script : logicComponent->_scriptList)
		{
			IScript* Script = new IScript(*(script.second));
			_scriptList.insert(std::pair<unsigned, IScript*>(script.first, Script));
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
				std::string str = document["ScriptId"][i].GetString();
				ScriptId temp = IScript::ScriptStringToInt(str);
				IScript* newScript = AddScript((ScriptId)temp);
				newScript->SerialiseComponent(document);
			}
		}
}

void LogicComponent::DeSerialiseComponent(DeSerialiser& prototypeDoc)
{
	rapidjson::Value value;

	value.SetArray();
	for (auto& scriptPair : _scriptList)
	{
		value.PushBack(rapidjson::Value(scriptPair.first).Move(), prototypeDoc.Allocator());
	}

	prototypeDoc.AddMember("ScriptId", value);
}



void LogicComponent::Inspect()
{
	IComponent::Inspect();
	for (auto& scriptPair : _scriptList)
	{
		scriptPair.second->Inspect();
	}
}


void LogicComponent::Update(double dt)
{
	for (auto it : _scriptList)
	{
		if (!it.second->_componentEnable)
			continue;

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

	IScript* newScript = EngineSystems::GetInstance()._logicSystem->AddScript(this, scriptType);
	_scriptList.insert(std::pair<unsigned, IScript*>((unsigned)scriptType, newScript));

	return newScript;
}

void LogicComponent::RemoveScript(ScriptId scriptType)
{
	if (!CheckScript(scriptType))
		return;

	EngineSystems::GetInstance()._logicSystem->RemoveScript(this, scriptType);
	_scriptList.erase((unsigned)scriptType);
}

IScript* LogicComponent::GetScript(ScriptId scriptType)
{
	return _scriptList[(unsigned)scriptType];
}