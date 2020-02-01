#pragma once
#include "PrecompiledHeaders.h"
#include "ButtonComponent.h"

ButtonComponent::ButtonComponent() :
	_buttonUId{ 0 },
	_currState{ ButtonStates::NORMAL },
	_haveHoverState{ false },
	_havePressState{ false },
	_normalFileName{},
	_hoveredFileName{},
	_pressedFileName{},
	_pressedAtStart{false}
{}

std::string ButtonComponent::ComponentName() const
{
	return std::string("Button Component");
}

void ButtonComponent::Inspect()
{
	IComponent::Inspect();
	ImGui::Spacing();

	ImGui::InputInt("Button ID", &_buttonUId);
	ImGui::Spacing();

	static auto& graphicList = MyResourceSystem.GetTexture2DList();
	std::vector<const char*> list(graphicList.size());
	//list[0] = "Choose a Texture ";

	int i = 0;
	int select1 = 0;
	int select2 = 0;
	int select3 = 0;
	for (auto graphicPair = graphicList.begin(); graphicPair != graphicList.end(); graphicPair++)
	{
		const char* ptr = graphicPair->first.c_str();
		list[i] = ptr;

		if (!strncmp(ptr, _normalFileName.c_str(), 20))
			select1 = i;

		if (!strncmp(ptr, _normalFileName.c_str(), 20))
			select2 = i;

		if (!strncmp(ptr, _normalFileName.c_str(), 20))
			select3 = i;

		i++;
	}

	static ComboFilterState s1 = { select1, 0 };
	static char buf1[128];
	static ImGuiFunctions function;
	static bool op = false;
	static bool* open = &op;

	if (_normalFileName.empty())
		strncpy(buf1, "type text here...", 18);
	else
		strncpy(buf1, _normalFileName.c_str(), _normalFileName.size());

	function.ComboFilter("Normal Texture", buf1, IM_ARRAYSIZE(buf1), list, list.size(), s1, _normalFileName, open);
	ImGui::Spacing();


	ImGui::Spacing();
	ImGui::Checkbox("Have Hovered State", &_haveHoverState);
	ImGui::Spacing();

	if (_haveHoverState)
	{
		static ComboFilterState s2 = { select2, 0 };
		static char buf2[128];
		static bool op = false;
		static bool* open = &op;

		if (_hoveredFileName.empty())
			strncpy(buf2, "type text here...", 18);
		else
			strncpy(buf2, _hoveredFileName.c_str(), _hoveredFileName.size());

		function.ComboFilter("Hovered Texture", buf2, IM_ARRAYSIZE(buf2), list, list.size(), s2, _hoveredFileName, open);
		ImGui::Spacing();
	}

	ImGui::Spacing();
	ImGui::Checkbox("Have Pressed State", &_havePressState);
	ImGui::Spacing();

	if (_havePressState)
	{
		static ComboFilterState s3 = { select3, 0 };
		static char buf3[128];

		if (_pressedFileName.empty())
			strncpy(buf3, "type text here...", 18);
		else
			strncpy(buf3, _pressedFileName.c_str(), _pressedFileName.size());

		function.ComboFilter("Pressed Texture", buf3, IM_ARRAYSIZE(buf3), list, list.size(), s3, _pressedFileName, open);
		ImGui::Spacing();
	}
}

///////////////////////////////////////////////////////////////////////////////
	// Function Setting and Getting only

size_t ButtonComponent::GetButtonUId()
{
	return (size_t)_buttonUId;
}

void ButtonComponent::ButtonNormalState()
{
	if (_currState == ButtonStates::NORMAL)
		return;

	_currState = ButtonStates::NORMAL;

	GraphicComponent* graphic = (GraphicComponent*)GetComponentMap(Graphic)[this->GetParentId()];

	if (!graphic || !graphic->GetEnable())
		return;

	graphic->SetFileName(_normalFileName);
}

void ButtonComponent::ButtonHoveredState()
{
	if (!_haveHoverState || _currState == ButtonStates::HOVERED)
		return;

	_currState = ButtonStates::HOVERED;

	GraphicComponent* graphic = (GraphicComponent*)GetComponentMap(Graphic)[this->GetParentId()];

	if (!graphic || !graphic->GetEnable())
		return;

	graphic->SetFileName(_hoveredFileName);
}

void ButtonComponent::ButtonPressedState()
{
	if (!_havePressState || _currState == ButtonStates::PRESSED)
		return;

	_currState = ButtonStates::PRESSED;

	GraphicComponent* graphic = (GraphicComponent*)GetComponentMap(Graphic)[this->GetParentId()];

	if (!graphic || !graphic->GetEnable())
		return;

	graphic->SetFileName(_pressedFileName);
}