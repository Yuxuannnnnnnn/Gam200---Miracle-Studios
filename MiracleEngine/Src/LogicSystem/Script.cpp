#include "PrecompiledHeaders.h"
#include "Script.h"

namespace Script_1 {
	void Update()
	{
		std::cout << "SCRIPT - 1" << std::endl;
	}
}

namespace Script_2 {
	void Update(LogicComponent* parent)
	{
		std::cout << "SCRIPT - 2" << "\t :: \t";
		TransformComponent* temp = (TransformComponent*)parent->GetSibilingComponent((unsigned)TypeIdComponent::TRANSFORMCOMPONENT);
		Vector3 tempVec = temp->GetPos();
		std::cout << tempVec._x << ",";		
		tempVec._x += 1;
		temp->GetPos() = tempVec;
		std::cout << tempVec._x;

		RigidBody2D* tempOne = (RigidBody2D*)parent->GetSibilingComponent((unsigned)TypeIdComponent::RIGIDBODYCOMPONENT);
		std::cout << "\t ~ " << tempOne->_angle;
		std::cout << std::endl;
	}
}

namespace Script_HealthMinus {
	void Update(int& health, int changeVal)
	{
		std::cout << "SCRIPT - HealthMinus" << std::endl;
	}
}





//#pragma once
//#include "PrecompiledHeaders.h"
//
//enum ScriptId {
//	// note, this is supposed to co-relate to the
//	// list of scripts in bottom half of this file
//	EMPTY = 0,
//	TEST1 = 1,
//	MOVE,
//	HEALTHMINUS,
//};
//
//class Script
//{
//	// list of scripts
//	ScriptId _ScriptId;
//public:
//	Script() = default;
//	Script(ScriptId scriptId)
//	{
//		SetScript(scriptId);
//	}
//	~Script() = default;
//	Script(const Script& rhs) = default;
//	Script& operator=(const Script& rhs) = default;
//	// InUpEx
//	void Init()
//	{
//	}
//	void Update(ScriptId scriptId)
//	{
//		// depending of _ScriptName, run that particular script
//		switch ((ScriptId)scriptId)
//		{
//		case EMPTY:
//			Test();
//			return;
//		case TEST1:
//			Test1();
//			return;
//		case MOVE:
//			//script = (void*)Move;
//			//void* (*funcPointerC)() = reinterpret_cast<void* (*)()>(funcInt);
//			return;
//		case HEALTHMINUS:
//			return;
//		}
//	}
//	void Exit()
//	{
//		// ?
//	}
//	// Others
//		// GetSet
//	unsigned GetScript()
//	{
//		return (unsigned)_ScriptId;
//	}
//	void SetScript(unsigned scriptName)
//	{
//		_ScriptId = (ScriptId)scriptName;
//	}
//	//////////////////////////////////////////////////////////////
//	// All Script()s below
//	void Test()
//	{
//		std::cout << "Script - Test()" << std::endl;
//	}
//	void Test1(int x = 10)
//	{
//		std::cout << "Script - Test1() " << x << std::endl;
//	}
//	void Move(Vector3& move)
//	{
//		// take parent GO, move by a vector
//	}
//	void HealthMius(int val)
//	{
//		// take parent GO, get its HP, minus by 'val'
//	}
//};
//
//
//class TestGO {
//	Script scriptId;
//public:
//	TestGO() = default;
//	TestGO(ScriptId in)
//	{
//		scriptId = Script(in);
//	}
//	~TestGO() = default;
//};