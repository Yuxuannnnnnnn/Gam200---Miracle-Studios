#pragma once
#include "GameObjectComponents/IComponentSystem.h"
#include "LogicSystem/Script.h"

#ifndef LOGICCOMPONENT_H
#define	LOGICCOMPONENT_H


enum ScriptId {
	// note, this is supposed to co-relate to the
	// list of scripts in 'Script.h'
	EMPTY = 0,
	SCRIPT_1 = 1,
	SCRIPT_2 = 2,
	SCRIPT_HEALTH = 3,
	SCRIPT_INPUT = 4,
	SCRIPT_SHOOT = 5,
	SCRIPT_MOVE = 6
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
//Constructor
	LogicComponent(GameObject* parent, size_t uId, IComponentSystem* component = nullptr);
	~LogicComponent() = default;
	LogicComponent(const LogicComponent& rhs) = default;
	LogicComponent& operator=(const LogicComponent& rhs) = default;

// CompName
	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser& document) override;
	virtual void Inspect() override;

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

#endif