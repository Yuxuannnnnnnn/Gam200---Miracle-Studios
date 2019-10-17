#pragma once
#include "PrecompiledHeaders.h"

enum ScriptNames {
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
	ScriptNames _ScriptName;
public:
	Script() = default;
	Script(ScriptNames script)
	{
		SetScript(script);
	}
	~Script() = default;
	Script(const Script& rhs) = default;
	Script& operator=(const Script& rhs) = default;
// InUpEx
	void Init()
	{
	}
	void Update(ScriptNames scriptName)
	{
		// depending of _ScriptName, run that particular script
		switch ((ScriptNames)scriptName)
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
		return (unsigned)_ScriptName;
	}
	void SetScript(unsigned scriptName)
	{
		_ScriptName = (ScriptNames)scriptName;
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
	Script script;
public:
	TestGO() = default;
	TestGO(ScriptNames in)
	{
		script = Script(in);
	}
	~TestGO() = default;
};