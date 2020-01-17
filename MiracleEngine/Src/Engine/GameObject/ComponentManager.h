#pragma once

#include "GameObject/Components/Graphic/AnimationComponent.h"
#include "GameObject/Components/Graphic/CameraComponent.h"
#include "GameObject/Components/Graphic/FontComponent.h"
#include "GameObject/Components/Graphic/GraphicComponent.h"
#include "GameObject/Components/Graphic/TransformComponent.h"
#include "GameObject/Components/Graphic/UIComponent.h"

#include "GameObject/Components/Logic/LogicComponent.h"

#include "GameObject/Components/Physic/BoxCollider2DComponent.h"
#include "GameObject/Components/Physic/CircleCollider2DComponent.h"
#include "GameObject/Components/Physic/EdgeCollider2DComponent.h"
#include "GameObject/Components/Physic/ICollider2D.h"
#include "GameObject/Components/Physic/RigidBody2DComponent.h"

#include "GameObject/Components/AudioComponent.h"
#include "GameObject/Components/ButtonComponent.h"
#include "GameObject/Components/IdentityComponent.h"
#include "GameObject/Components/TileMapComponent.h"

#include "GameObject/ComponentCreator.h"

class ComponentManager final
{
	std::unordered_map< ComponentId, std::unordered_map<size_t, IComponent*>* > _componentContainers;

public:
	ComponentManager() {}
	~ComponentManager()
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

	void AddNewComponentContainer(ComponentId tpyeId)
	{
		_componentContainers[tpyeId] = new std::unordered_map<size_t, IComponent*>;
	}

	std::unordered_map<size_t, IComponent*>* GetComponentContainer(ComponentId tpyeId)
	{
		std::unordered_map< ComponentId, std::unordered_map<size_t, IComponent*>* >::iterator it =
			_componentContainers.find(tpyeId);

		if (it == _componentContainers.end())
			return nullptr;

		return it->second;
	}

	void ClearAllComponents()
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
};

#define GetComponentMap(type) (*EngineSystems::GetInstance()._componentManager->GetComponentContainer(ComponentId::CT_##type))
