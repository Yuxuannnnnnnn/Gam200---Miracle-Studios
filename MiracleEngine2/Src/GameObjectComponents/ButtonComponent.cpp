#pragma once
#include "PrecompiledHeaders.h"
#include "ButtonComponent.h"

ButtonComponent::ButtonComponent() :
	_buttonType{ false }
{}

ButtonComponent::ButtonComponent(const ButtonComponent& rhs)
{
	_buttonType = rhs._buttonType;
	_pressed = rhs._pressed;
}


void ButtonComponent::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("ButtonType") && document["ButtonType"].IsInt())	//Checks if the variable exists in .Json file
	{
		_buttonType = (document["ButtonType"].GetInt());
	}
}

std::string ButtonComponent::ComponentName() const
{
	return std::string("Button Component");
}

void ButtonComponent::Inspect()
{
	IComponentSystem::Inspect();
}
