#pragma once
#include "PrecompiledHeaders.h"
#include "LogicSystem/Script.h"

enum ScriptId {
	// note, this is supposed to co-relate to the
	// list of scripts in 'Script.h'
	EMPTY = 0,
	SCRIPT_1 = 1,
	SCRIPT_2 = 2,
	SCRIPT_INPUT = 3,
};

class LogicComponent : public IComponentSystem
{
// _Parent
	size_t _ParentId;
// list of scripts
	//int _scriptId;
	std::vector<int> _ScriptList;
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
	void Update(ScriptId scriptId)
	{
		// updatePtr for accessing script's Update()
		std::function<void(void)> updatePtr;
		switch (scriptId)
		{
		case SCRIPT_1:
			updatePtr = Script1::Update;
			break;
		case SCRIPT_2:
			updatePtr = Script2::Update;
			break;
		case SCRIPT_INPUT:
			break;
		default:
			break;
		}
		updatePtr();
	}
	void Exit()
	{
		// ?
	}
// Others
// Get
	std::vector<int>& GetScriptId()
	{
		return _ScriptList;
	}
};
