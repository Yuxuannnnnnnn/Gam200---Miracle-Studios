#include "PrecompiledHeaders.h"
#include "LogicSystem.h"
#include "Script/Player.h"
#include "Script/Enemy.h"
#include "Script/Bullet.h"
#include "Script/Turret.h"
#include "Script/Spawner.h"
#include "Script/Explosion.h"
#include "Script/PickUps.h"
#include "Script/ButtonController.h"
#include "Script/HealthController.h"
#include "Script/ShieldSkill.h"
#include "Script/HitEffect.h"
#include "Script/MouseCursor.h"
#include "Script/EntrancePortal.h"
#include "Script/PauseMenu.h"
#include "Script/SplashScreen.h"
#include "Script/Boss.h"
#include "Script/LoadingScreen.h"
#include "Script/BossHealthController.h"
#include "Script/OptionScript.h"
#include "Script/WeaponTabs.h"



LogicSystem::~LogicSystem()
{
	for (auto& itr : _scriptTypeMap)
		delete itr.second;

	_scriptTypeMap.clear();

	for (auto& itr : _scriptList)
		delete itr.second;

	_scriptList.clear();
}

LogicSystem::LogicSystem() :
	_scriptUId{ 0 },
	enableScript2{ false },
	_resgister{ false }
{
}

void LogicSystem::RegisterAllScript()
{
	RegisterScript(Player);
	RegisterScript(Enemy);
	RegisterScript(Bullet);
	RegisterScript(Turret);
	RegisterScript(Spawner);
	RegisterScript(Explosion);
	RegisterScript(PickUps);
	RegisterScript(ButtonController);
	RegisterScript(HealthController);
	RegisterScript(ShieldSkill);
	RegisterScript(MouseCursor);
	RegisterScript(EntrancePortal);
	RegisterScript(PauseMenu);
	RegisterScript(HitEffect);
	RegisterScript(SplashScreen);
	RegisterScript(Boss);
	RegisterScript(LoadingScreen);
	RegisterScript(BossHealthController);
	RegisterScript(OptionScript);
	RegisterScript(WeaponTabs);
}

void LogicSystem::Init() {
	enableScript2 = bUseOldScripting;

	for (auto& itr : GetComponentMap(Logic)) 
	{
		LogicComponent* obj = (LogicComponent*)itr.second;

		if (obj && enableScript2)
		{
			for (auto& itr : obj->GetScriptContianer())
			{
				_scriptList[itr.second]->Init();
			}
		}


	}

	//ScriptSystem.Init();
}

void LogicSystem::LoadResource()
{
	for (auto& itr : GetComponentMap(Logic))
	{
		LogicComponent* obj = (LogicComponent*)itr.second;

		if (obj && enableScript2)
		{
			for (auto& itr : obj->GetScriptContianer())
			{
				_scriptList[itr.second]->LoadResource();
			}
		}
	}
}


void LogicSystem::Update(double dt) {
	for (auto& itr : GetComponentMap(Logic)) {

		if (!itr.second || !itr.second->GetEnable())
			continue;

		LogicComponent* obj = (LogicComponent*)itr.second;

		

		if (enableScript2)
		{
			for (auto& itr : obj->GetScriptContianer())
			{
				_scriptList[itr.second]->Update(dt);
			}
		}
		else
			obj->Update(dt);
	}
}

/////////////////////////////////////////////////////////////////////////////
// c++ scripting

void LogicSystem::AddScriptCreator(std::string scriptName, ScriptCreator* scriptCreator)
{
	_scriptTypeMap[scriptName] = scriptCreator;
}

IScript2* LogicSystem::CloneScript2(size_t uId)
{
	IScript2* newScript = _scriptList[uId]->Clone();
	newScript->_uId = ++_scriptUId;

	_scriptList[newScript->_uId] = newScript;

	return newScript;
}

IScript2* LogicSystem::CreateNewScript(const std::string& scriptName)
{
	IScript2* newScript = _scriptTypeMap[scriptName]->Create();
	newScript->_uId = ++_scriptUId;
	newScript->_type = _scriptTypeMap[scriptName]->_type;

	_scriptList[newScript->_uId] = newScript;

	return newScript;
}

std::unordered_map<size_t, IScript2*>& LogicSystem::GetScriptList()
{
	return _scriptList;
}


IScript2* LogicSystem::getScriptPtr(size_t uID)
{
	if (_scriptList.find(uID) != _scriptList.end())
	{
		return _scriptList[uID];
	}

	return nullptr;
}


std::unordered_map<std::string, ScriptCreator*>& LogicSystem::GetScriptTypeMap()
{
	return _scriptTypeMap;
}


std::vector<IScript2*> LogicSystem::GetScriptList(size_t objUId)
{
	std::vector<IScript2*> result;

	LogicComponent* obj = (LogicComponent*)GetComponentMap(Logic)[objUId];

	if (!obj || !obj->GetEnable())
		return result;

	for (auto& it : obj->GetScriptContianer())
		result.push_back(_scriptList[it.second]);

	return result;
}

void LogicSystem::ClearAllScripts()
{
#ifndef LEVELEDITOR
	for (auto& itr : _scriptList)
		delete itr.second;

	_scriptList.clear();

	_scriptUId = 0;
#endif
}