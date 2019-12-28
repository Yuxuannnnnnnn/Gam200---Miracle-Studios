
#include "PrecompiledHeaders.h"
#include "FontComponent.h"





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
}