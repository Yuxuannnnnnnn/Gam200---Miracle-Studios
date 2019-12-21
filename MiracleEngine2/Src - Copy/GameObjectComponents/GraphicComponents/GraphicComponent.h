#pragma once
#include "GameObjectComponents/IComponentSystem.h"
#include "GameObjectComponents/IBase.h"

enum class TypeIdGraphic {
	NONE = 0,

};

class GraphicComponent : public IComponentSystem, public IBase<GraphicComponent>
{
private:

	std::string _fileName;       // change back to filepath
	unsigned int _textureID;         // texture id for opengl


	unsigned _typeIdGraphic;
	int _shaderID;

	std::vector<std::string> _shaderList;

	int _textureState = 0; // for enemy with move and attack, this tell you which texture to run
	int _renderLayer = 0;
	// bool transparent.. so on

private:
	std::vector<const char*> _current_ShaderList;

public:

	unsigned int GetTextureID() const;               // base on asset file name, get the textureID on OpenGL for imgui
	
	const std::string& GetFileName() const;
	void SetFileName(const std::string& filename);


	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser& document) override;
	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;
	virtual void Inspect() override;

	//Constructor
	GraphicComponent();
	virtual ~GraphicComponent();
	GraphicComponent(const GraphicComponent& rhs);
	GraphicComponent& operator=(const GraphicComponent& rhs);


	void RenderLayerResolver();

	int GetTextureState();
	void SetTextureState(int state);

	int GetRenderLayer();
	void SetRenderLayer(int state);


	unsigned& GetTypeId();
};

