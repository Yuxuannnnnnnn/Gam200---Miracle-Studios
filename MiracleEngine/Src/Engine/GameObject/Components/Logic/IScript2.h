#pragma once
#include "GameObject/GameObject.h"
#include "Tools/EventHandler/IColliderHandler.h"
#include "Tools/EventHandler/IMouseHandler.h"
#include "SystemPhysics/IForce.h"
#include "GameObject/IComponent.h"

#include "Imgui/imgui.h"
#include "Tools/FileIO/DeSerialiser.h"
#include "Tools/FileIO/Serialiser.h"

#include "ScriptTypeId.h"

class IScript2 : public IColliderHandler, public IMouseHandler, public IForce
{
private:
	GameObject* _parent;
	size_t _parentUId;
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

	virtual void SerialiseComponent(Serialiser& document) = 0;
	virtual void DeSerialiseComponent(DeSerialiser& prototypeDoc) = 0;
	virtual void Inspect() = 0;
	virtual void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator) {}

	virtual IScript2* Clone() = 0;

	virtual void Init() {}
	virtual void Update(double dt) = 0;

	void SetParentPtr(GameObject* parent);
	GameObject* GetParentPtr() const;

	void SetParentId(size_t uid);
	size_t GetParentId() const;

	IComponent* GetSibilingComponent(ComponentId id);
	IScript2* GetSibilingScript(ScriptType type);

};

