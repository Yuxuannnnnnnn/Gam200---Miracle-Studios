#include "PrecompiledHeaders.h"
#include "Script.h"


///////// SCRAPPED VERSION, unable to dynamically select which function to set in the generic funcPtr()
//#include "PrecompiledHeaders.h"
//
//enum ScriptNames {
//	// note, this is supposed to co-relate to the
//	// list of scripts in bottom half of this file
//	NONE = 0,
//	MOVE,
//	HEALTHMINUS,
//};
//
//class Script
//{
//	// list of scripts
//	std::vector<void*> _listScript;
//public:
//	Script() = default;
//	~Script() = default;
//	Script(const Script& rhs) = default;
//	Script& operator=(const Script& rhs) = default;
//	// InUpEx
//	void Init()
//	{
//		// ?
//	}
//	void Update()
//	{
//		// run through _listScript and run scripts
//		std::vector<void*>::iterator itr = _listScript.begin();
//		while (itr != _listScript.end())
//			;
//	}
//	void Exit()
//	{
//		// ?
//	}
//	// Others
//		// GetSet
//
//		// Add script to 'listScript'
//	void AddScript(ScriptNames scriptName)
//	{
//		//void (*script)(void);
//		switch (scriptName)
//		{
//		case MOVE:
//			//script = (void*)Move;
//			void* (*funcPointerC)() = reinterpret_cast<void* (*)()>(funcInt);
//			break;
//		case HEALTHMINUS:
//			break;
//		}
//		_listScript.emplace_back(script);
//	}
//	//////////////////////////////////////////////////////////////
//	// All Script()s below
//	void Move(Vector3& move)
//	{
//		// take parent GO, move by a vector
//	}
//	void HealthMius(int val)
//	{
//		// take parent GO, get its HP, minus by 'val'
//	}
//	void funcInt()
//	{
//
//	}
//};