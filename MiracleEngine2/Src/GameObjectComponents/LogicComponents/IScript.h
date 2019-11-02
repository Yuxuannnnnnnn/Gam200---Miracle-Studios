#pragma once
#include "PrecompiledHeaders.h"
#include "GameObjectComponents/IComponentSystem.h" // need to be able to access other components
#include "GameObjectComponents/PrecompiledComponentHeader.h"
#include "Tools/EventHandler/IColliderHandler.h"
#include "Tools/EventHandler/IMouseHandler.h"

#ifndef ISCRIPT_H
#define	ISCRIPT_H

enum class ScriptId {
	EMPTY = 0,
	PLAYER = 1
};

class IScript : public IComponentSystem
{
private:
	unsigned _ScriptType;
public:
	IScript() : _ScriptType{ (unsigned)ScriptId::EMPTY } {}
	virtual ~IScript() {}

	virtual void Update(double dt) {}

	void SetType(ScriptId type)
	{
		if (_ScriptType == (unsigned)ScriptId::EMPTY)
			_ScriptType = (unsigned)type;
	}

	ScriptId GetType() const 
	{
		return (ScriptId)_ScriptType;
	}
};


#endif