#pragma once
#include "PrecompiledHeaders.h"
#include "ButtonComponent.h"

ButtonComponent::ButtonComponent() :
	_buttonType{ 0 },
	_pressed{false}
{}

std::string ButtonComponent::ComponentName() const
{
	return std::string("Button Component");
}



///////////////////////////////////////////////////////////////////////////////
	// Function Setting and Getting only

