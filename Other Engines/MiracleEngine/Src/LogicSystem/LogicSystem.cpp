#include "PrecompiledHeaders.h"
#include "LogicSystem.h"

// InUpEx
void LogicSystem::Init()
{
	// attach all scripts to objects

	// load all GOs with logic component into private:list
}
void LogicSystem::Update(const std::unordered_map < size_t, LogicComponent* >& lcmap,
	GameObjectFactory* factory, InputSystem* input)
{
	// update should be like this, take in the 'map of logic comps, from GOFac'
	//void GraphicsSystem::Update(const std::unordered_map < size_t, GraphicComponent* > & graphicmap)


	// run through 'list' and update the logic
		// update scripts
			// access std::vector<script> from GO
			// itr through and run all scripts
		// update AI

	GameObject* tmp = nullptr;
	for (auto const& x : lcmap)
	{
		//tmp = x.second->GetOwner();
		//_scriptList[x.second->GetID()](tmp);
		x.second->Update(factory, x.second->GetParentPtr(), input);
	}

	for (auto it : _ScriptList2)
	{
		it.second->Update(0.0);
	}

}
void LogicSystem::Exit()
{
	// unload list ?
}
// Others
	// add GO to list

	// add script
void LogicSystem::AddScript(int ID, scriptptr script)
{
	_ScriptList.push_back(script);
}
// update for scripts

void LogicSystem::AddNewScript(IScript* script)
{
	_ScriptList2.insert(ScriptPair(script->GetParentId(), script));
}

std::vector<IScript*> LogicSystem::GetGameObjectScripts(int id)
{
	std::vector<IScript*> temp;

	std::pair <ScriptMap::iterator, ScriptMap::iterator> ret;
	ret = _ScriptList2.equal_range(id);

	for (ScriptMap::iterator it = ret.first; it != ret.second; ++it)
		temp.push_back(it->second);

	return temp;
}