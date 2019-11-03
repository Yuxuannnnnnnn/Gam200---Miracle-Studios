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

	// bool transparent.. so on
	//Store the vb, ib, vao, shader

public:
	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser& document) override;
	virtual void Inspect() override;

	//Constructor
	GraphicComponent(GameObject* parent, size_t uId, IComponentSystem* component = nullptr);
	GraphicComponent();
	virtual ~GraphicComponent();
	GraphicComponent(const GraphicComponent& rhs);
	GraphicComponent& operator=(const GraphicComponent& rhs);

	unsigned& GetTypeId()
	{
		return _typeIdGraphic;
	}
	std::string& GetFileName()
	{
		return _fileName;
	}
};

