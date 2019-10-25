#pragma once
#include "PrecompiledHeaders.h"
#include "LogicSystem/Script.h"

enum ScriptId {
	// note, this is supposed to co-relate to the
	// list of scripts in 'Script.h'
	EMPTY = 0,
	SCRIPT_1 = 1,
	SCRIPT_2 = 2,
	SCRIPT_HEALTH = 3,
	SCRIPT_INPUT = 4,
};

class LogicComponent : public IComponentSystem
{
// _Parent
	size_t _ParentId;
// list of scripts
	//int _scriptId;
	std::vector<int> _scriptList;
// Logic Related Stats
	int _health{ 0 };
	int _speed{ 0 };
	int _lifetime{ 0 };

public:
	LogicComponent(size_t id = 0) : _ParentId{ id } {}
	~LogicComponent() = default;
	LogicComponent(const LogicComponent& rhs) = default;
	LogicComponent& operator=(const LogicComponent& rhs) = default;
// GetPID
	size_t GetParentId() const override
	{
		return _ParentId;
	}
// CompName
	std::string ComponentName() const
	{
		return "Logic Component";
	}
// InUpEx
	void Init()
	{
	}
	void Update()
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
	void Exit()
	{
		// ?
	}
// Others
// GetScript
	std::vector<int>& GetScriptId()
	{
		return _scriptList;
	}
// GetHealth
	int& GetHealth()
	{
		return _health;
	}
// GetHealth
	int& GetSpeed()
	{
		return _speed;
	}
// GetHealth
	int& GetLifetime()
	{
		return _lifetime;
	}
};
