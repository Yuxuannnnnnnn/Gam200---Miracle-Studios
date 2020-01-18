#pragma once
#include "IScript2.h"

class ScriptCreator
{
public:
	ScriptCreator(ScriptType type)
		:_type(type)
	{
	}

	ScriptType _type;
	///Create the component
	virtual IScript2* Create() = 0;
};

///Templated helper class used to make concrete component creators.
template<typename type>
class ScriptCreatorType : public ScriptCreator
{
public:
	ScriptCreatorType(ScriptType typeId)
		:ScriptCreator(typeId)
	{
	}

	virtual IScript2* Create()
	{
		return new type();
	}
};

//Register component macro
#define RegisterScript(script)  MyLogicSystem.AddScriptCreator( #script, new ScriptCreatorType<script>( ScriptType::SCRIPT_##script ) );