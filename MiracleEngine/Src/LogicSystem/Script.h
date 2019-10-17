#pragma once
#include "PrecompiledHeaders.h"

enum ScriptId {
	// note, this is supposed to co-relate to the
	// list of scripts in bottom half of this file
	EMPTY = 0,
	TEST1 = 1,
	MOVE,
	HEALTHMINUS,
};

class Script
{
	// list of scripts
	ScriptId _ScriptId;
public:
	Script() = default;
	Script(ScriptId scriptId)
	{
		SetScript(scriptId);
	}
	~Script() = default;
	Script(const Script& rhs) = default;
	Script& operator=(const Script& rhs) = default;
// InUpEx
	void Init()
	{
	}
	void Update(ScriptId scriptId)
	{
		// depending of _ScriptName, run that particular script
		switch ((ScriptId)scriptId)
		{
		case EMPTY:
			Test();
			return;
		case TEST1:
			Test1();
			return;			
		case MOVE:
			//script = (void*)Move;
			//void* (*funcPointerC)() = reinterpret_cast<void* (*)()>(funcInt);
			return;
		case HEALTHMINUS:
			return;
		}
	}
	void Exit()
	{
		// ?
	}
// Others
	// GetSet
	unsigned GetScript()
	{
		return (unsigned)_ScriptId;
	}
	void SetScript(unsigned scriptName)
	{
		_ScriptId = (ScriptId)scriptName;
	}
//////////////////////////////////////////////////////////////
// All Script()s below
	void Test()
	{
		std::cout << "Script - Test()" << std::endl;
	}
	void Test1(int x = 10)
	{
		std::cout << "Script - Test1() " << x << std::endl;
	}
	void Move(Vector3& move)
	{
		// take parent GO, move by a vector
	}
	void HealthMius(int val)
	{
		// take parent GO, get its HP, minus by 'val'
	}
};


class TestGO {
	Script scriptId;
public:
	TestGO() = default;
	TestGO(ScriptId in)
	{
		scriptId = Script(in);
	}
	~TestGO() = default;
};