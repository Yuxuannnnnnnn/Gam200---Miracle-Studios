#pragma once

#include "GameObject/Components/PrecompiledComponentHeader.h"

#include "GameObject/ComponentCreator.h"

class ComponentManager final
{
	std::unordered_map< ComponentId, std::unordered_map<size_t, IComponent*>* > _componentContainers;

public:
	ComponentManager();
	~ComponentManager();

	void RegisterAllComponent();

	void AddNewComponentContainer(ComponentId tpyeId);

	std::unordered_map<size_t, IComponent*>* GetComponentContainer(ComponentId tpyeId);

	void ClearAllComponents();
};

#define GetComponentMap(type) (*EngineSystems::GetInstance()._componentManager->GetComponentContainer(ComponentId::CT_##type))