#pragma once
#include "IComponentSystem.h"

#ifndef BUTTONCOMPONENT_H
#define BUTTONCOMPONENT_H

class ButtonComponent : public BoxCollider2D
{
public:
	bool _pressed;
	int _buttonType;

public:
	ButtonComponent();
	ButtonComponent(const ButtonComponent& rhs) = default;
	virtual ~ButtonComponent() = default;
	
	ButtonComponent& operator=(const ButtonComponent& rhs) = delete;

	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser& document) override;
	void Inspect();

///////////////////////////////////////////////////////////////////////////////
	// Function Setting and Getting only

};

#endif