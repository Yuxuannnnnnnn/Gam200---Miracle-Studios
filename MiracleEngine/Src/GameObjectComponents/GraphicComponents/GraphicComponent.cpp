#include "PrecompiledHeaders.h"

GraphicComponent::GraphicComponent() :
	_typeIdGraphic{ (unsigned)TypeIdGraphic::NONE },
	_fileName{ std::string() },
	_shaderID{ 0 },
	_textureID{ 0 },
	_pmesh{ new Mesh() }
{
}

GraphicComponent::~GraphicComponent()
{
	delete _pmesh;
}

GraphicComponent::GraphicComponent(const GraphicComponent& rhs)
{
	_typeIdGraphic = rhs._typeIdGraphic;
	_fileName = rhs._fileName;
	_shaderID = rhs._shaderID;
	_textureID = rhs._textureID;
	_pmesh = new Mesh();
}

GraphicComponent& GraphicComponent::operator= (const GraphicComponent& rhs)
{
	_typeIdGraphic = rhs._typeIdGraphic;
	_fileName = rhs._fileName;
	_shaderID = rhs._shaderID;
	_textureID = rhs._textureID;
	_pmesh = new Mesh();
	return *this;
}

std::string GraphicComponent::ComponentName() const
{
	return "Graphic Component";
}