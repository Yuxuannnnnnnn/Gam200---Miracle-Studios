#include "PrecompiledHeaders.h"
#include "GameObject/ComponentManager.h"

ComponentManager::ComponentManager() {}
ComponentManager::~ComponentManager()
{
	for (auto& it : _componentContainers)
	{
		for (auto& it2 : *(it.second))
		{
			delete it2.second;
		}

		delete it.second;
	}

	_componentContainers.clear();
}

void ComponentManager::AddNewComponentContainer(ComponentId tpyeId)
{
	_componentContainers[tpyeId] = new std::unordered_map<size_t, IComponent*>;
}

std::unordered_map<size_t, IComponent*>* ComponentManager::GetComponentContainer(ComponentId tpyeId)
{
	std::unordered_map< ComponentId, std::unordered_map<size_t, IComponent*>* >::iterator it =
		_componentContainers.find(tpyeId);

	if (it == _componentContainers.end())
		return nullptr;

	return it->second;
}

void ComponentManager::ClearAllComponents()
{
	for (auto& it : _componentContainers)
	{
		for (auto& it2 : *(it.second))
		{
			delete it2.second;
		}

		it.second->clear();
	}
}