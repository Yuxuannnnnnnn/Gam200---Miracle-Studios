#include "PrecompiledHeaders.h"
#include "LogicSystem.h"

#include "Script/Player.h"
#include "Script/Enemy.h"
#include "Script/Bullet.h"
#include "Script/Turret.h"


LogicSystem::~LogicSystem()
{
	for (auto& itr : _scriptTypeMap)
		delete itr.second;

	_scriptTypeMap.clear();

	for (auto& itr : _scriptList)
		delete itr.second;

	_scriptList.clear();
}

void LogicSystem::Init() {
	enableScript2 = bUseOldScripting;

	RegisterScript(Player);
	RegisterScript(Enemy);
	RegisterScript(Bullet);
	RegisterScript(Turret);

	//ScriptSystem.Init();
}
void LogicSystem::Update(double dt) {
	for (auto& itr : GetComponentMap(Logic)) {

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

std::unordered_map<std::string, ScriptCreator*>& LogicSystem::GetScriptTypeMap()
{
	return _scriptTypeMap;
}





//void LogicSystem::Update(double dt)
//{
//	for (auto it : MyComponentManger._logicComponents)
//	{
//		if (it.second->GetParentId() < 1000 || it.second->GetParentPtr()->GetDestory())
//			continue;
//
//		if (!it.second->GetEnable() || !it.second->_componentEnable)
//			continue;
//
//		for (auto it2 : it.second->_scriptList)
//		{
//			if (!it2.second->_componentEnable)
//				continue;
//			it2.second->Update(dt);
//		}
//	}
//}
//
//
//
//IScript* LogicSystem::AddScript(LogicComponent* object, ScriptId scriptType)
//{
//	if (!object)
//		return nullptr;
//
//	switch (scriptType)
//	{
//	case ScriptId::EMPTY:
//		break;
//	case ScriptId::PLAYER:
//	{
//		Player* newScript = new Player();
//		newScript->SetParentPtr(object->GetParentPtr());
//		newScript->SetParentId(object->GetParentId());
//		newScript->SetType(ScriptId::PLAYER);
//		_scriptList.insert(std::pair<size_t, IScript*>(object->GetParentId(), newScript));
//		return newScript;
//	}
//	case ScriptId::BULLET:
//	{
//		Bullet* newScript = new Bullet();
//		newScript->SetParentPtr(object->GetParentPtr());
//		newScript->SetParentId(object->GetParentId());
//		newScript->SetType(ScriptId::BULLET);
//		_scriptList.insert(std::pair<size_t, IScript*>(object->GetParentId(), newScript));
//		return newScript;
//	}
//	case ScriptId::ENEMY:
//	{
//		Enemy* newScript = new Enemy();
//		newScript->SetParentPtr(object->GetParentPtr());
//		newScript->SetParentId(object->GetParentId());
//		newScript->SetType(ScriptId::ENEMY);
//		_scriptList.insert(std::pair<size_t, IScript*>(object->GetParentId(), newScript));
//		return newScript;
//	}
//	//case ScriptId::ENEMYTWO:
//	//{
//	//	Enemy* newScript = new Enemy();
//	//	newScript->SetParentPtr(object->GetParentPtr());
//	//	newScript->SetParentId(object->GetParentId());
//	//	newScript->SetType(ScriptId::ENEMYTWO);
//	//	_scriptList.insert(std::pair<size_t, IScript*>(object->GetParentId(), newScript));
//	//	return newScript;
//	//}
//	case ScriptId::ENEMYTHREE:
//	{
//		EnemyThree* newScript = new EnemyThree();
//		newScript->SetParentPtr(object->GetParentPtr());
//		newScript->SetParentId(object->GetParentId());
//		newScript->SetType(ScriptId::ENEMYTHREE);
//		_scriptList.insert(std::pair<size_t, IScript*>(object->GetParentId(), newScript));
//		return newScript;
//	}
//	case ScriptId::TURRET:
//	{
//		Turret* newScript = new Turret();
//		newScript->SetParentPtr(object->GetParentPtr());
//		newScript->SetParentId(object->GetParentId());
//		newScript->SetType(ScriptId::TURRET);
//		_scriptList.insert(std::pair<size_t, IScript*>(object->GetParentId(), newScript));
//		return newScript;
//	}
//	case ScriptId::SPAWNER:
//	{
//		Spawner* newScript = new Spawner();
//		newScript->SetParentPtr(object->GetParentPtr());
//		newScript->SetParentId(object->GetParentId());
//		newScript->SetType(ScriptId::SPAWNER);
//		_scriptList.insert(std::pair<size_t, IScript*>(object->GetParentId(), newScript));
//		return newScript;
//	}
//	case ScriptId::SPAWNERTWO:
//	{
//		SpawnerTwo* newScript = new SpawnerTwo();
//		newScript->SetParentPtr(object->GetParentPtr());
//		newScript->SetParentId(object->GetParentId());
//		newScript->SetType(ScriptId::SPAWNERTWO);
//		_scriptList.insert(std::pair<size_t, IScript*>(object->GetParentId(), newScript));
//		return newScript;
//	}
//	case ScriptId::EXPLOSION:
//	{
//		Explosion* newScript = new Explosion();
//		newScript->SetParentPtr(object->GetParentPtr());
//		newScript->SetParentId(object->GetParentId());
//		newScript->SetType(ScriptId::EXPLOSION);
//		_scriptList.insert(std::pair<size_t, IScript*>(object->GetParentId(), newScript));
//		return newScript;
//	}
//	case ScriptId::BUTTON_UI:
//	{
//		ButtonUI* newScript = new ButtonUI();
//		newScript->SetParentPtr(object->GetParentPtr());
//		newScript->SetParentId(object->GetParentId());
//		newScript->SetType(ScriptId::BUTTON_UI);
//		_scriptList.insert(std::pair<size_t, IScript*>(object->GetParentId(), newScript));
//		return newScript;
//	}
//	case ScriptId::PICK_UPS:
//	{
//		PickUps* newScript = new PickUps();
//		newScript->SetParentPtr(object->GetParentPtr());
//		newScript->SetParentId(object->GetParentId());
//		newScript->SetType(ScriptId::PICK_UPS);
//		_scriptList.insert(std::pair<size_t, IScript*>(object->GetParentId(), newScript));
//		return newScript;
//	}
//	case ScriptId::BOSS:
//	{
//		Boss* newScript = new Boss();
//		newScript->SetParentPtr(object->GetParentPtr());
//		newScript->SetParentId(object->GetParentId());
//		newScript->SetType(ScriptId::BOSS);
//		_scriptList.insert(std::pair<size_t, IScript*>(object->GetParentId(), newScript));
//		return newScript;
//	}
//	default:
//		break;
//	}
//
//	return nullptr;
//}
//
//IScript* LogicSystem::CloneScript(LogicComponent* object, IScript* script, ScriptId scriptType)
//{
//	if (!object)
//		return nullptr;
//
//	switch (scriptType)
//	{
//	case ScriptId::EMPTY:
//		break;
//	case ScriptId::PLAYER:
//	{
//		Player* newScript = new Player(*reinterpret_cast<Player*>(script));
//		newScript->SetParentPtr(object->GetParentPtr());
//		newScript->SetParentId(object->GetParentId());
//		newScript->SetType(ScriptId::PLAYER);
//		_scriptList.insert(std::pair<size_t, IScript*>(object->GetParentId(), newScript));
//		return newScript;
//	}
//	case ScriptId::BULLET:
//	{
//		Bullet* newScript = new Bullet(*reinterpret_cast<Bullet*>(script));
//		newScript->SetParentPtr(object->GetParentPtr());
//		newScript->SetParentId(object->GetParentId());
//		newScript->SetType(ScriptId::BULLET);
//		_scriptList.insert(std::pair<size_t, IScript*>(object->GetParentId(), newScript));
//		return newScript;
//	}
//	case ScriptId::ENEMY:
//	{
//		Enemy* newScript = new Enemy(*reinterpret_cast<Enemy*>(script));
//		newScript->SetParentPtr(object->GetParentPtr());
//		newScript->SetParentId(object->GetParentId());
//		newScript->SetType(ScriptId::ENEMY);
//		_scriptList.insert(std::pair<size_t, IScript*>(object->GetParentId(), newScript));
//		return newScript;
//	}
//	//case ScriptId::ENEMYTWO:
//	//{
//	//	Enemy* newScript = new Enemy(*reinterpret_cast<Enemy*>(script));
//	//	newScript->SetParentPtr(object->GetParentPtr());
//	//	newScript->SetParentId(object->GetParentId());
//	//	newScript->SetType(ScriptId::ENEMYTWO);
//	//	_scriptList.insert(std::pair<size_t, IScript*>(object->GetParentId(), newScript));
//	//	return newScript;
//	//}
//	case ScriptId::ENEMYTHREE:
//	{
//		EnemyThree* newScript = new EnemyThree(*reinterpret_cast<EnemyThree*>(script));
//		newScript->SetParentPtr(object->GetParentPtr());
//		newScript->SetParentId(object->GetParentId());
//		newScript->SetType(ScriptId::ENEMYTHREE);
//		_scriptList.insert(std::pair<size_t, IScript*>(object->GetParentId(), newScript));
//		return newScript;
//	}
//	case ScriptId::TURRET:
//	{
//		Turret* newScript = new Turret(*reinterpret_cast<Turret*>(script));
//		newScript->SetParentPtr(object->GetParentPtr());
//		newScript->SetParentId(object->GetParentId());
//		newScript->SetType(ScriptId::TURRET);
//		_scriptList.insert(std::pair<size_t, IScript*>(object->GetParentId(), newScript));
//		return newScript;
//	}
//	case ScriptId::SPAWNER:
//	{
//		Spawner* newScript = new Spawner(*reinterpret_cast<Spawner*>(script));
//		newScript->SetParentPtr(object->GetParentPtr());
//		newScript->SetParentId(object->GetParentId());
//		newScript->SetType(ScriptId::SPAWNER);
//		_scriptList.insert(std::pair<size_t, IScript*>(object->GetParentId(), newScript));
//		return newScript;
//	}
//	case ScriptId::SPAWNERTWO:
//	{
//		SpawnerTwo* newScript = new SpawnerTwo(*reinterpret_cast<SpawnerTwo*>(script));
//		newScript->SetParentPtr(object->GetParentPtr());
//		newScript->SetParentId(object->GetParentId());
//		newScript->SetType(ScriptId::SPAWNERTWO);
//		_scriptList.insert(std::pair<size_t, IScript*>(object->GetParentId(), newScript));
//		return newScript;
//	}
//	case ScriptId::EXPLOSION:
//	{
//		Explosion* newScript = new Explosion(*reinterpret_cast<Explosion*>(script));
//		newScript->SetParentPtr(object->GetParentPtr());
//		newScript->SetParentId(object->GetParentId());
//		newScript->SetType(ScriptId::EXPLOSION);
//		_scriptList.insert(std::pair<size_t, IScript*>(object->GetParentId(), newScript));
//		return newScript;
//	}
//	case ScriptId::BUTTON_UI:
//	{
//		ButtonUI* newScript = new ButtonUI(*reinterpret_cast<ButtonUI*>(script));
//		newScript->SetParentPtr(object->GetParentPtr());
//		newScript->SetParentId(object->GetParentId());
//		newScript->SetType(ScriptId::BUTTON_UI);
//		_scriptList.insert(std::pair<size_t, IScript*>(object->GetParentId(), newScript));
//		return newScript;
//	}
//	case ScriptId::PICK_UPS:
//	{
//		PickUps* newScript = new PickUps(*reinterpret_cast<PickUps*>(script));
//		newScript->SetParentPtr(object->GetParentPtr());
//		newScript->SetParentId(object->GetParentId());
//		newScript->SetType(ScriptId::PICK_UPS);
//		_scriptList.insert(std::pair<size_t, IScript*>(object->GetParentId(), newScript));
//		return newScript;
//	}
//	case ScriptId::BOSS:
//	{
//		Boss* newScript = new Boss(*reinterpret_cast<Boss*>(script));
//		newScript->SetParentPtr(object->GetParentPtr());
//		newScript->SetParentId(object->GetParentId());
//		newScript->SetType(ScriptId::BOSS);
//		_scriptList.insert(std::pair<size_t, IScript*>(object->GetParentId(), newScript));
//		return newScript;
//	}
//	default:
//		break;
//	}
//
//	return nullptr;
//}
//
//void LogicSystem::RemoveScript(LogicComponent* object, ScriptId scriptType)
//{
//	std::pair <std::unordered_multimap<size_t, IScript*>::iterator, std::unordered_multimap<size_t, IScript*>::iterator> ret;
//	ret = _scriptList.equal_range(object->GetParentId());
//
//	for (std::unordered_multimap<size_t, IScript*>::iterator it = ret.first; it != ret.second; ++it)
//	{
//		if (it->second->GetType() == scriptType)
//		{
//			delete it->second;
//			_scriptList.erase(it);
//			return;
//		}
//	}
//}
//
//void LogicSystem::DeleteLevelScripts()
//{
//	for (auto it : _scriptList)
//		delete it.second;
//	_scriptList.clear();
//}