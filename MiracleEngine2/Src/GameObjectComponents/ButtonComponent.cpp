#pragma once
#include "PrecompiledHeaders.h"
#include "ButtonComponent.h"

ButtonComponent::ButtonComponent() :
	_buttonType{ false },
	_pressed{false}
{}

std::string ButtonComponent::ComponentName() const
{
	return std::string("Button Component");
}

void ButtonComponent::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("ButtonType") && document["ButtonType"].IsInt())	//Checks if the variable exists in .Json file
	{
		_buttonType = (document["ButtonType"].GetInt());
	}
}

void ButtonComponent::Inspect()
{
	IComponentSystem::Inspect();
}

///////////////////////////////////////////////////////////////////////////////
	// Function Setting and Getting only

