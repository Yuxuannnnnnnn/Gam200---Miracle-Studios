#include "PrecompiledHeaders.h"


const std::string& UIComponent::GetFileName() const
{
	return _fileName;
}

void UIComponent::SetFileName(const std::string& filename)
{
	_fileName = filename;
}

UIComponent::UIComponent() :
	_fileName{},
	_layer{ 11 }
{
}

UIComponent::~UIComponent()
{
	//delete[]_fileName;
}

std::string UIComponent::ComponentName() const
{
	return "UI Component";
}

void UIComponent::Init()
{
}

void UIComponent::LoadResource()
{
#ifdef LEVELEDITOR
	MyResourceManager.AddNewTexture2DResource({ _fileName, MyResourceSystem.GetTexture2DResourcePath(_fileName) });
#endif // LEVELEDITOR
}
