#pragma once
#include "PrecompiledHeaders.h"
#include "GameObjectComponents/IComponentSystem.h"
#include "LogicSystem/Script.h"

enum ScriptId {
	// note, this is supposed to co-relate to the
	// list of scripts in 'Script.h'
	EMPTY = 0,
	SCRIPT_1 = 1,
	SCRIPT_2 = 2,
	SCRIPT_HEALTH = 3,
	SCRIPT_INPUT = 4,
	SCRIPT_SHOOT = 5,
};

class LogicComponent : public IComponentSystem
{
// list of scripts
	//int _scriptId;
	std::vector<int> _scriptList;
// Logic Related Stats
	int _health{ 0 };
	int _speed{ 0 };
	int _lifetime{ 0 };

public:
	LogicComponent(size_t id = 0);
	//~LogicComponent() = default;
	//LogicComponent(const LogicComponent& rhs) = default;
	//LogicComponent& operator=(const LogicComponent& rhs) = default;

// CompName
	std::string ComponentName() const override;
// InUpEx
	void Init();
	void Update(GameObjectFactory* factory, GameObject* obj, InputSystem* input);
	void Exit();
// Others
// GetScript
	std::vector<int>& GetScriptId();
// GetHealth
	int& GetHealth();
// GetHealth
	int& GetSpeed();
// GetHealth
	int& GetLifetime();
};
