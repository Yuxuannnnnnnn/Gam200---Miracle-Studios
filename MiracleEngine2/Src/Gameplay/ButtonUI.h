#pragma once
#include "GameObjectComponents/LogicComponents/IScript.h"

// create a enum for buttonType
enum class ButtonType {
	NONE = 0,
	CLOSE,
	OPEN,
};

class ButtonUI : public IScript
{
private:
	int _buttonType;
public:
	//Constructor
	ButtonUI();
	// override these functions
	virtual void OnMouseDown();
	virtual void OnMouseEnter();
	virtual void OnMouseOver();
	virtual void OnMouseExit();
	
	// InUpEx
	void Init();
	void Update();
	void Exit();

	void SerialiseComponent(Serialiser& document);
};