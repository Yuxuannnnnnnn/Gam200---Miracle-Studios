#pragma once
#include "GameObject/GameObject.h"
#include "Tools/EventHandler/IColliderHandler.h"
#include "Tools/EventHandler/IMouseHandler.h"
#include "SystemPhysics/IForce.h"

#include "Imgui/imgui.h"
#include "Tools/FileIO/DeSerialiser.h"
#include "Tools/FileIO/Serialiser.h"

enum class ScriptType {
	SCRIPT_Player,
	SCRIPT_COUNT
};

inline const char* ToScriptName(ScriptType type)
{
	switch (type)
	{
	case ScriptType::SCRIPT_Player:		return "Player";

	default:      return "None";
	}
}

class IScript2 : public IColliderHandler, public IMouseHandler, public IForce
{
private:
	GameObject* _parent;
public:
	size_t _uId;
	ScriptType _type;
	
	bool _scriptEnable;

	IScript2();
	virtual ~IScript2() {}

	std::string ComponentName() const
	{
		return "IScript Component";
	}

	void SerialiseComponent(Serialiser& document) {}
	void DeSerialiseComponent(DeSerialiser& prototypeDoc) {}
	void Inspect() {}

	virtual IScript2* Clone() = 0;

	virtual void Update(double dt) = 0;

	void SetParentPtr(GameObject* parent)
	{
		_parent = parent;
	}

	GameObject* GetParentPtr() const
	{
		return _parent;
	}



};
