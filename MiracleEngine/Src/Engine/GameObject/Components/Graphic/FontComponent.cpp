
#include "PrecompiledHeaders.h"
#include "FontComponent.h"





glm::vec3 FontComponent::GetFontColor() const
{
	return glm::vec3{ _color[0], _color[1], _color[2]};
}

float FontComponent::GetDelayTime() const
{
	return _delayTime;
}

float FontComponent::IsStartDisplaying() const
{
	return _startDisplaying;
}

std::string FontComponent::ComponentName() const
{
	return "Font Component";
}

std::string& FontComponent::GetFontString()
{
	return _fontString;
}

void FontComponent::Inspect()
{
	static char buffer[300] = " ";
	ImGui::InputText("Text To OutPut  ", buffer, 300);
	_fontString = buffer;

	ImGui::Spacing();

	static auto& fontList = MyResourceSystem.GetFontList();
	std::vector<const char*> list;
	list.push_back("Choose a Font ");
	static const char* name = list[0];


	int i = 1;
	static int select = 0;
	for (auto fontPair = fontList.begin(); fontPair != fontList.end(); fontPair++)
	{
		const char* ptr = fontPair->first.c_str();

		list.push_back(ptr);

	}

	if (ImGui::BeginCombo("Font", list[select], 0)) // The second parameter is the label previewed before opening the combo.
	{
		for (int n = 0; n < list.size(); n++)
		{
			bool is_selected = (name == list[n]);
			if (ImGui::Selectable(list[n], is_selected))
			{
				_fontType = list[n];
				select = n;
			}

			//if (is_selected);
			//ImGui::SetItemDefaultFocus();   // Set the initial focus when opening the combo (scrolling + for keyboard navigation support in the upcoming navigation branch)

		}
		ImGui::EndCombo();
	}

	ImGui::ColorEdit3("color", _color);

	ImGui::Checkbox("start text", &_startDisplaying);

	ImGui::InputFloat("Delay time", &_delayTime);
	//ImGui::SliderFloat(string.c_str(), &_alphaVal, 0, 1);
}