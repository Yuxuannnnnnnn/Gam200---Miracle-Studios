#pragma once
#include <string>
#include "PrecompiledHeaders.h"

#ifndef ICOMPONENTSYSTEM_H
#define	ICOMPONENTSYSTEM_H

enum class SerialTypeId {
	TRANSFORM_DATA = 0,
	GRAPHICS_DATA = 1,
	RIGIDBODY_DATA = 2,
	COLLIDER_DATA = 3,
	AUDIO_DATA = 4,
	LOGIC_DATA = 5
};

enum class ComponentId {
	TRANSFORM_COMPONENT = 0,
	GRAPHICS_COMPONENT = 1,
	RIGIDBODY_COMPONENT = 2,
	CIRCLECOLLIDER_COMPONENT = 3,
	BOXCOLLIDER_COMPONENT = 4,
	LINECOLLIDER_COMPONENT = 5,
	AUDIO_COMPONENT = 6,
	LOGIC_COMPONENT = 7
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

	void DestoryThis();
};

#endif
