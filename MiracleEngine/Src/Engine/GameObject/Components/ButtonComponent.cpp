#pragma once
#include "PrecompiledHeaders.h"
#include "ButtonComponent.h"

ButtonComponent::ButtonComponent() :
	_buttonUId{ 0 },
	_normalFileName{},
	_hoveredFileName{},
	_pressedFileName{}

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

	static ImGuiFunctions::ComboFilterState s1 = { select1, 0 };
	static char buf1[128];

	if (_normalFileName.empty())
		strncpy(buf1, "type text here...", 18);
	else
		strncpy(buf1, _normalFileName.c_str(), _normalFileName.size());

	ImGuiFunctions::ComboFilter("Normal Texture", buf1, IM_ARRAYSIZE(buf1), list, list.size(), s1, _normalFileName);
	ImGui::Spacing();

	static ImGuiFunctions::ComboFilterState s2 = { select2, 0 };
	static char buf2[128];

	if (_hoveredFileName.empty())
		strncpy(buf2, "type text here...", 18);
	else
		strncpy(buf2, _hoveredFileName.c_str(), _hoveredFileName.size());

	ImGuiFunctions::ComboFilter("Hovered Texture", buf2, IM_ARRAYSIZE(buf2), list, list.size(), s2, _hoveredFileName);
	ImGui::Spacing();

	static ImGuiFunctions::ComboFilterState s3 = { select3, 0 };
	static char buf3[128];

	if (_pressedFileName.empty())
		strncpy(buf3, "type text here...", 18);
	else
		strncpy(buf3, _pressedFileName.c_str(), _pressedFileName.size());

	ImGuiFunctions::ComboFilter("Pressed Texture", buf3, IM_ARRAYSIZE(buf3), list, list.size(), s3, _pressedFileName);
	ImGui::Spacing();
}

///////////////////////////////////////////////////////////////////////////////
	// Function Setting and Getting only

