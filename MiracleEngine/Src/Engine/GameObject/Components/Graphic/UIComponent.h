#pragma once
#include "../../IComponent.h"
#include "GameObject/IAllocator.h"


class UIComponent : public IComponent, public IBase<UIComponent>
{
private:

	std::string _fileName;
	unsigned int _textureID;

public:

	const std::string& GetFileName() const;
	void SetFileName(const std::string& filename);


	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser& document) override;
	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;
	virtual void Inspect() override;

	//Constructor
	UIComponent();
	virtual ~UIComponent();
	UIComponent(const UIComponent& rhs);
	UIComponent& operator=(const UIComponent& rhs);
};

