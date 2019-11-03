#pragma once
#include "GameObjectComponents/IComponentSystem.h"
#include "GameObjectComponents/IBase.h"

enum class TypeIdGraphic {
	NONE = 0,

};

class GraphicComponent : public IComponentSystem, public IBase<GraphicComponent>
{
private:
	unsigned _typeIdGraphic;
	std::string _fileName;

	int _shaderID;
	int _textureID;

	int _textureState; // for enemy with move and attack, this tell you which texture to run

	// bool transparent.. so on
	//Store the vb, ib, vao, shader

public:
	GraphicComponent();
	virtual ~GraphicComponent();
	GraphicComponent(const GraphicComponent& rhs);
	GraphicComponent& operator=(const GraphicComponent& rhs);

	std::string ComponentName() const override;

	int GetTextureState();
	void SetTextureState(int state);

	unsigned& GetTypeId()
	{
		return _typeIdGraphic;
	}
	std::string& GetFileName()
	{
		return _fileName;
	}
};

