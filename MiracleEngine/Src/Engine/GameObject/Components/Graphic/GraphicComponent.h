#pragma once
#include "../../IComponent.h"
#include "GameObject/IAllocator.h"
#include "SystemGraphics/RenderLayer.h"

enum class TypeIdGraphic {
	NONE = 0,

};

class GraphicComponent : public IComponent
{
private:

	std::string _fileName;      
	std::string _shader;
	RenderLayer _renderlayer;

	float u0, v0;
	float u1, v1;

public:

	unsigned int GetTextureID() const;               // base on asset file name, get the textureID on OpenGL for imgui
	
	const std::string& GetFileName() const;
	void SetFileName(const std::string& filename);


	const std::string& GetShaderType()
	{
		return _shader;
	}


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
	void SetTextureState(int state)
	{

	}

	int GetRenderLayer()
	{
		return 0;
	}
	void SetRenderLayer(int state);


	unsigned& GetTypeId();
};

