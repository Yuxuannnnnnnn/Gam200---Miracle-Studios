#include "PrecompiledHeaders.h"
#include "LogicComponent.h"

LogicComponent::LogicComponent(GameObject* parent, size_t uId, IComponentSystem* component)
	:IComponentSystem(parent, uId)
{
	if (component)
	{
		LogicComponent* logicComponent = dynamic_cast<LogicComponent*>(component);

		for(auto& script : logicComponent->_scriptList)
		 _scriptList.emplace_back(script);
		// Logic Related Stats
		 _health = logicComponent->_health;
		 _speed = logicComponent->_speed;
		 _lifetime = logicComponent->_lifetime;
	}
}


// CompName
std::string LogicComponent::ComponentName() const
{
	return "Logic Component";
}


void LogicComponent::SerialiseComponent(Serialiser& document)
{

	if (document.HasMember("_scriptList") && document["_scriptList"].IsArray())	//Checks if the variable exists in .Json file
		for (int i = 0; i < document["ScriptId"].Size(); i++)
		{
			if(document["ScriptId"][i].IsInt())
				_scriptList.emplace_back(document["ScriptId"][i].GetInt());
		}

	if (document.HasMember("Health") && document["Health"].IsInt())	//Checks if the variable exists in .Json file
		_health = document["Health"].GetInt();

	if (document.HasMember("Speed") && document["Speed"].IsInt())	//Checks if the variable exists in .Json file
		_speed = document["Speed"].GetInt();

	if (document.HasMember("Lifetime") && document["Lifetime"].IsInt())	//Checks if the variable exists in .Json file
		_lifetime = document["Lifetime"].GetInt();

}

void LogicComponent::Inspect()
{
}


// InUpEx
void LogicComponent::Init()
{
}



void LogicComponent::Update(GameObjectFactory* factory, GameObject* obj, InputSystem* input)
{
	if (!_scriptList.empty()) // make sure scriptList is !empty()
	{
		//std::function<void(void)> updatePtr; // dont need, just call the function directly
		//std::function<void(int&, int)> updatePtr_Health;
		for (int scriptId : _scriptList)
		{
			switch (scriptId)
			{
			case SCRIPT_1:
				Script_1::Update();
				break;
			case SCRIPT_2:
				Script_2::Update(this);
				break;
			case SCRIPT_HEALTH:
				Script_HealthMinus::Update(_health, 1);
				break;
			case SCRIPT_INPUT:
				Script_Input::Update(factory, obj, input);
				break;
			case SCRIPT_SHOOT:
				Script_Shoot::Update(this->GetParentPtr(), factory);
			case SCRIPT_MOVE:
				Script_Move::Update(this->GetParentPtr());
			default:
				break;
			};
		}
		std::cout << std::endl;
	}
	if (_lifetime)
	{
		// kill obj if _lifetime is over
	}
}
void LogicComponent::Exit()
{
	// ?
}
// Others
// GetScript
std::vector<int>& LogicComponent::GetScriptId()
{
	return _scriptList;
}
// GetHealth
int& LogicComponent::GetHealth()
{
	return _health;
}
// GetHealth
int& LogicComponent::GetSpeed()
{
	return _speed;
}
// GetHealth
int& LogicComponent::GetLifetime()
{
	return _lifetime;
}
