#include "PrecompiledHeaders.h"

void GraphicComponent::SetAlpha(float alphaValue)
{
	_alphaVal = alphaValue;
}

float GraphicComponent::GetAlpha()
{
	return _alphaVal;
}

const std::string& GraphicComponent::GetFileName() const
{
	return _fileName;
}

void GraphicComponent::SetFileName(const std::string& filename)
{
	_fileName = filename;
}



unsigned int GraphicComponent::GetTextureID() const
{
	//auto it = EngineSystems::GetInstance()._graphicsSystem->GetTextureManager()._textureMap.find(_fileName);
	//
	//// if there is a filename in texturemap
	//if (it != EngineSystems::GetInstance()._graphicsSystem->GetTextureManager()._textureMap.end())
	//{
	//	return it->second->GetTextureID();
	//}


	//return _textureID;
	return 0;
}




GraphicComponent::GraphicComponent() :
	_fileName{}, 
	_shader{},
	_layer{ 1 }, _hasAlpha{false}
{
	_alphaVal = 1.0f;
}

GraphicComponent::~GraphicComponent()
{
	//delete[]_fileName;
}

//GraphicComponent::GraphicComponent(const GraphicComponent& rhs)
//{
//
//
//}
//
//GraphicComponent& GraphicComponent::operator= (const GraphicComponent& rhs)
//{
//
//	return *this;
//}

void GraphicComponent::RenderLayerResolver()
{
	IdentityComponent* IdCom = dynamic_cast<IdentityComponent*> (GetSibilingComponent(ComponentId::CT_Identity));
	std::string type = IdCom->ObjectType();

	
}


std::string GraphicComponent::ComponentName() const
{
	return "Graphic Component";
}





//unsigned& GraphicComponent::GetTypeId()
//{
//	return _typeIdGraphic;
//}