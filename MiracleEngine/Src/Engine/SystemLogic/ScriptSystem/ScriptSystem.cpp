#include "PrecompiledHeaders.h"
#include "ScriptSystem.h"

void ScriptSystem::Create_TableScriptData()
{
	std::unordered_map<std::string, std::vector<std::string>> _TableScriptData;

	_TableScriptData["health"] = std::vector<std::string>{ "health" };
	_TableScriptData["ammo"] = std::vector<std::string>{ "ammo" };
	_TableScriptData["shield"] = std::vector<std::string>{ "capacity", "recharge" };
}

void ScriptSystem::RunScript(GameObject* src, std::string& scriptName)
{

}

void ScriptSystem::Init() {
	Create_TableScriptData();
}
//void ScriptSystem::Update(float dt) {}
void ScriptSystem::Exit() {

}