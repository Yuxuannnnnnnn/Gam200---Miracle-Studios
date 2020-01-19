#pragma once

#include "UIMesh.h"
#include "../Engine/GameObject/Components/Graphic/UIComponent.h"
#include <map>

class UIRenderer
{
public:
	void Update(std::unordered_map<size_t, IComponent*> uiMap);
private:
	UIMesh _uiMesh;
};