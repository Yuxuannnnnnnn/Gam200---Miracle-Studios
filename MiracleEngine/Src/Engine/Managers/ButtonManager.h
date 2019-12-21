#ifndef _BUTTON_MANAGER_H
#define _BUTTON_MANAGER_H

#include <unordered_map>
#include "Components/ButtonComponent.h"

#include "Interfaces/IManager.h"

class ButtonManager final : public IManager
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

	void AddObject(size_t uId, void* component = 0);
	void RemoveObject(size_t uId);
};

#endif
