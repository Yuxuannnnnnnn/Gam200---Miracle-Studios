#ifndef BUTTONCOMPONENT_H
#define BUTTONCOMPONENT_H

#pragma once
#include "../IComponent.h"
#include "Tools/MathLib/Math.h"

enum class ButtonStates {
	NORMAL,
	HOVERED,
	PRESSED,

	TOTAL_BUTTONSTATE
};

class ButtonComponent : public IComponent
{
private:
	TransformComponent* _transform;
	UIComponent* _graphic;

	int _buttonUId;

	ButtonStates _currState;

	bool _haveHoverState;
	bool _havePressState;

	Vec3 _normalScale;
	Vec3 _hoveredScale;
	Vec3 _pressedScale;

	std::string _normalFileName;
	std::string _hoveredFileName;
	std::string _pressedFileName;

	std::string _hoveredAudioFileName;
public:
	bool _pressedAtStart;
	std::string _pressedAudioFileName;

	ButtonComponent();
	ButtonComponent(const ButtonComponent& rhs) = default;
	virtual ~ButtonComponent() = default;
	
	virtual void Init() override;
	virtual void LoadResource() override;

	ButtonComponent& operator=(const ButtonComponent& rhs) = delete;

	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser& document) override;


	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;

	void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator);

	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator);


	virtual void Inspect() override;

	size_t GetButtonUId();

	void ButtonNormalState();
	void ButtonHoveredState();
	void ButtonPressedState();


///////////////////////////////////////////////////////////////////////////////
	// Function Setting and Getting only
	ButtonComponent* CloneComponent() { return new ButtonComponent(*this); }
};

#endif