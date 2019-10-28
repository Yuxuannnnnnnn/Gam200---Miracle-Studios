#pragma once
#include <string>
#include "PrecompiledHeaders.h"

enum class TypeIdSiblingComp { // direct copy of the one in GameObject
	TRANSFORMCOMPONENT = 0,
	GRAPHICSCOMPONENT = 1,
	RIGIDBODYCOMPONENT = 2,
	COLLIDERCOMPONENT = 3,
	LOGICCOMPONENT = 4,
	AUDIOCOMPONENT = 5
};

class GameObject; // forward declaration

class IComponentSystem
{
public:
	GameObject* _ParentPtr{ nullptr };
	size_t _ParentId{ 0 };

	virtual std::string ComponentName() const;

	size_t GetParentId() const;
	GameObject* GetParentPtr();
	IComponentSystem* GetSibilingComponent(unsigned _componentId);
};

