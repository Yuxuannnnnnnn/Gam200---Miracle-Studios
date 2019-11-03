#include "PrecompiledHeaders.h"



//GraphicComponent::GraphicComponent(GameObject* parent, size_t uId, IComponentSystem* component)
//	: IComponentSystem(parent, uId),
//	_typeIdGraphic{ (unsigned)TypeIdGraphic::NONE },
//	_fileName{ std::string() },
//	_shaderID{ 0 },
//	_textureID{ 0 }
//{
//
//	if (component)
//	{
//		GraphicComponent* graphicComponent = dynamic_cast<GraphicComponent*>(component);
//		_typeIdGraphic = graphicComponent->_typeIdGraphic;
//		_fileName = graphicComponent->_fileName;
//		_shaderID = graphicComponent->_shaderID;
//		_textureID = graphicComponent->_textureID;
//	}
//}



GraphicComponent::GraphicComponent() :
	_typeIdGraphic{ (unsigned)TypeIdGraphic::NONE },
	_fileName{ new char[40] },
	_shaderID{ 0 },
	_textureID{ 0 },
	_renderLayer{ 0 }
{
}

GraphicComponent::~GraphicComponent()
{
	delete []_fileName;
}

GraphicComponent::GraphicComponent(const GraphicComponent& rhs)
{
	_typeIdGraphic = rhs._typeIdGraphic;
	_fileName = new char[40];
	strcpy_s(_fileName, 40, rhs._fileName);
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


void GraphicComponent::SerialiseComponent(Serialiser& document)
{
	if (document.HasMember("G.TypeId") && document["G.TypeId"].IsInt())	//Checks if the variable exists in .Json file
		_typeIdGraphic = document["G.TypeId"].GetInt();

	if (document.HasMember("G.FileName") && document["G.FileName"].IsString())
		strcpy_s(_fileName, 40, document["G.FileName"].GetString());
}

void GraphicComponent::Inspect()
{
	//_fileName
	//	_shaderID
	//	_renderLayer
	IComponentSystem::Inspect();

	ImGui::Spacing();
	ImGui::InputText("Static Graphic File Name", _fileName, IM_ARRAYSIZE(_fileName));
	ImGui::Spacing();
	ImGui::InputInt("Shader ID", &_shaderID);
	ImGui::Spacing();
	ImGui::InputInt("RendeerLayer", &_renderLayer);
	ImGui::Spacing();


}
