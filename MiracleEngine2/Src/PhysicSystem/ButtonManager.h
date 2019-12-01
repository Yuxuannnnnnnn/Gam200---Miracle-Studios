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
#include "GameObjectComponents/ButtonComponent.h"

#include "IContainer.h"

class ButtonManager final : public IContainer
{
public:
	std::unordered_map< size_t, ButtonComponent*> _buttonList;

public:
	ButtonManager() = default;
	~ButtonManager() {}

	ButtonManager(const ButtonManager& rhs) = delete;
	ButtonManager& operator= (const ButtonManager& rhs) = delete;

	void Update();
	void Draw();

	void AddObject(size_t uId);
	void RemoveObject(size_t uId);
};

#endif
