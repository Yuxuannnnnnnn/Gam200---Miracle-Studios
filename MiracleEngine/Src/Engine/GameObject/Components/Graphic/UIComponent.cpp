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
	_fileName{}
{
}

UIComponent::~UIComponent()
{
	//delete[]_fileName;
}

UIComponent::UIComponent(const UIComponent& rhs)
{
	_fileName = rhs._fileName;;

}

UIComponent& UIComponent::operator= (const UIComponent& rhs)
{
	_fileName = rhs._fileName;
	return *this;
}

std::string UIComponent::ComponentName() const
{
	return "UI Component";
}

