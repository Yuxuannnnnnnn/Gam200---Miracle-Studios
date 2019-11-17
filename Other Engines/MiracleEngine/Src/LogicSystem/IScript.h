#pragma once
#include "PrecompiledHeaders.h"
#include "GameObjectComponents/IComponentSystem.h" // need to be able to access other components

#ifndef ISCRIPT_H
#define	ISCRIPT_H


class IScript : public IComponentSystem
{
public:
	virtual ~IScript() {}

	virtual void Update(double dt) {}
};


#endif