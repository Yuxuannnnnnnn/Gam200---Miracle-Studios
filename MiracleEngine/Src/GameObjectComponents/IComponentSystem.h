#pragma once
#include <string>
#include "PrecompiledHeaders.h"

#ifndef ICOMPONENTSYSTEM_H
#define	ICOMPONENTSYSTEM_H

enum class TypeIdComponent {
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
private:

	GameObject* _ParentPtr;
	size_t _ParentId;

public:

	IComponentSystem();
	virtual ~IComponentSystem() {}

	virtual std::string ComponentName() const;

	size_t GetParentId() const;
	void SetParentId(size_t inVal);
	GameObject* GetParentPtr();
	void SetParentPtr(GameObject* inVal);
	IComponentSystem* GetSibilingComponent(unsigned _componentId);
};

#endif
