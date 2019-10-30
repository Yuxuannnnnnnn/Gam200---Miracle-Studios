#include "PrecompiledHeaders.h"
#include "LogicComponent.h"

LogicComponent::LogicComponent(size_t id)
{
	SetParentId(id);
}
// CompName
std::string LogicComponent::ComponentName() const
{
	return "Logic Component";
}
// InUpEx
void LogicComponent::Init()
{
}
void LogicComponent::Update()
{
	if (!_scriptList.empty()) // make sure scriptList is !empty()
	{
		//std::function<void(void)> updatePtr; // dont need, just call the function directly
		//std::function<void(int&, int)> updatePtr_Health;
		std::cout << "GO id : " << this->GetParentId() << std::endl;
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
				//Script_Input::Update(INGAME);
				break;
			default:
				break;
			};
		}
		std::cout << std::endl;
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
