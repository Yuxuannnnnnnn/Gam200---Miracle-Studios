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

std::string GraphicComponent::ComponentName() const
{
	return "Graphic Component";
}