#pragma once
#include "PrecompiledHeaders.h"

enum ScriptId {
	// note, this is supposed to co-relate to the
	// list of scripts in 'Script.h'
	EMPTY = 0,
	SCRIPT_1,
	SCRIPT_2,
	SCRIPT_INPUT,
};

class LogicComponent : public IComponentSystem
{
// _Parent
	size_t _ParentId;
// list of scripts
	std::vector<ScriptId> _ScriptList;
public:
	LogicComponent(size_t id) : _ParentId{ id } {}
	~LogicComponent() = default;
	LogicComponent(const LogicComponent& rhs) = default;
	LogicComponent& operator=(const LogicComponent& rhs) = default;
// GetPID
	size_t GetParentId() const override
	{
		return _ParentId;
	}
	// InUpEx
	void Init()
	{
	}
	void Update(ScriptId scriptId)
	{
		
	}
	void Exit()
	{
		// ?
	}
// Others
		//typedef int (*fptr)();
		//void(*Update)(void) GetScript(ScriptId id)
		//{
		//	switch (id)
		//	{
		//	case EMPTY:
		//		return nullptr;
		//	case SCRIPT_1:
		//		return Script1::Update();
		//	case SCRIPT_2:
		//		return nullptr;
		//	case SCRIPT_INPUT:
		//		return nullptr;
		//	}
		//}
};
