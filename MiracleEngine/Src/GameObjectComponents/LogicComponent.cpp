#include "PrecompiledHeaders.h"
#include "LogicComponent.h"

LogicComponent::LogicComponent(size_t id)
{
	_ParentId = id;
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
	if (_scriptList.empty()) // makeSure script is !empty()
	{
		std::function<void(void)> updatePtr;
		std::function<void(int&, int)> updatePtrHealth;
		for (int scriptId : _scriptList)
		{
			// updatePtr for accessing script's Update()
			switch (scriptId)
			{
			case SCRIPT_1:
				updatePtr = Script_1::Update;
				break;
			case SCRIPT_2:
				updatePtr = Script_2::Update;
				break;
			case SCRIPT_HEALTH:
				Script_HealthMinus::Update(_health, 1);
				break;
			case SCRIPT_INPUT:
				//Script_Input::Update(INGAME);
				updatePtr = nullptr;
				break;
			default:
				updatePtr = nullptr;
				break;
			}
			if (updatePtr)
				updatePtr();
		}
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
