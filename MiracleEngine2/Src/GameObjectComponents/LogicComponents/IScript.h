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
	PLAYER = 1,
	BULLET = 2,
	ENEMY = 3,
	TURRET = 4,
	SPAWNER = 5,
	ENEMYTWO = 6,
};

class IScript : public IComponentSystem, public IColliderHandler, public IMouseHandler
{
private:
	unsigned _ScriptType;
public:
	bool _componentEnable;


	IScript() : _ScriptType{ (unsigned)ScriptId::EMPTY }, _componentEnable{ true } {}
	virtual ~IScript() {}


	IScript(const IScript& copy) = default;

	std::string ComponentName() const override
	{
		return "IScript Component";
	}

	void SerialiseComponent(Serialiser & document) override
	{

	}

	virtual void Inspect() override
	{

	}

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