#pragma once
#include "PrecompiledHeaders.h"
#include "ButtonComponent.h"

ButtonComponent::ButtonComponent() :
	_buttonUId{ 0 },
	_pressed{false},
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

	static auto& graphicList = MyResourceSystem.GetTexture2DList();
	std::vector<const char*> list(graphicList.size());
	//list[0] = "Choose a Texture ";

	int i = 0;
	int select = 0;
	for (auto graphicPair = graphicList.begin(); graphicPair != graphicList.end(); graphicPair++)
	{
		const char* ptr = graphicPair->first.c_str();


		list[i] = ptr;
		if (!strncmp(ptr, _normalFileName.c_str(), 20))
		{
			select = i;
		}


		i++;
	}

	static ImGuiFunctions::ComboFilterState s = { select, 0 };

	static char buf[128];

	if (_normalFileName.empty())
	{
		strncpy(buf, "type text here...", 18);
	}
	else
	{
		strncpy(buf, _normalFileName.c_str(), _normalFileName.size());
	}

	if (ImGuiFunctions::ComboFilter("Texture", buf, IM_ARRAYSIZE(buf), list, list.size(), s, _normalFileName))
	{
		//puts(buf);
	}
}

///////////////////////////////////////////////////////////////////////////////
	// Function Setting and Getting only

