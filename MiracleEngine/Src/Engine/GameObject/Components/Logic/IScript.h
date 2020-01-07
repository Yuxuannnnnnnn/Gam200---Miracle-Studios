#pragma once
#include "../../IComponent.h" // need to be able to access other components
#include "Tools/EventHandler/IColliderHandler.h"
#include "Tools/EventHandler/IMouseHandler.h"
#include "SystemPhysics/IForce.h"

#include "Imgui/imgui.h"
#include "Tools/FileIO/DeSerialiser.h"
#include "Tools/FileIO/Serialiser.h"

#include "GameObject/Components/Physic/ICollider2D.h"

//#include "../PrecompiledComponentHeader.h"

#ifndef ISCRIPT_H
#define	ISCRIPT_H

enum class ScriptId {
	EMPTY = 0,

	PLAYER,
	TURRET,

	ENEMY,
	ENEMYTWO,
	ENEMYTHREE,
	BOSS,	
	SPAWNER,	
	SPAWNERTWO,

	PICK_UPS,
	BULLET,
	EXPLOSION,

	BUTTON_UI,	
};

class IScript : public IColliderHandler, public IMouseHandler, public IForce, public IComponent
{
private:
	unsigned _ScriptType;
public:
	bool _componentEnable;

	IScript() : _ScriptType{ (unsigned)ScriptId::EMPTY }, _componentEnable{ true } {}
	virtual ~IScript() {}

	IScript(const IScript& copy) = default;

	std::string ComponentName() const 
	{
		return "IScript Component";
	}

	void SerialiseComponent(Serialiser& document) 	{}
	void DeSerialiseComponent(DeSerialiser& prototypeDoc) 	{}
	void Inspect() 	{}

	ScriptId static ScriptStringToInt(std::string& in) ;

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

	IComponent* CloneComponent() { return nullptr; }
};


#endif