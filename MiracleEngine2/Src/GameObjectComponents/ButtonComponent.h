#pragma once
#include "IComponentSystem.h"

#ifndef BUTTONCOMPONENT_H
#define BUTTONCOMPONENT_H

class ButtonComponent : public BoxCollider2D
{
	
public:
	bool _pressed;
	int _buttonType;
	ButtonComponent();
	virtual ~ButtonComponent() = default;
	ButtonComponent(const ButtonComponent& rhs);
	ButtonComponent& operator= (const ButtonComponent& rhs) = delete;
	void SerialiseComponent(Serialiser& document) override;
	std::string ComponentName() const override;
	void Inspect();
};

#endif
