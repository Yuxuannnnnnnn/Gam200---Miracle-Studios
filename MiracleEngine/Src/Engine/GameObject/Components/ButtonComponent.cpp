#pragma once
#include "PrecompiledHeaders.h"
#include "ButtonComponent.h"

ButtonComponent::ButtonComponent() :
	_transform{ nullptr },
	_graphic{ nullptr },
	_buttonUId{ 0 },
	_currState{ ButtonStates::NORMAL },
	_haveHoverState{ false },
	_havePressState{ false },
	_normalScale{ Vec3{1.f,1.f,1.f} },
	_hoveredScale{ Vec3{1.f,1.f,1.f} },
	_pressedScale{ Vec3{1.f,1.f,1.f} },
	_normalFileName{},
	_hoveredFileName{},
	_pressedFileName{},
	_hoveredAudioFileName{},
	_pressedAudioFileName{},
	_pressedAtStart{false}
{}

std::string ButtonComponent::ComponentName() const
{
	return std::string("Button Component");
}

void ButtonComponent::Init()
{
	_transform = (TransformComponent*)GetComponentMap(Transform)[GetParentId()];
	_graphic = (UIComponent*)GetComponentMap(UI)[this->GetParentId()];
}

void ButtonComponent::Inspect()
{
	IComponent::Inspect();
	ImGui::Spacing();

	ImGui::InputInt("Button ID", &_buttonUId);
	ImGui::Spacing();

	ImGui::NewLine();

	static auto& graphicList = MyResourceSystem.GetTexture2DList();
	std::vector<const char*> list(graphicList.size());

	static auto& AudioList = MyResourceSystem.GetSoundList();
	std::vector<const char*> soundlist(AudioList.size());

	//list[0] = "Choose a Texture ";

	int i = 0;
	int select1 = 0;
	int select2 = 0;
	int select3 = 0;

	int select4 = 0;
	int select5 = 0;

	for (auto& graphicPair = graphicList.begin(); graphicPair != graphicList.end(); graphicPair++)
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

	i = 0;
	for (auto& soundPair = AudioList.begin(); soundPair != AudioList.end(); soundPair++)
	{
		const char* ptr = soundPair->first.c_str();
		soundlist[i] = ptr;

		if (!strncmp(ptr, _hoveredAudioFileName.c_str(), 20))
			select4 = i;

		if (!strncmp(ptr, _pressedAudioFileName.c_str(), 20))
			select5 = i;
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

	function.ComboFilter("Normal Texture", buf1, IM_ARRAYSIZE(buf1), list, (int)list.size(), s1, _normalFileName, open);
	ImGui::Spacing();

	ImGui::InputFloat2("Normal Scale X, Y", _normalScale.m);

	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Checkbox("Have Hovered State", &_haveHoverState);
	ImGui::Spacing();

	if (_haveHoverState)
	{
		static ComboFilterState s2 = { select2, 0 };
		static char buf2[128];

		if (_hoveredFileName.empty())
			strncpy(buf2, "type text here...", 18);
		else
			strncpy(buf2, _hoveredFileName.c_str(), _hoveredFileName.size());

		function.ComboFilter("Hovered Texture", buf2, IM_ARRAYSIZE(buf2), list, (int)list.size(), s2, _hoveredFileName, open);
		ImGui::Spacing();

		ImGui::InputFloat2("Hovered Scale X, Y", _hoveredScale.m);
		ImGui::Spacing();

		static ComboFilterState s4 = { select4, 0 };
		static char buf4[128];

		if (_hoveredAudioFileName.empty())
			strncpy(buf4, "type text here...", 18);
		else
			strncpy(buf4, _hoveredAudioFileName.c_str(), _hoveredAudioFileName.size());

		function.ComboFilter("Hovered Audio File", buf4, IM_ARRAYSIZE(buf4), soundlist, (int)soundlist.size(), s4, _hoveredAudioFileName, open);
		ImGui::Spacing();
	}

	
	ImGui::Spacing();
	ImGui::Spacing();
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

		function.ComboFilter("Pressed Texture", buf3, IM_ARRAYSIZE(buf3), list, (int)list.size(), s3, _pressedFileName, open);
		ImGui::Spacing();

		ImGui::InputFloat2("Pressed Scale X, Y", _pressedScale.m);
		ImGui::Spacing();

		static ComboFilterState s5 = { select5, 0 };
		static char buf5[128];

		if (_pressedAudioFileName.empty())
			strncpy(buf5, "type text here...", 18);
		else
			strncpy(buf5, _pressedAudioFileName.c_str(), _pressedAudioFileName.size());

		function.ComboFilter("Pressed Audio File", buf5, IM_ARRAYSIZE(buf5), soundlist, (int)soundlist.size(), s5, _pressedAudioFileName, open);
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

	if (_graphic)
		_graphic->SetFileName(_normalFileName);

	if (_transform)
		_transform->SetScale(_normalScale);
}

void ButtonComponent::ButtonHoveredState()
{
	if (!_haveHoverState || _currState == ButtonStates::HOVERED)
		return;

	_currState = ButtonStates::HOVERED;

	if (_graphic)
		_graphic->SetFileName(_hoveredFileName);

	if (_transform)
		_transform->SetScale(_hoveredScale);

	MyAudioSystem.PlaySFX(_hoveredAudioFileName);
}

void ButtonComponent::ButtonPressedState()
{
	if (!_havePressState || _currState == ButtonStates::PRESSED)
		return;

	_currState = ButtonStates::PRESSED;

	if (_graphic)
		_graphic->SetFileName(_pressedFileName);

	if (_transform)
		_transform->SetScale(_pressedScale);
}