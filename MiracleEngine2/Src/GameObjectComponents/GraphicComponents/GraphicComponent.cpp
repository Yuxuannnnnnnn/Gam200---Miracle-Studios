#include "PrecompiledHeaders.h"

int GraphicComponent::GetRenderLayer()
{
	return _renderLayer;
}
void GraphicComponent::SetRenderLayer(int layer)
{
	_renderLayer = layer;
}

int GraphicComponent::GetTextureState()
{
	return _textureState;
}
void GraphicComponent::SetTextureState(int state)
{
	_textureState = state;
}


GraphicComponent::GraphicComponent() :
	_typeIdGraphic{ (unsigned)TypeIdGraphic::NONE },
	_fileName{ std::string() },
	_shaderID{ 0 },
	_textureID{ 0 },
	_renderLayer{ 0 }
{
}

GraphicComponent::~GraphicComponent()
{
	
}

GraphicComponent::GraphicComponent(const GraphicComponent& rhs)
{
	_typeIdGraphic = rhs._typeIdGraphic;
	_fileName = rhs._fileName;
	_shaderID = rhs._shaderID;
	_textureID = rhs._textureID;
	_renderLayer = rhs._renderLayer;
}

GraphicComponent& GraphicComponent::operator= (const GraphicComponent& rhs)
{
	_typeIdGraphic = rhs._typeIdGraphic;
	_fileName = rhs._fileName;
	_shaderID = rhs._shaderID;
	_textureID = rhs._textureID;
	_renderLayer = rhs._renderLayer;
	return *this;
}

void GraphicComponent::RenderLayerResolver()
{
	switch (GetParentPtr()->Get_typeId())
	{
	case (unsigned)TypeIdGO::FLOOR:
		_renderLayer = 0;
		break;
	case (unsigned)TypeIdGO::WALL:
		_renderLayer = 0;
		break;
	case (unsigned)TypeIdGO::PLAYER:
		_renderLayer = 5;
		break;
	case (unsigned)TypeIdGO::ENEMY:
		_renderLayer = 5;
		break;
	case (unsigned)TypeIdGO::TURRET:
		_renderLayer = 5;
		break;
	case (unsigned)TypeIdGO::BULLET:
		_renderLayer = 10;
		break;
	}
}

std::string GraphicComponent::ComponentName() const
{
	return "Graphic Component";
}