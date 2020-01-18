#include "PrecompiledHeaders.h"
#include "IScript2.h"

IScript2::IScript2() :
	_parent{ nullptr },
	_uId{ 0 },
	_type{ ScriptType::SCRIPT_COUNT },
	_scriptEnable{ true }
{
}