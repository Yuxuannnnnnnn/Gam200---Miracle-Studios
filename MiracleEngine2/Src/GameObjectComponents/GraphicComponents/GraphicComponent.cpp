#include "PrecompiledHeaders.h"




GraphicComponent::GraphicComponent(GameObject* parent, size_t uId, IComponentSystem* component)
	: IComponentSystem(parent, uId),
	_typeIdGraphic{ (unsigned)TypeIdGraphic::NONE },
	_fileName{ std::string() },
	_shaderID{ 0 },
	_textureID{ 0 }
{

	if (component)
	{
		GraphicComponent* graphicComponent = dynamic_cast<GraphicComponent*>(component);
		_typeIdGraphic = graphicComponent->_typeIdGraphic;
		_fileName = graphicComponent->_fileName;
		_shaderID = graphicComponent->_shaderID;
		_textureID = graphicComponent->_textureID;
	}
}



GraphicComponent::GraphicComponent() :
	_typeIdGraphic{ (unsigned)TypeIdGraphic::NONE },
	_fileName{ std::string() },
	_shaderID{ 0 },
	_textureID{ 0 }
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
	
}

GraphicComponent& GraphicComponent::operator= (const GraphicComponent& rhs)
{
	_typeIdGraphic = rhs._typeIdGraphic;
	_fileName = rhs._fileName;
	_shaderID = rhs._shaderID;
	_textureID = rhs._textureID;
	return *this;
}

std::string GraphicComponent::ComponentName() const
{
	return "Graphic Component";
}


void GraphicComponent::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("G.TypeId") && document["G.TypeId"].IsInt())	//Checks if the variable exists in .Json file
		_typeIdGraphic = document["G.TypeId"].GetInt();

	if (document.HasMember("G.FileName") && document["G.FileName"].IsString())
		_fileName = document["G.FileName"].GetString();
}

void GraphicComponent::Inspect()
{
}
