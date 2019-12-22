///////////////////////////////////////////////////////////////////////////////////////
//
//	PhysicsSystem.h
//	
//	Authors: yinshuyu
//	Copyright 2019, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _BUTTON_MANAGER_H
#define _BUTTON_MANAGER_H

#include <unordered_map>
#include "GameObject/Components/ButtonComponent.h"

#include "IContainer.h"

class ButtonManager final 
{

public:
	ButtonManager() = default;
	~ButtonManager() {}

	ButtonManager(const ButtonManager& rhs) = delete;
	ButtonManager& operator= (const ButtonManager& rhs) = delete;

	void Update();
	void Draw();
};

#endif
